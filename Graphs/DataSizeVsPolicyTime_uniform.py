# importing the required module

import matplotlib.pyplot as plt
import numpy as np
# x axis values

#xi = [i for i in range(0, len(x))]
# corresponding y axis values
f = plt.figure(1)
x = np.array([100000, 1000000, 10000000, 100000000, 1000000000])
y_j = np.array([50464.0,898727.0,1.19542e+07,1.61546e+08,2.0254e+09])
y_m =np.array([125742.0,1.25393e+06,1.82513e+07,2.60381e+08,3.8807e+09])
# plotting the points
plt.plot(x, y_j/1000000, marker = 'o', label='CrackThreshold10^5')
plt.plot(x, y_m/1000000, marker = 'o',label = 'MAP')
plt.xscale('log')
plt.yscale('log')
# naming the x axis
plt.xlabel('Data size')
# naming the y axis
plt.ylabel('TransformationTime(sec)')

plt.legend(loc='upper right', fancybox=True, framealpha=0.1, frameon=False)
plt.show()
font = {
#    'family' : 'Times New Roman',
  'size'   : 12
}
plt.rc('font', **font)
f.savefig("/Users/darshanabalakrishnan/GitLab/Paper-JITD-ICDE2108/DataSizeVsPolicyTime_Uniform.pdf", bbox_inches='tight', format = 'pdf',transparent= 'true')