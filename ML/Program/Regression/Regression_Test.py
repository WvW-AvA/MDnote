# _*_coding:utf-8_*_
from datetime import date
from typing import List
import warnings
from matplotlib import colors
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from pandas.core.construction import array
import sympy as sym
import openpyxl

# 数据读入
source = pd.read_csv('train.csv', index_col='Type')
source[source == 'NR'] = 0
source = source.to_numpy()  # 转化为数据集合

# 数据预处理，将同项挪到一行上，并分月收集
month_date = {}
for month in range(12):
    sample = np.empty([18, 480])  # 生成空容器
    for day in range(20):
        sample[:, day*24:(day+1)*24] = source[month*20*18 +
                                              day*18:month*20*18+(day+1)*18, 1:25]
    month_date[month] = sample

# 取PM2.5这一项的第一个月的前19天数据进行回归分析
# x每一行为一组前9小时的数据，共有（12*20*24-9）行
# y为所有第10小时PM2.5的数据，共一列
x = np.empty([471*12, 18*9], dtype=float)
y = np.empty([471*12, 1], dtype=float)
for month in range(12):
    for day in range(20):
        for hour in range(24):
            if day == 19 and hour > 14:
                continue
            x[month*471+day*24+hour,
                :] = np.reshape(month_date[month][:, day*24+hour:day*24+hour+9], [1, -1])
            y[month*471+day*24+hour, 0] = month_date[month][9, day*24+hour+9]
print(x)
print(y)

# 数据标准化Normalize
# x的列为不同类型的数据，其数量级差距较大，会影响权重，故将其标准化
# 矩阵标准化的公式为x=(x-mean)/std
mean_x = np.mean(x, axis=0)
std_x = np.std(x, axis=0)
for i in range(len(x)):
    for j in range(len(x[0])):
        if std_x[j] != 0:
            x[i][j] = (x[i][j]-mean_x[j])/std_x[j]

x = np.concatenate((np.ones([471*12, 1]), x), axis=1).astype(float)
out = np.empty([18*9+1, 20])
for k in range(20):
    # Gradient Descent
    w = np.zeros([18*9+1, 1])
    adagrad = np.zeros([18*9+1, 1])
    learning_rate = 10*k
    liter_time = 2000
    esp = 0.00000000001
    for i in range(liter_time):
        if(i % 200 == 0):
            Loss = np.sqrt(np.sum(np.power(y-np.dot(x, w), 2))/471/12)
            print('Loss'+str(i/200)+'='+str(Loss))
        grad = 2*np.dot(np.transpose(x), (np.dot(x, w)-y))
        adagrad += grad**2
        w = w-learning_rate*grad/np.sqrt(adagrad+esp)
    # print(w)
    out[:, k] = w[:, 0]

excel_date = pd.DataFrame(out)
writer = pd.ExcelWriter("D:\Program\PyTest\output.xlsx")
excel_date.to_excel(writer, 'output1', float_format='%f', index=False)
writer.save()
writer.close()
