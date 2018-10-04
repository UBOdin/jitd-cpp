# importing the required module

import matplotlib.pyplot as plt
import numpy as np
# x axis values

#xi = [i for i in range(0, len(x))]
# corresponding y axis values
f = plt.figure(1)
x = np.array([100000, 1000000, 10000000, 100000000, 1000000000])
y_j = np.array([599482.0,446773.0,428990.0,372912.0,288356.0])
y_j = y_j /100000.0
y_m =np.array([321695.0,416301.0,315340.0,437716.0,334322.0])
y_m = y_m /100000.0
# plotting the points
plt.plot(x, y_j, marker = 'o', label='JITD')
plt.plot(x, y_m, marker = 'o',label = 'MAP')
plt.xscale('log')
# plt.xlim(10000,10000000000)
# plt.ylim(10000,700000)
# naming the x axis
plt.xlabel('Crack Threshold')
# naming the y axis
plt.ylabel('Time for one Scan(micro sec)')
#plt.xticks(xi, x)
# giving a title to my graph
plt.title('HeavyHitter Workload')
plt.legend(loc='upper right', fancybox=True, framealpha=0.5, frameon=False)
plt.show()
font = {'family' : 'Times New Roman',
        'size'   : 8}
f.savefig("/Users/darshanabalakrishnan/GitRepo/JITD_ICDE_2018F/jitd-cpp/Graphs/CrackThresholdVsScanTime_HeavyHitter.pdf",dpi = '300', bbox_inches='tight', format = 'pdf',transparent= 'true')