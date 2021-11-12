# Hand-written data : total 1797 x 64
from sklearn import datasets
digits = datasets.load_digits()

from sklearn import svm
clf = svm.SVC(gamma=0.001, C=100.)

X_train = digits.data[:-180]	# train data: except 180
y_train = digits.target[:-180]	# 0~9

X_test = digits.data[-180:]	# test data
y_test = digits.target[-180:]

clf.fit(X_train, y_train)
y_pred = clf.predict(X_test)

print('y_test =', y_test)
print('y_pred =', y_pred)

from sklearn.metrics import accuracy_score
print("SVM accuracy -- {0:.4f}".format(accuracy_score(y_test, y_pred)))
print("\tNumber of mislabeled points out of %d points : %d" %(X_test.shape[0],(y_test != y_pred).sum()))