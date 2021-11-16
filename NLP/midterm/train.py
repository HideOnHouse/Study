import os.path
import pickle
import sys

import pandas as pd
from sklearn.feature_extraction.text import TfidfVectorizer
from tqdm import tqdm

from utils import *


def main(args):
    if len(args) == 2:
        train_file_path = args[1]
    elif len(args) == 1:
        train_file_path = f"{os.curdir}{os.sep}ratings_train{os.extsep}txt"
    else:
        print("Invalid Argument")
        return 1
    df_train = pd.read_csv(train_file_path, sep='\t')

    # 유효하지 않은 행 삭제
    df_train = df_train.dropna(axis=0)

    # 각 문서를 토큰화
    print("Tokenization...")
    df_train['document'] = [*map(tokenize, df_train['document'])]
    doc_train = df_train['document'].to_list()
    doc_label = df_train['label'].to_list()
    df_train[['label', 'document']].to_csv("train_tok.csv", sep='\t', index=False)

    # 각 라인을 문서로 간주하여 문서벡터 구성
    print("Vectorization...")
    vectorizer = TfidfVectorizer()
    v_train = vectorizer.fit_transform(doc_train)

    # Word of bag 저장
    with open("vectorizer.pickle", 'wb') as f:
        pickle.dump(vectorizer, f)

    # SVM 데이터 (example1/train.dat)과 동일한 포맷으로 만들어주는 부분
    result = v_train.todok().items()
    result = sorted(result, key=lambda x: x[0][0])

    # 문서벡터를 파일로 출력
    print("Writing Vector...")
    with open("test.dat", 'w', encoding='utf-8') as f:
        temp = []
        row = 0
        for i in tqdm(result):
            if i[0][0] == row:
                temp.append(f'{i[0][1]}:{i[1]}')
            else:
                f.write(f"{1 if doc_label[row] == 0 else -1} " + " ".join(temp) + '\n')
                row += 1
                temp.clear()
        if len(temp) != 0:
            f.write(f"{1 if doc_label[row] == 0 else -1} " + " ".join(temp) + '\n')
    print(f"Train vector saved at {os.curdir}{os.sep}{train_file_path.rsplit(os.extsep, maxsplit=1)[0]}{os.extsep}dat")


if __name__ == '__main__':
    main(sys.argv)
