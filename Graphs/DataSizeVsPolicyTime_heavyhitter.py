# importing the required module

import matplotlib.pyplot as plt
import numpy as np
# x axis values

#xi = [i for i in range(0, len(x))]
# corresponding y axis values
f = plt.figure(1)
x = np.array([100000, 1000000, 10000000, 100000000, 1000000000])
y_j = np.array([50871.0,887632.0,1.22753e+07,1.56416e+08,1.91023e+09])
y_m =np.array([128381.0,1.26236e+06,1.84246e+07,2.63954e+08,3.77703e+09])
# plotting the points
plt.plot(x, y_j, marker = 'o', label='JITD')
plt.plot(x, y_m, marker = 'o',label = 'MAP')
plt.xscale('log')
plt.yscale('log')
# naming the x axis
plt.xlabel('Data size')
# naming the y axis
plt.ylabel('TransformationTime(micro sec)')
#plt.xticks(xi, x)
# giving a title to my graph
plt.title('HeavyHitter Workload')
plt.legend(loc='upper right', fancybox=True, framealpha=0.5, frameon=False)
plt.show()
font = {'family' : 'Times New Roman',
        'size'   : 8}
f.savefig("/Users/darshanabalakrishnan/GitRepo/JITD_ICDE_2018F/jitd-cpp/Graphs/DataSizeVsPolicyTime_HeavyHitter.pdf",dpi = '300', bbox_inches='tight', format = 'pdf',transparent= 'true')