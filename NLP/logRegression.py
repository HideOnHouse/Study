from sklearn.linear_model import LogisticRegression

from sklearn.datasets import load_iris
X, y = load_iris(return_X_y=True)

clf = LogisticRegression(max_iter=500, random_state=0)
clf.fit(X, y)
print(clf.predict(X[:2, :]))

print(clf.predict_proba(X[:2, :]))
print(clf.score(X, y))