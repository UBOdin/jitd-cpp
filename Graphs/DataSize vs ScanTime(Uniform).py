
import matplotlib.pyplot as plt
import numpy as np
f = plt.figure(1)
x = np.array([100000, 1000000, 10000000, 100000000, 1000000000])
y_j = np.array([103954,177180,277329,411596,634574])
y_m = np.array([65081,112756,165981,255338,390288])

plt.plot(x, y_j, marker = 'o',label = 'JITD')
plt.plot(x, y_m, marker = 'o',label = 'MAP')
plt.xscale('log')
plt.xlim(10000,10000000000)
plt.ylim(10000,700000)

plt.xlabel('Data size')

plt.ylabel('Scan Time')

plt.title('Uniform Workload')

plt.legend(loc='upper right', fancybox=True, framealpha=0.5, frameon=False)
plt.show()
font = {'family' : 'Times New Roman',
        'size'   : 8}
f.savefig("/Users/darshanabalakrishnan/Desktop/JITD-ICDE-2018/DataSizeVsScanTime(Uniform).pdf",dpi = '300', bbox_inches='tight', format = 'pdf',transparent= 'true')