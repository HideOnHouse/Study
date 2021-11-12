import pickle
import sys

import pandas as pd

from utils import *


def find_top5(target_vector, train_vectors):
    result = []
    for idx, i in enumerate(train_vectors):
        result.append((idx, cosine_similarity(target_vector, i)))
    result = sorted(result, key=lambda x: x[1], reverse=True)
    return [i[0] for i in result[:5]]


def main(args):
    # i 값을 sys.argv[1]로 받음
    target_idx = int(args[1])
    train_vectors = []

    # 유사한 영화평을 찾기 위해 문서 벡터를 읽음
    with open("train.dat", 'r') as f:
        for line in f:
            line = line.strip().split(" ")
            label, temp = line[0], line[1:]
            vector = dict()
            for i in temp:
                i = i.split(':')
                vector[int(i[0])] = float(i[1])
            train_vectors.append(vector)

    # 문서들을 읽어옴
    df_train = pd.read_csv('./ratings_train.txt', sep='\t')
    df_train = df_train.dropna(axis=0)
    df_test = pd.read_csv('./ratings_test.txt', sep='\t')
    df_test = df_test.dropna(axis=0)

    # 사용자가 원하는 문서를 선택
    target = df_test.iloc[target_idx]
    doc_target, label_target = target['document'], target['label']

    # 사용자가 원하는 문서를 토큰화
    target_tok = tokenize(doc_target)
    with open("test_tok.csv", 'w') as f:
        for idx, i in enumerate(target_tok):
            f.write(f"{idx},{i}\n")
    with open("vectorizer.pickle", 'rb') as f:
        vectorizer = pickle.load(f)

    # 토근화된 문서를 벡터화한 후에 문서 벡터로 구성
    v_test = vectorizer.transform([target_tok])
    temp = v_test.todok().items()
    vector = dict()
    for i, j in temp:
        vector[i[1]] = j

    # 가장 유사한 5개의 영화평을 찾음
    top_idx = find_top5(vector, train_vectors)

    # 결과 출력
    print("original text: " + df_test['document'].iloc[target_idx])
    temp = [0, 0]
    for idx, i in enumerate(top_idx):
        label = df_train["label"].iloc[i]
        temp[label] += 1
        text = df_train['document'].iloc[i]
        print(f'# {idx}\n{text}')
    print(f"result: {'positive' if temp[0] <= temp[1] else 'negative'}, 0:{temp[0]}, 1:{temp[1]}")


if __name__ == '__main__':
    main(sys.argv)
