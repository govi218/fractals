import math
import numpy as np
import h5py
import matplotlib.pyplot as plt
from matplotlib.pyplot import grid, imread
import scipy
from PIL import Image
import pandas as pd
import tensorflow as tf
import tensorflow.keras.layers as tfl
from tensorflow.python.framework import ops
import re
from sklearn.model_selection import train_test_split
from multiprocessing import Pool

# %matplotlib inline
np.random.seed(1)

grid_set = pd.read_csv("grid_set_small.txt")

m_set = pd.read_csv("m_set_small.txt")

grid_set['i'] = grid_set['i'].astype(float)
grid_set['j'] = grid_set['j'].astype(float) 

m_set['i'] = m_set['i'].astype(float)
m_set['j'] = m_set['j'].astype(float) 

# adding column with constant value
grid_set['m_set_member'] = pd.Series([0 for x in range(len(grid_set.index))])
m_set['m_set_member'] = pd.Series([1 for x in range(len(m_set.index))])

# grid_set = pd.merge(grid_set, m_set, how='left')

grid_set.update(m_set)

# print(m_set)
# print(m_set.loc[m_set['m_set_member']==1.0])
# print(grid_set.loc[grid_set['m_set_member']==1.0])
# print(grid_set)
# print(len(m_set))

grid_set = grid_set.to_numpy()
# m_set = m_set.to_numpy()

print(grid_set)
# print(m_set)


# labeled_set = np.zeros(shape=(len(grid_set),3))
# print(labeled_set)


# pool = Pool(processes=8)

# # labeled_set = pool.map(for_loop, [grid_set, m_set, labeled_set])

# for i in range(len(grid_set)):
#         if(i%10000 == 0):
#             print(i)
#         if(grid_set[i] in m_set):
#             labeled_set[i] = (np.append(grid_set[i], 1))
#             np.delete(m_set, np.argwhere(m_set == grid_set[i]))
#         else:
#             labeled_set[i] = (np.append(grid_set[i], 0))

# print(labeled_set)

X_train, X_test, y_train, y_test = train_test_split(grid_set[:,:2], grid_set[:,2], test_size=0.1, random_state=33)





# print((labeled_set[:,2]))

