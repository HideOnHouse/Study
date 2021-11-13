import pickle
from sklearn.feature_extraction.text import CountVectorizer, TfidfTransformer, TfidfVectorizer
import os
import re
import pandas as pd
from sklearn.metrics.pairwise import cosine_similarity

from tqdm.notebook import tqdm, trange



def find_top5(movie_id: int, rating_df):
    key_rating = rating_df['document'].iloc[movie_id]
    ret = cosine_similarity(key_rating, rating_df)[0]
    top_5_idx = sorted([i for i in range(len(ret))], key=lambda x: ret[x], reverse=True)[:5]
    return top_5_idx


def main():
    df_train = pd.read_csv('./ratings_train.txt', sep='\t')
    df_train = df_train.dropna(axis=0)
    original_train = df_train['document'].to_list()
    df_train['document'] = [*map(tokenize, df_train['document'])]
    df_train.to_csv('processed_ratings_train.csv', sep='\t')
    df_train['id'] = df_train.pop('label')
    df_train.rename(columns={'id': 'label'})
    doc_train = df_train['document'].to_list()
    vectorizer = TfidfVectorizer()
    v_train = vectorizer.fit_transform(doc_train)
    df_test = pd.read_csv('ratings_test.txt', sep='\t')
    df_test = df_test.dropna(axis=0)
    original_test = df_test['document'].to_list()
    df_test['document'] = [*map(tokenize, df_test['document'])]
    df_test.to_csv('processed_ratings_test.csv', sep='\t')
    df_test['id'] = df_test.pop('label')
    df_test.rename(columns={'id': 'label'})
    doc_test = df_test['document'].to_list()
    v_test = vectorizer.transform(doc_test)


if __name__ == '__main__':
    main()
