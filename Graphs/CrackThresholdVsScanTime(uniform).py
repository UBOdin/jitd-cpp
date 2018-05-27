# importing the required module

import matplotlib.pyplot as plt
import numpy as np
# x axis values

#xi = [i for i in range(0, len(x))]
# corresponding y axis values
f = plt.figure(1)
x = np.array([100000, 1000000, 10000000, 100000000, 1000000000])
y_j = np.array([645476,503720,476443,365710,327390])
y_m =np.array([421605,329808,408730,327256,392719])
# plotting the points
plt.plot(x, y_j, marker = 'o', label='JITD')
plt.plot(x, y_m, marker = 'o',label = 'MAP')
plt.xscale('log')
plt.xlim(10000,10000000000)
plt.ylim(10000,700000)
# naming the x axis
plt.xlabel('Crack Threshold')
# naming the y axis
plt.ylabel('Scan Time(micro sec)')
#plt.xticks(xi, x)
# giving a title to my graph
plt.title('Uniform Workload')
plt.legend(loc='upper right', fancybox=True, framealpha=0.5, frameon=False)
plt.show()
font = {'family' : 'Times New Roman',
        'size'   : 8}
f.savefig("/Users/darshanabalakrishnan/Desktop/JITD-ICDE-2018/CrackThresholdVsScanTime(Uniform).pdf",dpi = '300', bbox_inches='tight', format = 'pdf',transparent= 'true')