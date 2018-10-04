# importing the required module

import matplotlib.pyplot as plt
import numpy as np
# x axis values

#xi = [i for i in range(0, len(x))]
# corresponding y axis values
f = plt.figure(1)
x = np.array([100000, 1000000, 10000000, 100000000, 1000000000])
y_j = np.array([28,30,32,29,36])
y_m =np.array([3.91E+09,3.83E+09,3.93E+09,3.54E+09,3.93E+09])
# plotting the points
plt.plot(x, y_j, marker = 'o', label='JITD')
plt.plot(x, y_m, marker = 'o',label = 'MAP')
plt.xscale('log')
plt.yscale('log')
# plt.xlim(10000,10000000000)
# plt.ylim(10,10000000000)
# naming the x axis
plt.xlabel('Crack Threshold')
# naming the y axis
plt.ylabel('Load Time(micro sec)')
#plt.xticks(xi, x)
# giving a title to my graph
plt.title('Uniform Workload')
plt.legend(loc='upper right', fancybox=True, framealpha=0.5, frameon=False)
plt.show()
font = {'family' : 'Times New Roman',
        'size'   : 8}
f.savefig("/Users/darshanabalakrishnan/GitRepo/JITD_ICDE_2018F/jitd-cpp/Graphs/CrackThresholdVsLoadTime_Uniform.pdf",dpi = '300', bbox_inches='tight', format = 'pdf',transparent= 'true')