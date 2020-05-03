import pandas as pd
import numpy as np

data = pd.read_csv('result3B.txt',header=None,sep=" ",engine='python')
print(f'Maximum : {np.max(data[0]):.3f}')
print(f'Minimum : {np.min(data[0]):.3f}')
print(f'Mean : {np.mean(data[0]):.3f}')
print(f'Median : {np.median(data[0]):.3f}')
print(f'Standard Deviation : {np.std(data[0]):.3f}')
