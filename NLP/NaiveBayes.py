# https://scikit-learn.org/stable/modules/naive_bayes.html
# Iris dataset -- https://en.wikipedia.org/wiki/Iris_flower_data_set

from sklearn import datasets
from sklearn.naive_bayes import GaussianNB
iris = datasets.load_iris()
gnb = GaussianNB()
y_pred = gnb.fit(iris.data, iris.target).predict(iris.data)
print("Number of mislabeled points out of a total %d points : %d" %(iris.data.shape[0],(iris.target != y_pred).sum()))