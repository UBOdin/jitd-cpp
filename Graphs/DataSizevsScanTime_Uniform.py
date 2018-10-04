
import matplotlib.pyplot as plt
import numpy as np
f = plt.figure(1)
x = np.array([100000, 1000000, 10000000, 100000000, 1000000000])
y_j = np.array([103954.0,177180.0,277329.0,411596.0,634574.0])
y_m = np.array([65081.0,112756.0,165981.0,255338.0,390288.0])
y_j = y_j/100000.0
y_m = y_m/100000.0
plt.plot(x, y_j/1000000, marker = 'o',label = 'CrackThreshold10^5')
plt.plot(x, y_m/1000000, marker = 'o',label = 'MAP')
plt.xscale('log')
plt.yscale('log')
plt.xlabel('Data size')

plt.ylabel('Time for one Lookup(sec)')

plt.legend(loc='upper right', fancybox=True, framealpha=0.1, frameon=False)
plt.show()
font = {
#    'family' : 'Times New Roman',
  'size'   : 12
}
plt.rc('font', **font)
f.savefig("/Users/darshanabalakrishnan/GitLab/Paper-JITD-ICDE2108/DataSizeVsScanTime_Uniform.pdf", bbox_inches='tight', format = 'pdf',transparent= 'true')