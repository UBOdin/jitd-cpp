# importing the required module

import matplotlib.pyplot as plt
import numpy as np
# x axis values

#xi = [i for i in range(0, len(x))]
# corresponding y axis values
x_5_action = np.array([4005,8010,12015,16020,20025,24030,28035,32040,36045,40056])
policy_time_5 = np.array([1.2443e+09,1.50315e+09,1.41692e+09,1.52074e+09,1.447e+09,1.64554e+09,1.8528e+09,1.99966e+09,2.10552e+09,1.95927e+09])
y_5_scan = np.array([2533110,1267060,803301,659560,503929,253313,113430,41015,12429,8125])

x_6_action = np.array([402,804,1206,1608,2010,2412,2814,3616,3618,4028])
policy_time_6 = np.array([8.77524e+08,1.05162e+09,1.02825e+09,1.13545e+09,1.23346e+09,1.42878e+09,1.52634e+09,1.60518e+09,1.85649e+09,1.7164e+09])
y_6_scan = np.array([2.3885e+07,1.31287e+07,8.00404e+06,6.03012e+06,4.93013e+06,2.54362e+06,829320,264717,37774,9422])

x_7_action = np.array([39,78,117,156,195,234,273,312,351,398])
policy_time_7 = np.array([5.46152e+08,6.79847e+08,6.56895e+08,7.55787e+08,7.36953e+08,9.86481e+08,1.22374e+09,1.30465e+09,1.39448e+09,1.44888e+09])
y_7_scan = np.array([2.52865e+08,1.35427e+08,8.5222e+07,6.0564e+07,4.69642e+07,2.6502e+07,1.09418e+07,5.73727e+06,316430,8016])

x_8_action = np.array([5,10,15,20,25,30,35,40,45,52])
policy_time_8 = np.array([2.71662e+08,3.81625e+08,3.6693e+08,4.12779e+08,9.165e+08,9.90742e+08,1.15698e+09,1.16814e+09,1.27126e+09,1.24831e+09])
y_8_scan = np.array([1.75369e+09,8.68177e+08,6.46406e+08,5.43071e+08,9.50107e+07,8.84241e+07,1.16712e+07,6061,6225,6375])
#divide all values by 1000 for final graph.

x_9_action = np.array([1,2])
policy_time_9 = np.array([8.90849e+08,8.82903e+08])
y_9_scan = np.array([5358,5431])


#plotting the points
plt.plot(x_5_action, y_5_scan, marker = 'o', label='JITD_5')
plt.plot(x_6_action, y_6_scan, marker = 'o', label='JITD_6')
plt.plot(x_7_action, y_7_scan, marker = 'o', label='JITD_7')
# plt.plot(x_8_action, y_8_scan, marker = 'o', label='JITD_8')
# plt.plot(x_9_action, y_9_scan, marker = 'o', label='JITD_9')

# plt.plot(policy_time_5,y_5_scan, marker = 'o', label='JITD_5')
# plt.plot(policy_time_6,y_6_scan, marker = 'o', label='JITD_6')
# plt.plot(policy_time_7,y_7_scan, marker = 'o', label='JITD_7')
# plt.plot(policy_time_8,y_8_scan, marker = 'o', label='JITD_8')
# plt.plot(policy_time_9,y_9_scan, marker = 'o', label='JITD_9')

# plt.plot(y_5_scan,policy_time_5, marker = 'o', label='JITD_5')
# plt.plot(y_6_scan,policy_time_6, marker = 'o', label='JITD_6')
# plt.plot(y_7_scan,policy_time_7, marker = 'o', label='JITD_7')
# plt.plot(y_8_scan,policy_time_8, marker = 'o', label='JITD_8')
# plt.plot(y_9_scan,policy_time_9, marker = 'o', label='JITD_9')


#plt.plot(x, y_m, marker = 'o',label = 'MAP')
plt.xscale('log')
plt.yscale('log')
#plt.xlim(1000,10000000000)
#plt.ylim(1000000,10000000000)

#plt.ylim(1000000,70000000)
# naming the x axis
plt.ylabel('Scan Time in us')
# naming the y axis
plt.xlabel('Policy action Time in us')
#plt.xticks(xi, x)
# giving a title to my graph
plt.title('Uniform Workload')
plt.legend(bbox_to_anchor=(1.1, 1.05))
# function to show the plot
plt.show()