# importing the required module

import matplotlib.pyplot as plt
import numpy as np

x_5_action = np.array([2000,2401,2802,3203,3604,4005,8010,12015,16020,20025,24030,28035,32040,36045,40056])
policy_time_51 = np.array([1.23492e+09,1.26343e+09,1.28512e+09,1.29664e+09,1.32638e+09,1.33961e+09,1.432e+09,1.49299e+09,1.53652e+09,1.57336e+09,1.7472e+09,1.88458e+09,1.98995e+09,2.0346e+09,2.05227e+09])
policy_time_52 = np.array([1.22665e+09,1.26373e+09,1.28303e+09,1.3002e+09,1.31881e+09,1.33084e+09,1.43832e+09,1.50744e+09,1.53674e+09,1.57534e+09,1.74783e+09,1.89867e+09,1.98003e+09,2.04776e+09,2.05411e+09])
policy_time_53 = np.array([1.23398e+09,1.25701e+09,1.28234e+09,1.3013e+09,1.31497e+09,1.33254e+09,1.44385e+09,1.4947e+09,1.5451e+09,1.57578e+09,1.74798e+09,1.88401e+09,1.98977e+09,1.98977e+09,2.05698e+09])
policy_time_54 = np.array([1.22619e+09,1.25221e+09,1.27795e+09,1.29809e+09,1.31474e+09,1.33047e+09,1.43734e+09,1.50933e+09,1.53815e+09,1.57e+09,1.75239e+09,1.88215e+09,1.98193e+09,2.03604e+09,2.05899e+09])
policy_time_5 = (policy_time_51 + policy_time_52 + policy_time_53 + policy_time_54)/4
policy_time_5 = np.append(policy_time_5,100000000000)
policy_time_5 = policy_time_5/1000000.0
y_51_scan = np.array([4.96162e+06,4.22228e+06,3.54926e+06,3.08932e+06,2.76355e+06,2.49395e+06,1.24755e+06,822533,634402,508675,268736,121007,38604,12249,8233,8233])
y_52_scan = np.array([4.91412e+06,4.17268e+06,3.53824e+06,3.13451e+06,2.74466e+06,2.46562e+06,1.248e+06,837751,633990,506004,268975,122241,38523,12712,8156,8156])
y_53_scan = np.array([4.89905e+06,4.09915e+06,3.54752e+06,3.10125e+06,2.74911e+06,2.49586e+06,1.26917e+06,951077,635016,509138,269109,121143,38568,38568,11207,11207])
y_54_scan = np.array([4.86199e+06,4.09433e+06,3.54461e+06,3.10573e+06,2.67601e+06,2.46912e+06,1.24754e+06,837993,635108,509467,268952,121012,38162,12349,7981,7981])
y_5_scan= (y_51_scan + y_52_scan + y_53_scan + y_54_scan)/4
y_5_scan = y_5_scan/1000000000.0

x_6_action = np.array([202,242,282,322,362,402,804,1206,1608,2010,2412,2814,3616,3618,4028])
policy_time_61 = np.array([8.7397e+08,9.03766e+08,9.28562e+08,9.4908e+08,9.68615e+08,9.76081e+08,1.08475e+09,1.14745e+09,1.19199e+09,1.23227e+09,1.44874e+09,1.60573e+09,1.71944e+09,1.78287e+09,1.81466e+09])
policy_time_62 = np.array([8.74546e+08,9.03981e+08,9.25243e+08,9.51668e+08,9.68457e+08,9.84577e+08,1.09304e+09,1.15629e+09,1.20175e+09,1.24097e+09,1.453e+09,1.61681e+09,1.72873e+09,1.79495e+09,1.80413e+09])
policy_time_63 = np.array([8.66845e+08,9.03559e+08,9.24061e+08,9.46599e+08,9.61846e+08,9.80056e+08,1.08644e+09,1.14838e+09,1.19307e+09,1.23213e+09,1.45299e+09,1.60756e+09,1.72084e+09,1.78711e+09,1.80416e+09])
policy_time_64 = np.array([8.68969e+08,8.97028e+08,9.27867e+08,9.43079e+08,9.61135e+08,9.84195e+08,1.08568e+09,1.15458e+09,1.1932e+09,1.23232e+09,1.4511e+09,1.60683e+09,1.73038e+09,1.78558e+09,1.80194e+09])
policy_time_6 = (policy_time_61 + policy_time_62 + policy_time_63 + policy_time_64)/4
policy_time_6 = np.append(policy_time_6,100000000000)
policy_time_6 = policy_time_6/1000000.0
y_61_scan = np.array([4.69121e+07,3.87133e+07,3.28943e+07,2.86826e+07,2.6214e+07,2.33245e+07,1.23393e+07,8.12273e+06,5.91841e+06,4.89895e+06,2.54931e+06,1.00477e+06,324252,45421,9723,9723])
y_62_scan = np.array([4.69191e+07,3.87294e+07,3.27135e+07,2.86989e+07,2.61552e+07,2.34828e+07,1.23708e+07,8.20996e+06,6.03884e+06,5.0138e+06,2.5646e+06,988169,319638,47124,9558,9558])
y_63_scan = np.array([4.66831e+07,3.8752e+07,3.27182e+07,2.85971e+07,2.6053e+07,2.33424e+07,1.23347e+07,8.09348e+06,6.03983e+06,4.84327e+06,2.58602e+06,987148,314525,46199,9567,9567])
y_64_scan = np.array([4.67194e+07,3.86004e+07,3.29031e+07,2.8592e+07,2.62787e+07,2.3318e+07,1.23083e+07,8.3634e+06,5.92628e+06,4.86296e+06,2.57545e+06,1.01002e+06,335776,45541,9313,9313])
y_6_scan = (y_61_scan + y_62_scan + y_63_scan + y_64_scan)/4
y_6_scan = y_6_scan/1000000000.0

x_7_action = np.array([19,23,27,31,35,39,78,117,156,195,234,273,312,351,398])
policy_time_71 = np.array([4.89438e+08,5.20935e+08,5.46042e+08,5.74468e+08,5.93231e+08,6.05193e+08,7.17251e+08,7.87825e+08,8.25221e+08,8.6043e+08,1.08972e+09,1.28177e+09,1.41266e+09,1.49781e+09,1.53998e+09])
policy_time_72 = np.array([4.8697e+08,5.21012e+08,5.5142e+08,5.75498e+08,5.88945e+08,6.11677e+08,7.24629e+08,7.88007e+08,8.32274e+08,8.6847e+08,1.0891e+09,1.28564e+09,1.42018e+09,1.50515e+09,1.54983e+09])
policy_time_73 = np.array([4.84283e+08,5.21372e+08,5.46493e+08,5.70889e+08,5.91056e+08,6.10489e+08,7.20505e+08,7.86813e+08,8.25841e+08,8.67431e+08,1.08268e+09,1.28004e+09,1.42023e+09,1.49819e+09,1.54574e+09])
policy_time_74 = np.array([4.88038e+08,5.18287e+08,5.50438e+08,5.70338e+08,5.92257e+08,6.06756e+08,7.23518e+08,7.81678e+08,8.31616e+08,8.62006e+08,1.08293e+09,1.28017e+09,1.42047e+09,1.49574e+09,1.54113e+09])
policy_time_7 = (policy_time_71 + policy_time_72 + policy_time_73 + policy_time_74)/4
policy_time_7 = np.append(policy_time_7,100000000000)
policy_time_7 = policy_time_7/1000000
y_71_scan = np.array([5.36636e+08,4.29052e+08,3.40587e+08,2.9239e+08,2.62723e+08,2.33379e+08,1.18343e+08,7.93705e+07,6.03773e+07,4.82246e+07,2.73475e+07,1.20724e+07,4.33108e+06,942075,8278,8278])
y_72_scan = np.array([5.36172e+08,4.28583e+08,3.42408e+08,2.91034e+08,2.62224e+08,2.34361e+08,1.18998e+08,7.94269e+07,6.04928e+07,4.84395e+07,2.73926e+07,1.21355e+07,4.34856e+06,941844,8114,8114])
y_73_scan = np.array([5.35947e+08,4.29719e+08,3.42305e+08,2.8973e+08,2.61587e+08,2.34155e+08,1.1828e+08,7.94576e+07,6.02729e+07,4.85189e+07,2.71998e+07,1.21625e+07,4.35533e+06,937482,8158,8158])
y_74_scan = np.array([5.36956e+08,4.27583e+08,3.43743e+08,2.90061e+08,2.62415e+08,2.33732e+08,1.18924e+08,7.902e+07,6.06398e+07,4.82755e+07,2.72461e+07,1.20892e+07,4.35896e+06,934229,8072,8072])
y_7_scan = (y_71_scan + y_72_scan + y_73_scan +y_74_scan)/4
y_7_scan = y_7_scan/1000000000.0

x_8_action = np.array([1,3,5,10,15,20,25,30,35,40,45,52])
policy_time_81 = np.array([8.69127e+07,2.04637e+08,2.96569e+08,3.91804e+08,4.49104e+08,4.92249e+08,8.64013e+08,1.0916e+09,1.21631e+09,1.26122e+09,1.26967e+09,1.26428e+09])
policy_time_82 = np.array([8.68681e+07,2.02743e+08,2.95777e+08,3.90384e+08,4.52571e+08,4.96773e+08,8.66117e+08,1.08968e+09,1.22014e+09,1.2625e+09,1.26863e+09,1.27086e+09])
policy_time_83 = np.array([8.62051e+07,2.03558e+08,2.94718e+08,3.91084e+08,4.50531e+08,4.92496e+08,8.68897e+08,1.09029e+09,1.21791e+09,1.26298e+09,1.26528e+09,1.26938e+09])
policy_time_84 = np.array([8.70102e+07,2.02796e+08,2.93718e+08,3.93276e+08,4.50021e+08,4.92955e+08,8.65853e+08,1.09426e+09,1.21627e+09,1.26376e+09,1.26552e+09,1.26373e+09])
policy_time_8 = (policy_time_81 + policy_time_82 + policy_time_83 + policy_time_84)/4
policy_time_8 = np.append(policy_time_8,100000000000)
policy_time_8 = policy_time_8/1000000
y_81_scan = np.array([4.33258e+09,3.50277e+09,1.597e+09,8.83617e+08,6.19905e+08,4.89391e+08,1.75015e+08,4.63921e+07,8.27382e+06,16333,6172,6221,6221])
y_82_scan = np.array([4.32711e+09,3.48719e+09,1.59971e+09,8.83494e+08,6.22464e+08,4.91397e+08,1.75811e+08,4.65295e+07,8.30249e+06,16246,6287,6245,6245])
y_83_scan = np.array([4.31272e+09,3.55841e+09,1.58946e+09,8.84932e+08,6.20108e+08,4.89292e+08,1.76081e+08,4.6357e+07,8.2736e+06,16154,6244,6317,6317])
y_84_scan = np.array([4.3161e+09,3.49175e+09,1.59105e+09,8.87646e+08,6.20921e+08,4.92013e+08,1.75276e+08,4.6553e+07,8.2743e+06,16214,6221,6241,6241])
#y_8_scan = y_8_scan/1000000
y_8_scan = (y_81_scan + y_82_scan + y_83_scan +y_84_scan)/4
y_8_scan = y_8_scan/1000000000.0

x_9_action = np.array([1,2])
policy_time_91 = np.array([8.94548e+08,8.94616e+08])
policy_time_92 = np.array([8.94299e+08,8.95435e+08])
policy_time_93 = np.array([8.94447e+08,8.94466e+08])
policy_time_94 = np.array([8.9452e+08,8.94832e+08])
policy_time_9 = (policy_time_91 + policy_time_92 + policy_time_93 + policy_time_94)/4
policy_time_9 = np.append(policy_time_9,100000000000)
policy_time_9 = policy_time_9/1000000
y_91_scan = np.array([5370,5349,5349])
y_92_scan = np.array([5388,5381,5381])
y_93_scan = np.array([5402,5370,5370])
y_94_scan = np.array([5403,5338,5338])
y_9_scan = (y_91_scan + y_92_scan + y_93_scan +y_94_scan)/4
y_9_scan = y_9_scan/1000000000.0



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

f = plt.figure(1)
plt.xlim(100,100000)
plt.plot(policy_time_5,y_5_scan, marker = 'o', label='CrackThreshold10^5',linestyle = '-',linewidth = 3.0, markevery = 3, markersize = 9,color = 'r')
plt.plot(policy_time_6,y_6_scan, marker = 'x', label='CrackThreshold10^6',linestyle = '--' ,linewidth = 3.0,markevery = 3,  markersize = 9,color = 'g')
plt.plot(policy_time_7,y_7_scan, marker = '^', label='CrackThreshold10^7',linestyle = '-.',linewidth = 3.0,markevery = 3,  markersize = 9,color = 'b')
plt.plot(policy_time_8,y_8_scan, marker = '*', label='CrackThreshold10^8',linestyle = ':',linewidth = 3.0,markevery = 3,  markersize = 9,color = 'c')
plt.plot(policy_time_9,y_9_scan, marker = 'D', label='CrackThreshold10^9',linestyle = '-',linewidth = 3.0,markevery = 3,  markersize = 9,color = 'm')

xv9 = np.array([8.94832e+08/1000000,8.94832e+08/1000000])
yv9 = np.array([(5338/1000000000.0),(7.14601e+09/1000000000.0)])
plt.axhline(y = 3946/1000000000.0, label = 'Map', color = 'k')
plt.axvline(x = 3.44703e+09/1000000, color = 'k')
plt.plot(xv9,yv9,marker = 'D',linestyle = '-',linewidth = 3.0,markevery = 3,  markersize = 7,color = 'm')

xh9 = np.array([100000000/1000000,8.94832e+08/1000000])
yh9 = np.array([(7.14601e+09/1000000000.0),(7.14601e+09/1000000000.0)])
plt.plot(xh9,yh9,marker = 'D',linestyle = '-',linewidth = 3.0,markevery = 3,  markersize = 7,color = 'm')

# plt.axhline(y = 8233, color = 'b')
# plt.axhline(y = 9723, color = 'g')
# plt.axhline(y = 8278, color = 'r')
# plt.axhline(y = 6221, color = 'c')
# plt.axhline(y = 5349, color = 'm')

plt.axhline(y = 7.14601e+09/1000000000.0, label = 'Unsorted Array', color = 'y')
font = {
#    'family' : 'Times New Roman',
  'size'   : 12
}
plt.rc('font', **font)
# plt.xscale('log')
plt.yscale('log')
plt.xlim(50,3500)
plt.xlabel('Transformation Time(sec)')
plt.ylabel('Lookup Time(sec)')

plt.legend(loc='best', fancybox=True, framealpha=0.1, frameon=False)
#plt.tight_layout(w_pad= 2.0, h_pad= 0.5)
plt.show()

f.savefig("/Users/darshanabalakrishnan/GitLab/Paper-JITD-ICDE2108/TransformTimeVSScanTime.pdf", bbox_inches='tight', format = 'pdf',transparent= 'true')
