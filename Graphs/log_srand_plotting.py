# importing the required module

import matplotlib.pyplot as plt
import numpy as np

x_5_action = np.array([2000,2401,2802,3203,3604,4005,8010,12015,16020,20025,24030,28035,32040,36045,40056])
policy_time_5 = np.array([1.23492e+09,1.26343e+09,1.28512e+09,1.29664e+09,1.32638e+09,1.33961e+09,1.432e+09,1.49299e+09,1.53652e+09,1.57336e+09,1.7472e+09,1.88458e+09,1.98995e+09,2.0346e+09,2.05227e+09,10e+10])
#policy_time_5 = policy_time_5/1000000
y_5_scan = np.array([4.96162e+06,4.22228e+06,3.54926e+06,3.08932e+06,2.76355e+06,2.49395e+06,1.24755e+06,822533,634402,508675,268736,121007,38604,12249,8233,8233])
#y_5_scan = y_5_scan/1000000

x_6_action = np.array([202,242,282,322,362,402,804,1206,1608,2010,2412,2814,3616,3618,4028])
policy_time_6 = np.array([8.7397e+08,9.03766e+08,9.28562e+08,9.4908e+08,9.68615e+08,9.76081e+08,1.08475e+09,1.14745e+09,1.19199e+09,1.23227e+09,1.44874e+09,1.60573e+09,1.71944e+09,1.78287e+09,1.81466e+09,10e+10])
#policy_time_6 = policy_time_6/1000000
y_6_scan = np.array([4.69121e+07,3.87133e+07,3.28943e+07,2.86826e+07,2.6214e+07,2.33245e+07,1.23393e+07,8.12273e+06,5.91841e+06,4.89895e+06,2.54931e+06,1.00477e+06,324252,45421,9723,9723])
#y_6_scan = y_6_scan/1000000

x_7_action = np.array([19,23,27,31,35,39,78,117,156,195,234,273,312,351,398])
policy_time_7 = np.array([4.89438e+08,5.20935e+08,5.46042e+08,5.74468e+08,5.93231e+08,6.05193e+08,7.17251e+08,7.87825e+08,8.25221e+08,8.6043e+08,1.08972e+09,1.28177e+09,1.41266e+09,1.49781e+09,1.53998e+09,10e+10])
#policy_time_7 = policy_time_7/1000000
y_7_scan = np.array([5.36636e+08,4.29052e+08,3.40587e+08,2.9239e+08,2.62723e+08,2.33379e+08,1.18343e+08,7.93705e+07,6.03773e+07,4.82246e+07,2.73475e+07,1.20724e+07,4.33108e+06,942075,8278,8278])
#y_7_scan = y_7_scan/1000000

x_8_action = np.array([1,3,5,10,15,20,25,30,35,40,45,52])
policy_time_8 = np.array([8.69127e+07,2.04637e+08,2.96569e+08,3.91804e+08,4.49104e+08,4.92249e+08,8.64013e+08,1.0916e+09,1.21631e+09,1.26122e+09,1.26967e+09,1.26428e+09,10e+10])
#policy_time_8 = policy_time_8/1000000
y_8_scan = np.array([4.33258e+09,3.50277e+09,1.597e+09,8.83617e+08,6.19905e+08,4.89391e+08,1.75015e+08,4.63921e+07,8.27382e+06,16333,6172,6221,6221])
#y_8_scan = y_8_scan/1000000

x_9_action = np.array([1,2])
policy_time_9 = np.array([8.94548e+08,8.94616e+08,10e+10])
#policy_time_9 = policy_time_9/1000000
y_9_scan = np.array([5370,5349,5349])
#y_9_scan = y_9_scan/1000000



#plotting the points
# plt.figure(1)
# plt.plot(x_5_action, y_5_scan, marker = 'o', label='JITD_5',color = 'b')
# plt.plot(x_6_action, y_6_scan, marker = 'o', label='JITD_6',color = 'g')
# plt.plot(x_7_action, y_7_scan, marker = 'o', label='JITD_7',color = 'r')
# plt.plot(x_8_action, y_8_scan, marker = 'o', label='JITD_8',color = 'c')
# plt.plot(x_9_action, y_9_scan, marker = 'o', label='JITD_9',color = 'm')
# plt.xscale('log')
# plt.yscale('log')
# plt.legend(bbox_to_anchor=(1.1, 1.05))
# plt.xlabel('No of actions')
# plt.ylabel('Scan Time in micro sec')

f = plt.figure(2)
plt.plot(policy_time_5,y_5_scan, marker = 'o', label='JITD_5')
plt.plot(policy_time_6,y_6_scan, marker = 'o', label='JITD_6')
plt.plot(policy_time_7,y_7_scan, marker = 'o', label='JITD_7')
plt.plot(policy_time_8,y_8_scan, marker = 'o', label='JITD_8')
plt.plot(policy_time_9,y_9_scan, marker = 'o', label='JITD_9')

plt.axhline(y = 3946, label = 'Map', color = 'k')
plt.axvline(x = 3.44703e+09, color = 'k')

# plt.axhline(y = 8233, color = 'b')
# plt.axhline(y = 9723, color = 'g')
# plt.axhline(y = 8278, color = 'r')
# plt.axhline(y = 6221, color = 'c')
# plt.axhline(y = 5349, color = 'm')

plt.axhline(y = 7.14601e+09, label = 'Unsorted Array', color = 'y')

plt.xscale('log')
plt.yscale('log')

plt.xlabel('TransformationTime (micro sec)')
plt.ylabel('Scan Time (micro sec)')

plt.title('Uniform Workload')
plt.legend(loc='upper right', fancybox=True, framealpha=0.5, frameon=False)
plt.show()
font = {'family' : 'Times New Roman',
        'size'   : 8}
f.savefig("/Users/darshanabalakrishnan/GitRepo/JITD_ICDE_2018F/jitd-cpp/Graphs/TransformTimeVSScanTime.pdf",dpi = '300', bbox_inches='tight', format = 'pdf',transparent= 'true')
