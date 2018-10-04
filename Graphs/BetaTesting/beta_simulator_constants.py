import matplotlib.pyplot as plt
import numpy as np
import math
# f = plt.figure(1)
data_size = np.array([10**m for m in [5, 6, 7, 8, 9]])
data_size_nlogn = np.array([(100000*math.log(100000,2)),(1000000*math.log(1000000,2)),(10000000*math.log(10000000,2)),(100000000*math.log(100000000,2)),(1000000000*math.log(1000000000,2))])
sort_time5 = np.array([95138,51350,51271,51345,51115])

sort_time9 = np.array([8.97209e+08,8.94671e+08,8.98395e+08,8.93895e+08,8.93729e+08])
sort_mul5 = (np.mean(sort_time5))
sort_mul9 = (np.mean(sort_time9))
print "the sort multipliers are: "
print sort_mul5
plt.show(data_size_nlogn,sort_time5)
print sort_mul9


crack_time5 = np.array([19331,19746,8544,19965,8416])

crack_time9 = np.array([8.68508e+07,8.52197e+07,8.51958e+07,8.51113e+07,8.54735e+07])
crack_mul5 = (np.mean(crack_time5))

crack_mul9 = (np.mean(crack_time9))
print "the crack multipliers are: "
print crack_mul5

print crack_mul9
#print crack_mul9/(10**9)

data_size_logn = np.array([(math.log(100000,2)),(math.log(1000000,2)),(math.log(10000000,2)),(math.log(100000000,2)),(math.log(1000000000,2))])
sorted_scan_time5 = np.array([972193,965562,962995,1.00477e+06,974042,5])

sorted_scan_time9 = np.array([3.12556e+06,3.10865e+06,3.12824e+06,3.36017e+06,3.09947e+06])
sort_scan_mul5 = (np.mean(sorted_scan_time5))/1000000

sort_scan_mul9 = (np.mean(sorted_scan_time9))/1000000
print "the sort scan multipliers are: "
print sort_scan_mul5

print sort_scan_mul9


unsorted_scan_time5 = np.array([2764,1107,1106,1145,1106])

unsorted_scan_time9 = np.array([1.16991e+07,1.15459e+07,1.15269e+07,3.01204e+06,4.58668e+06])
unsort_scan_mul5 = (np.mean(unsorted_scan_time5))

unsort_scan_mul9 = (np.mean(unsorted_scan_time9))
print "the unsort scan multipliers are: "
print unsort_scan_mul5

print unsort_scan_mul9

# print "the variemce of the scan unsort multipliers are:"
# print np.var(np.array([unsort_scan_mul5,unsort_scan_mul6,unsort_scan_mul7,unsort_scan_mul8,unsort_scan_mul9]))
# print "the final scan unsorted multiplier is: "
# print (unsort_scan_mul5+unsort_scan_mul6+unsort_scan_mul7+unsort_scan_mul8+unsort_scan_mul9)/5.0

print "Fitting the a + bx model"
print "FOR SORT MULTIPLIER"
b_sort_mul = sort_mul9 / ((10**9) * math.log(10**9, 2))
print b_sort_mul
a_sort_mul = sort_mul5 - (b_sort_mul*((10**5)*math.log((10**5),2)))
print a_sort_mul

print "FOR CRACK MULTIPLIER"
b_crack_mul = crack_mul9 / (10**9)
print b_crack_mul
a_crack_mul = crack_mul5 - (b_crack_mul*((10**5)))
print a_crack_mul
#
print "FOR SCAN SORTED MULTIPLIER"
b_scansort_mul = sort_scan_mul9 / (math.log(10**9, 2))
print b_scansort_mul
a_scansort_mul = sort_scan_mul5 - (b_scansort_mul*(math.log((10**5),2)))
print a_scansort_mul
#
print "FOR SCAN UNSORTED MULTIPLIER"
b_scanunsort_mul = unsort_scan_mul9 / (10**9)
print b_scanunsort_mul
a_scanunsort_mul = unsort_scan_mul5 - (b_scanunsort_mul*((10**5)))
print a_scanunsort_mul

# font = {'family' : 'Times New Roman',
#         'size'   : 8}
# plt.plot(data_size,sort_time,marker = 'o',label = 'Sort Multiplier')
# plt.plot(data_size,crack_time,marker = 'x',label = 'Crack Multiplier')
# plt.plot(data_size,sorted_scan_time,marker = '+',label = 'Scan Sorted Array Multiplier')
# plt.plot(data_size,unsorted_scan_time,marker = '^',label = 'Scan UnSorted Array Multiplier')
#
# plt.xscale('log')
# plt.yscale('log')
#
# plt.xlabel('Data Size')
# plt.ylabel('Time (micro sec)')
#
# plt.legend(loc='best', fancybox=True, framealpha=0.1, frameon=False)
# plt.tight_layout(w_pad= 2.0, h_pad= 0.5)
# f.savefig("/Users/darshanabalakrishnan/GitRepo/JITD_ICDE_2018F/jitd-cpp/Graphs/SimulatorConstants.pdf",dpi = '300', bbox_inches='tight', format = 'pdf',transparent= 'true')
#
# plt.show()