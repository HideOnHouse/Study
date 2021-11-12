# https://scikit-learn.org/stable/modules/tree.html
from sklearn import tree 
X = [[0, 0], [1, 1]] 
Y = [0, 1] 
clf = tree.DecisionTreeClassifier() 
clf = clf.fit(X, Y)
clf.predict([[2., 2.]])

# Iris dataset -- https://en.wikipedia.org/wiki/Iris_flower_data_set
from sklearn.datasets import load_iris
from sklearn import tree
iris = load_iris() 
clf = tree.DecisionTreeClassifier() 
clf = clf.fit(iris.data, iris.target)
clf.predict(iris.data)
tree.plot_tree(clf.fit(iris.data, iris.target)) 
