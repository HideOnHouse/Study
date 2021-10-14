import os
import pickle

if __name__ == '__main__':

    dict_path = f"{os.curdir}{os.sep}mecab_dict{os.extsep}pickle"

    with open(dict_path, 'rb') as f:
        temp = pickle.load(f)
    temp['tail_suffix'].add('하다')
    temp['tail_suffix'].add('했다')
    temp['tail_suffix'].add('한다면')
    temp['tail_eomi'].add('었다')
    temp['tail_eomi'].add('고는')

    with open(dict_path, 'wb') as f:
        pickle.dump(temp, f)
