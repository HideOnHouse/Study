# SVM light example1.tar.gz 데이터를 scikit-learn의 SVM, NB, MLP로 실험한 것임
# 아래 소스는 김택현(국민대, 영문과)군이 구현한 것을 수정하였음
# 2020년 11월 국민대학교 소프트웨어학부 강승식
from sklearn.metrics import accuracy_score
from sklearn import svm
import numpy as np
import time

def load_file(filename):	# loading train.dat, test.dat
    f = open(filename)
    file = f.readlines()
    dlist = []
    for d in file:
        dlist.append(d.strip().split(" "))
    del dlist[0] # 첫 번째 라인(코멘트) 삭제
    return dlist

def target_list(dlist):	# extract targets for each data
    target = []    # category list -- 첫 행 label 추출: +1 또는 -1
    for i in range(len(dlist)):
        target.append(int(dlist[i][0]))
    return target

def docvec_list(dlist, n):	# document vectors
    # Data format conversion: [id:val, id:val, ...] --> [val1, val2, ...]
    # id:value 포맷을 dv[docid][id] = value 형태로 변환
    dv = np.zeros((len(dlist), n))    # doc. vector 초기화 -- n(2000/600) x 9947
    for i in range(len(dlist)):
        for e in range(1, len(dlist[i])): # 첫행 target label 무시
            tmp = dlist[i][e].split(":")
            feature_num = tmp[0]
            feature_val = tmp[1]
            dv[i][int(feature_num)-1] = feature_val
    return dv

train_doc = load_file('./example1/train.dat') # SVM train data -- 2,000개
X_train = docvec_list(train_doc, 9947)
y_train = target_list(train_doc)

test_doc = load_file('./example1/test.dat') # SVM test data -- 600개
X_test = docvec_list(test_doc, 9947)
y_test = target_list(test_doc)

print('분류기 엔진의 정확도 비교 -- 학습데이터 SVM light의 example1.tar.gz')
print('<참고> SVM 엔진 실험하려면... #6 앞의 exit()문을 코멘트 처리하면 됨!\n')

# 1. Naive Bayes 분류기 실험
from sklearn.naive_bayes import GaussianNB
gnb = GaussianNB()
y_pred = gnb.fit(X_train, y_train).predict(X_test)
print("NB 정확도 -- {0:.4f}".format(accuracy_score(y_test, y_pred)))
print("\tNumber of mislabeled points out of %d points : %d" %(X_test.shape[0],(y_test != y_pred).sum()))

# 2. Decision Tree 분류기 실험
from sklearn import tree 
clf = tree.DecisionTreeClassifier() 
y_pred = clf.fit(X_train, y_train).predict(X_test)
print("Decision Tree 정확도 -- {0:.4f}".format(accuracy_score(y_test, y_pred)))
print("\tNumber of mislabeled points out of %d points : %d" %(X_test.shape[0],(y_test != y_pred).sum()))

# 3. Random Forest 분류기 실험
from sklearn.ensemble import RandomForestClassifier

clf = RandomForestClassifier(max_depth=6, random_state=0)
y_pred = clf.fit(X_train, y_train).predict(X_test)
print("Random Forest 정확도 -- {0:.4f}".format(accuracy_score(y_test, y_pred)))
print("\tNumber of mislabeled points out of %d points : %d" %(X_test.shape[0],(y_test != y_pred).sum()))

# 4. Logistic Regression 분류기 실험
from sklearn.linear_model import LogisticRegression

clf = LogisticRegression(random_state=0, max_iter=500)
y_pred = clf.fit(X_train, y_train).predict(X_test)
print("Logistic Regression 정확도 -- {0:.4f}".format(accuracy_score(y_test, y_pred)))
print("\tNumber of mislabeled points out of %d points : %d" %(X_test.shape[0],(y_test != y_pred).sum()))

# 5. Multi-layer Perceptron (MLP) 분류기 실험
from sklearn.neural_network import MLPClassifier 
clf = MLPClassifier(solver='lbfgs', alpha=1e-5, hidden_layer_sizes=(5, 2), random_state=1) 
clf.fit(X_train, y_train) 
y_pred = clf.predict(X_test)

[coef.shape for coef in clf.coefs_] 	# clf.coefs_ -- weight matrices
print("MLP 정확도 -- {0:.4f}".format(accuracy_score(y_test, y_pred)))
print("\tNumber of mislabeled points out of %d points : %d" %(X_test.shape[0],(y_test != y_pred).sum()))

exit()

# 6. SVM 분류기 실험
start_time = time.time()
clf = svm.SVC(gamma='scale')

print("SVM 모델 학습 중...")
clf.fit(X_train, y_train)
end_time = time.time()
print("SVM 모델 학습에 걸린 시간 -- {}초".format(round(end_time - start_time)))

y_pred = clf.predict(X_test)
print("SVM 정확도 -- {0:.4f}".format(accuracy_score(y_test, y_pred)))
print("\tNumber of mislabeled points out of %d points : %d" %(X_test.shape[0],(y_test != y_pred).sum()))
