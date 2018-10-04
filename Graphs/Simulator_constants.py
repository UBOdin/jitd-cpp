import matplotlib.pyplot as plt
import numpy as np
import math
# f = plt.figure(1)
data_size = np.array([10**m for m in [5, 6, 7, 8, 9]])
data_size_nlogn = np.array([(100000*math.log(100000,2)),(1000000*math.log(1000000,2)),(10000000*math.log(10000000,2)),(100000000*math.log(100000000,2)),(1000000000*math.log(1000000000,2))])
sort_time5 = np.array([95138,51350,51271,51345,51115,51107])
sort_time6 = np.array([607768,603817,632805,610467,607882,604454])
sort_time7 = np.array([7.08118e+06,7.09075e+06,7.35898e+06,7.06059e+06,7.06091e+06,7.05835e+06])
sort_time8 = np.array([8.09438e+07,8.00905e+07,8.01518e+07,8.02802e+07,8.00856e+07,8.02071e+07])
sort_time9 = np.array([8.97209e+08,8.94671e+08,8.98395e+08,8.93895e+08,8.93729e+08,8.94171e+08])
sort_mul5 = (np.mean(sort_time5))
sort_mul6 = (np.mean(sort_time6))
sort_mul7 = (np.mean(sort_time7))
sort_mul8 = (np.mean(sort_time8))
sort_mul9 = (np.mean(sort_time9))
print "the sort multipliers are: "
print sort_mul5
print sort_mul6
print sort_mul7
print sort_mul8
print sort_mul9
#print sort_mul9/(10**9)
print "polyfit"
print np.polyfit(data_size_nlogn,np.array([sort_mul5,sort_mul6,sort_mul7,sort_mul8,sort_mul9]),1)
# print "the varience of the  crack multipliers are:"
# print np.var(np.array([sort_mul5,sort_mul6,sort_mul7,sort_mul8,sort_mul9]))
# print "final sort multiplier is: "
# print (sort_mul5 + sort_mul6 +sort_mul7 +sort_mul8+sort_mul9)/5.0

crack_time5 = np.array([19331,19746,8544,19965,8416,8458])
crack_time6 = np.array([119520,119578,110735,89031,89278,120531])
crack_time7 = np.array([699197,690531,691395,691511,691077,691866])
crack_time8 = np.array([7.63074e+06,7.48597e+06,7.46955e+06,7.48229e+06,7.47538e+06,7.48414e+06])
crack_time9 = np.array([8.68508e+07,8.52197e+07,8.51958e+07,8.51113e+07,8.54735e+07,8.52939e+07])
crack_mul5 = (np.mean(crack_time5))
crack_mul6 = (np.mean(crack_time6))
crack_mul7 = (np.mean(crack_time7))
crack_mul8 = (np.mean(crack_time8))
crack_mul9 = (np.mean(crack_time9))
print "the crack multipliers are: "
print crack_mul5
print crack_mul6
print crack_mul7
print crack_mul8
print crack_mul9
#print crack_mul9/(10**9)
print "polyfit"
# #print data_size
print np.polyfit(data_size,np.array([crack_mul5,crack_mul6,crack_mul7,crack_mul8,crack_mul9]),1)
#print np.polyfit(np.array([5,6,7,8,9]),np.array([ math.log(x, 10) for x in [crack_mul5,crack_mul6,crack_mul7,crack_mul8,crack_mul9]]),1)
# print "the varience of the crack multipliers are:"
# print np.var(np.array([crack_mul5,crack_mul6,crack_mul7,crack_mul8,crack_mul9]))
# print "final crack multiplier is: "
# print (crack_mul5+crack_mul6+crack_mul7+crack_mul8+crack_mul9)/5.0
data_size_logn = np.array([(math.log(100000,2)),(math.log(1000000,2)),(math.log(10000000,2)),(math.log(100000000,2)),(math.log(1000000000,2))])
sorted_scan_time5 = np.array([4,3,4,3,4,5])
sorted_scan_time6 = np.array([6,6,6,5,6,7])
sorted_scan_time7 = np.array([20,16,20,19,21,18])
sorted_scan_time8 = np.array([25,26,29,25,24,10])
sorted_scan_time9 = np.array([38,36,39,36,37,37])
sort_scan_mul5 = (np.mean(sorted_scan_time5))
sort_scan_mul6 = (np.mean(sorted_scan_time6))
sort_scan_mul7 = (np.mean(sorted_scan_time7))
sort_scan_mul8 = (np.mean(sorted_scan_time8))
sort_scan_mul9 = (np.mean(sorted_scan_time9))
print "the sort scan multipliers are: "
print sort_scan_mul5
print sort_scan_mul6
print sort_scan_mul7
print sort_scan_mul8
print sort_scan_mul9
print "polyfit"
print np.polyfit(data_size_logn,np.array([sort_scan_mul5,sort_scan_mul6,sort_scan_mul7,sort_scan_mul8,sort_scan_mul9]),1)
# print "the varience of the scan sort multipliers are: "
# print np.var(np.array([sort_scan_mul5,sort_scan_mul6,sort_scan_mul7,sort_scan_mul8,sort_scan_mul9]))
# print "the final scan sorted multiplier is: "
# print (sort_scan_mul5+sort_scan_mul6+sort_scan_mul7+sort_scan_mul8+sort_scan_mul9)/5.0

unsorted_scan_time5 = np.array([2764,1107,1106,1145,1106,1106])
unsorted_scan_time6 = np.array([18649,11498,11406,11469,11399,11414])
unsorted_scan_time7 = np.array([116739,114927,116163,115183,114882,115162])
unsorted_scan_time8 = np.array([1.15708e+06,1.15191e+06,1.15442e+06,1.14627e+06,1.15417e+06,1.15305e+06])
unsorted_scan_time9 = np.array([1.16991e+07,1.15459e+07,1.15269e+07,3.01204e+06,4.58668e+06,1.15251e+07])
unsort_scan_mul5 = (np.mean(unsorted_scan_time5))
unsort_scan_mul6 = (np.mean(unsorted_scan_time6))
unsort_scan_mul7 = (np.mean(unsorted_scan_time7))
unsort_scan_mul8 = (np.mean(unsorted_scan_time8))
unsort_scan_mul9 = (np.mean(unsorted_scan_time9))
print "the unsort scan multipliers are: "
print unsort_scan_mul5
print unsort_scan_mul6
print unsort_scan_mul7
print unsort_scan_mul8
print unsort_scan_mul9
print "polyfit"
print np.polyfit(data_size,np.array([unsort_scan_mul5,unsort_scan_mul6,unsort_scan_mul7,unsort_scan_mul8,unsort_scan_mul9]),1)
# print "the variemce of the scan unsort multipliers are:"
# print np.var(np.array([unsort_scan_mul5,unsort_scan_mul6,unsort_scan_mul7,unsort_scan_mul8,unsort_scan_mul9]))
# print "the final scan unsorted multiplier is: "
# print (unsort_scan_mul5+unsort_scan_mul6+unsort_scan_mul7+unsort_scan_mul8+unsort_scan_mul9)/5.0

# print "Fitting the a + bx model"
# print "FOR SORT MULTIPLIER"
# b_sort_mul = sort_mul9 / (10**9 * math.log(10**9, 2))
# print b_sort_mul
# a_sort_mul = sort_mul5 - b_sort_mul*((10**5)*math.log((10**5),2))
# print a_sort_mul
#
# print "FOR CRACK MULTIPLIER"
# b_crack_mul = crack_mul9 / (10**9 * math.log(10**9, 2))
# print b_crack_mul
# a_crack_mul = crack_mul5 - b_crack_mul*((10**5)*math.log((10**5),2))
# print a_crack_mul
# #
# print "FOR SCAN SORTED MULTIPLIER"
# b_scansort_mul = sort_scan_mul9 / (10**9 * math.log(10**9, 2))
# print b_scansort_mul
# a_scansort_mul = sort_scan_mul5 - b_scansort_mul*((10**5)*math.log((10**5),2))
# print a_scansort_mul
# #
# print "FOR SCAN UNSORTED MULTIPLIER"
# b_scanunsort_mul = unsort_scan_mul9 / (10**9 * math.log(10**9, 2))
# print b_scanunsort_mul
# a_scanunsort_mul = unsort_scan_mul5 - b_scanunsort_mul*((10**5)*math.log((10**5),2))
#print a_scanunsort_mul

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