# importing the required module

import matplotlib.pyplot as plt
import numpy as np
# x axis values

#xi = [i for i in range(0, len(x))]
# corresponding y axis values
f = plt.figure(1)
x = np.array([100000,1000000,10000000, 100000000, 1000000000])
y_j = np.array([645476.0,503720.0,476443.0,365710.0,327390.0])
y_m =np.array([421605.0,329808.0,408730.0,327256.0,392719.0])
y_j = y_j /100000.0
y_m = (np.sum(y_m)/5)/100000.0

# plotting the points
plt.plot(x, y_j, marker = 'o', label='Just-In-Time-Index',color = 'b')
#plt.plot(x, y_m, marker = 'o',label = 'MAP')
plt.axhline(y = y_m,marker = 'o',label = 'MAP',color = 'g')
plt.xscale('log')

# naming the x axis
plt.xlabel('Crack Threshold')
# naming the y axis
plt.ylabel('Time for one Lookup(micro sec)')
#plt.xticks(xi, x)
# giving a title to my graph
plt.title('Uniform Workload')
plt.legend(loc='upper right', fancybox=True, framealpha=0.1, frameon=False)
plt.show()
font = {
#    'family' : 'Times New Roman',
  'size'   : 12
}
plt.rc('font', **font)
f.savefig("/Users/darshanabalakrishnan/GitLab/Paper-JITD-ICDE2108/CrackThresholdVsScanTime_Uniform.pdf", bbox_inches='tight', format = 'pdf',transparent= 'true')