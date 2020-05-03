import numpy as np
import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt
from scipy import stats

data = pd.read_csv('result3A.txt',header=None,sep=" ",engine='python')
data1 = pd.read_csv('result3B.txt',header=None,sep=" ",engine='python')
sns.set_context("poster",font_scale=.6)
g = sns.distplot(data1[0],bins=250,kde=True,kde_kws={'color':'red','shade':True,'linewidth':1},hist_kws={'rwidth':0.8},color='#00008b')
plt.title('Round Trip Time', fontsize=20)
plt.xlabel('RTT (ms)', fontsize=16)
plt.ylabel('Frequency', fontsize=16)
plt.show()
