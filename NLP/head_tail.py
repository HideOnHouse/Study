import os
import pickle
import sys
import re
from konlpy.tag import Mecab


def print_possible(word, mecab, mecab_dict):
    word = re.sub('[^ ㄱ-ㅎ|가-힣+]', "", word)
    temp = mecab.pos(word)
    idx = 0
    head = []
    for i in range(len(temp)):
        if temp[i][1][0] == 'N' or temp[i][1][0] == 'V' or temp[i][1][:2] == 'XP':
            head.append(temp[i][0])
            idx += 1
        else:
            break
    head = "".join(head)
    tail = "".join(i[0] for i in temp[idx:])
    flag = True
    for status in mecab_dict:
        if len(head) != 0 and tail in mecab_dict[status]:
            print(f"{head}/head + {tail}/{status}")
            flag = False
    if flag and len(word) != 0:
        print(word + '/head')


def main(args):
    dict_path = f"{os.curdir}{os.sep}mecab_dict{os.extsep}pickle"
    if len(args) == 1:
        file_path = 'interactive'
    elif len(args) == 2:
        file_path = args[1]
    else:
        print(f"Usage:python head_tail.py [file_path=interactive]")
        return 1

    mecab = Mecab()
    with open(dict_path, 'rb') as f:
        mecab_dict = pickle.load(f)

    if file_path == 'interactive':
        while True:
            words = input('>>>')
            words = words.strip().split(" ")
            for i in words:
                print_possible(i, mecab, mecab_dict)
    else:
        with open(file_path, 'r') as f:
            for line in f:
                words = re.split(r'\s', line.strip())
                for word in words:
                    print_possible(word, mecab, mecab_dict)


if __name__ == '__main__':
    main(sys.argv)
