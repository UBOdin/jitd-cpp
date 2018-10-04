# importing the required module

import matplotlib.pyplot as plt
import numpy as np
# x axis values

#xi = [i for i in range(0, len(x))]
# corresponding y axis values
f = plt.figure(1)
x = np.array([100000, 1000000, 10000000, 100000000, 1000000000])
y_j = np.array([100404.0,165187.0,258946.0,368379.0,587929.0])
y_m =np.array([67472.0,106654.0,158990.0,247015.0,331953.0])
# plotting the points
plt.plot(x, y_j/100000.0, marker = 'o', label='JITD')
plt.plot(x, y_m/100000.0, marker = 'o',label = 'MAP')
plt.xscale('log')

# naming the x axis
plt.xlabel('Data size')
# naming the y axis
plt.ylabel('Time for one scan(micro sec)')
#plt.xticks(xi, x)
# giving a title to my graph
plt.title('HeavyHitter Workload')
plt.legend(loc='upper right', fancybox=True, framealpha=0.5, frameon=False)
plt.show()
font = {'family' : 'Times New Roman',
        'size'   : 8}
f.savefig("/Users/darshanabalakrishnan/GitRepo/JITD_ICDE_2018F/jitd-cpp/Graphs/DataSizeVsScanTime_HeavyHitter.pdf",dpi = '300', bbox_inches='tight', format = 'pdf',transparent= 'true')