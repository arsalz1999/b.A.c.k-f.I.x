import numpy as np 
import matplotlib.pyplot as plt

xc = 5
yc = 7



X = np.array([[5,2], [1,9], [9, 9], [xc+a,xy+a], [xc+b,xy+b], [7+c, 8+c]])
Y = ['red', 'red', 'red', 'blue', 'blue', 'blue']

plt.figure()
plt.scatter(X[:, 0], X[:, 1], s = 170, color = Y[:])

t1 = plt.Polygon(X[:3,:], color=Y[0])
plt.gca().add_patch(t1)

t2 = plt.Polygon(X[3:6,:], color=Y[3])
plt.gca().add_patch(t2)


plt.show()
