import matplotlib.pyplot as plt
import numpy as np

f = plt.figure(1)
data_size = np.array([100000,1000000,10000000,100000000,1000000000])
sort_time = np.array([95138,607768,7.08118e+06,8.09438e+07,8.97209e+08])
crack_time = np.array([19331,119520,699197,7.63074e+06,8.68508e+07])
sorted_scan_time = np.array([5,6,21,10,40])
unsorted_scan_time = np.array([2764,18649,116739,1.15708e+06,1.16991e+07])
crack_multiplier = np.sum(crack_time)/5
sort_multiplier = np.sum(sort_time)/5
scan_sorted_multiplier = np.sum(sorted_scan_time)/5
scan_unsorted_multiplier = np.sum(unsorted_scan_time)/5
print crack_multiplier
print sort_multiplier
print scan_sorted_multiplier
print scan_unsorted_multiplier
font = {'family' : 'Times New Roman',
        'size'   : 8}
plt.plot(data_size,sort_time,marker = 'o',label = 'Sort Multiplier')
plt.plot(data_size,crack_time,marker = 'x',label = 'Crack Multiplier')
plt.plot(data_size,sorted_scan_time,marker = '+',label = 'Scan Sorted Array Multiplier')
plt.plot(data_size,unsorted_scan_time,marker = '^',label = 'Scan UnSorted Array Multiplier')

plt.xscale('log')
plt.yscale('log')

plt.xlabel('Data Size')
plt.ylabel('Time (micro sec)')

plt.legend(loc='best', fancybox=True, framealpha=0.1, frameon=False)
plt.tight_layout(w_pad= 2.0, h_pad= 0.5)
f.savefig("/Users/darshanabalakrishnan/GitRepo/JITD_ICDE_2018F/jitd-cpp/Graphs/SimulatorConstants.pdf",dpi = '300', bbox_inches='tight', format = 'pdf',transparent= 'true')

plt.show()