import os
import pickle
import platform
import sys

import chardet
from konlpy.tag import Mecab

JOSA = {'가', '같이', '고', '과과', '는', '과', '를', '과', '의', '까지', '까지', '는', '까지', '의', '께', '께서', '께서', '는', '께서', '도', '나',
        '는', '니', '다대', '로', '도', '든', '라라고', '라도', '랑', '로로', '가로', '는', '로', '도로', '부터', '로서', '로서', '의', '로써', '로',
        '의', '를', '마다', '만만', '에', '만', '으로', '만', '을', '만의', '만', '이만큼', '며', '밖', '에', '보', '고', '보', '다', '보다', '는',
        '보다', '도', '부터', '부터', '는', '아야', '에', '에게', '에게', '는', '에', '는', '에도', '에', '만', '에서', '에서', '는', '에서', '도',
        '에서', '의', '에', '선', '엔', '여와', '와', '는', '와', '의요', '으로', '으로', '는', '으로', '도', '으로부터', '으로서', '으로서', '의',
        '으로써', '으로', '의', '은', '을', '의이', '이', '고', '이', '나이다', '이라이', '라고', '이', '라는', '이라도', '이', '며', '이', '야조', '차',
        '처럼', '치', '고', '토록', '하', '고'}

EOMI = {'ㄴ', 'ㄴ', '가', 'ㄴ', '가', '를', 'ㄴ', '다', 'ㄴ다고', 'ㄴ', '다는', 'ㄴ', '다면', 'ㄴ', '데', 'ㄴ', '데', '다', 'ㄴ', '지', 'ㄴ지',
        '를', 'ㄹ', 'ㄹ', '까', 'ㄹ까', '요', 'ㄹ', '라', 'ㄹ', '만한', 'ㄹ', '수록', 'ㄹ', '지', 'ㅁ', 'ㅂ', '니까', 'ㅂ니다', 'ㅂ시다', 'ㅂ', '시',
        '오', '거나', '건', '게', '고고', '는', '고도', '고서', '고서', '는', '고자', '곤구', '나군', '기기', '로', '기', '에', '긴', '길나', '나',
        '요나', '이', '다냐', '네', '는', '는', '가', '는가', '를', '는', '가', '에', '는', '다', '는다는', '는', '대로', '는', '데', '는데', '다',
        '는데도', '는', '지', '는지', '를', '니', '니까니', '라다', '다', '가', '다고', '다', '는다며', '다', '면', '다', '면서', '단다', '더', '니더',
        '라도', '던', '도록', '되', '든', '듯', '듯이', '디', '라', '라고', '라는', '라도', '라며', '라면', '라면', '서란', '랍니다', '래', '러', '려',
        '려고', '려는', '려면', '련마', '매', '며', '면면', '서', '면서', '도', '므로', '므로써', '세', '세요', '소습', '니까', '습니다', '아', '아라',
        '아서', '아야', '어', '어', '다', '어도', '어라', '어서어서', '는', '어서', '도', '어서', '만', '어', '선어', '야', '어야', '만어', '요오', '요',
        '으', '나으니', '으리', '라', '으며', '으면', '으면', '서', '으므로', '은', '을', '을', '까', '을까요', '을', '수', '록음', '음', '에', '도',
        '이', '자자', '고자', '는', '자', '면', '죠', '지', '지', '는지', '도지', '를', '지만', '지', '요', '진질'}


def process_files(file_list: list, encoding):
    data = []
    for file_path in file_list:
        print(f"Decoding file {file_path}")
        with open(file_path, 'rb') as f:
            temp = f.read()
        temp = temp.split(b'\n')
        if encoding == 'auto':
            encoding = chardet.detect(b"".join(temp[:max(len(temp), 1000)]))['encoding']
        for i in range(len(temp)):
            try:
                data.append(temp[i].decode(encoding=encoding))
            except UnicodeDecodeError:
                pass
    data = "".join(data)
    return data


def process_data(data: str):
    mecab_dict = {'tail_eomi': EOMI,
                  'tail_josa': JOSA,
                  'tail_suffix': set()
                  }
    status = {
        'J': 'tail_josa',
        'E': 'tail_eomi',
        'X': 'tail_suffix'
    }
    print(f"Process data with Mecab...")
    mecab = Mecab()
    mecab_result = mecab.pos(data, flatten=False)
    for i in mecab_result:
        if len(i):
            for j in i:
                word = j[0]
                tag = j[1]
                if tag[0] in ['J', 'E', 'X']:
                    idx = 0
                    s = status[tag[0]]
                    while idx < len(i) and i[idx][1][0] in ['J', 'E', 'X']:
                        mecab_dict[s].add(word)
                        word += i[idx][0]
                        idx += 1
    return mecab_dict


def main(args):
    if platform.system() != "Linux":
        print(
            f"====Only works on Linux, not {platform.system()}====\nUsage:\npython generate_dict.py [input_file_path or input_file_dir] [encoding=auto]")
        return 1
    elif len(args) == 3:
        file_path = args[1]
        encoding = args[2]
    elif len(args) == 2:
        file_path = args[1]
        encoding = 'auto'
    else:
        print("Usage:\npython generate_dict.py [input_file_path] [encoding=auto]")
        return 1

    file_list = []
    if os.path.isfile(file_path):
        file_list.append(file_path)
    else:
        for path, _, files in os.walk(file_path):
            for file in files:
                file_list.append(path + os.sep + file)

    data = process_files(file_list, encoding)
    assert len(data) != 0

    mecab_dict = process_data(data)
    with open('mecab_dict.pickle', 'wb') as f:
        pickle.dump(mecab_dict, f)
    print(f"dictionary saved at {os.curdir}{os.sep}mecab_dict{os.extsep}pickle")


if __name__ == '__main__':
    main(sys.argv)
