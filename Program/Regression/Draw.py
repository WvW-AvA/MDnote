import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.axes as ax
Date = pd.read_csv('train.csv')
Date = Date.to_numpy()
print(Date)
PM2_5_Date = np.empty([1, 24])
PM2_5_Date = Date[9, 2:]
print(PM2_5_Date)
plt.xlabel("Time/Hours")
plt.ylabel("PM2.5")
X_axis = np.linspace(0, 24, 24, endpoint=False)
plt.scatter(X_axis, PM2_5_Date)
plt.show()
