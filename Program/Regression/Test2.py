import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from pandas.core.algorithms import mode
import sympy as sym
import os
test = pd.read_csv('test.csv')
test[test == 'NR'] = 0
test = test.to_numpy()

t = np.empty([20, 18*9+1])
for k in range(20):
    t[k, 0] = 1
    t[k, 1:18*9+1] = np.reshape(test[k*18:(k+1)*18, 2:], (1, -1))


model = pd.read_excel('output.xlsx')
model = model.to_numpy()


result = np.dot(t, model)

print(result)
result = pd.DataFrame(result)
writer = pd.ExcelWriter('D:\Program\PyTest\outputResult.xlsx')
result.to_excel(writer, "result1", float_format='%f', index=False)
writer.save()
writer.close()
