# importing the required module

import matplotlib.pyplot as plt
import numpy as np
# x axis values

#xi = [i for i in range(0, len(x))]
# corresponding y axis values
f = plt.figure(1)
x = np.array([100000, 1000000, 10000000, 100000000, 1000000000])
y_j = np.array([100404,165187,258946,368379,587929])
y_m =np.array([67472,106654,158990,247015,331953])
# plotting the points
plt.plot(x, y_j, marker = 'o', label='JITD')
plt.plot(x, y_m, marker = 'o',label = 'MAP')
plt.xscale('log')
plt.xlim(10000,10000000000)
plt.ylim(10000,700000)
# naming the x axis
plt.xlabel('Data size')
# naming the y axis
plt.ylabel('Scan Time')
#plt.xticks(xi, x)
# giving a title to my graph
plt.title('HeavyHitter Workload')
plt.legend(loc='upper right', fancybox=True, framealpha=0.5, frameon=False)
plt.show()
font = {'family' : 'Times New Roman',
        'size'   : 8}
f.savefig("/Users/darshanabalakrishnan/Desktop/JITD-ICDE-2018/DataSizeVsScanTime(HeavyHitter).pdf",dpi = '300', bbox_inches='tight', format = 'pdf',transparent= 'true')