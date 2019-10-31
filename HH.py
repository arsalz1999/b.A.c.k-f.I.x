import numpy as np
import math
import matplotlib.pyplot as plt
from matplotlib.patches import Polygon
from matplotlib.collections import PatchCollection
import matplotlib.animation as animation
import time

data = np.genfromtxt('myFile.txt', delimiter=',')


for list in data: # Each list in full set

    plt.figure()
    left = int(list[0])
    right = int(list[1])
    bottom = int(list[2])
    if left < 0:
        left = abs(left)
    if right < 0:
        right = abs(right)
    if bottom < 0:
        bottom = abs(bottom)

    a = 700
    b = 700
    c = 700
    m = 350
    i = math.sqrt(3)/2

    X = np.array([[m, m-c], [m-i*a,m+0.5*a], [m+i*b, m+0.5*b], [m, m-bottom], [m-i*left,m+0.5*left], [m+i*right, m+0.5*right]])
    Y = ['#ff9999', '#ccccff', 'red', 'blue', 'blue', 'blue']
    plt.figure()
    plt.scatter(X[:, 0], X[:, 1], s = 0, color = Y[:])

    t_inner = plt.Polygon(X[:3,:], color=Y[1])
    plt.gca().add_patch(t_inner)

    t_threshold = plt.Polygon(X[3:6,:], color=Y[0])
    plt.gca().add_patch(t_threshold)
    plt.show()
