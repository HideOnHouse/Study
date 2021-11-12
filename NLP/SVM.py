# https://scikit-learn.org/stable/modules/svm.html

from sklearn import svm
X = [[0, 0], [1, 1]]	# feature vectors for training data
y = [0, 1]		# labels for training data

clf = svm.SVC(gamma='scale')# model selection
clf.fit(X, y) 		# training
clf.predict([[2., 2.]])		# running for test data