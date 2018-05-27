# importing the required module

import matplotlib.pyplot as plt
import numpy as np
# x axis values

#xi = [i for i in range(0, len(x))]
# corresponding y axis values
f = plt.figure(1)
ct = np.array([100000, 1000000, 10000000, 100000000, 1000000000])
pt = np.array([2.02E+09,1.75E+09,1.60E+09,1.15E+09,8.86E+08])
st =np.array([645476,503720,476443,365710,327390])
# plotting the points
plt.scatter(pt, st, c = ['r','g','b','c','m'], marker = 'o')
for i, txt in enumerate(ct):
    plt.annotate(txt, (pt[i],st[i]))
#plt.xscale('log')
plt.yscale('log')
# naming the x axis
plt.xlabel('PolicyTime(micro sec)')
# naming the y axis
plt.ylabel('Scan Time(micro sec)')
#plt.xticks(xi, x)
# giving a title to my graph
plt.title('JITD Uniform Workload')
#plt.legend(loc='upper right', fancybox=True, framealpha=0.5, frameon=False)
plt.show()
font = {'family' : 'Times New Roman',
        'size'   : 8}
f.savefig("/Users/darshanabalakrishnan/Desktop/JITD-ICDE-2018/policyTimeVsScanTimeVsCrackThresholdJITDUni.pdf",dpi = '300', bbox_inches='tight', format = 'pdf',transparent= 'true')

f = plt.figure(2)
ct = np.array([100000, 1000000, 10000000, 100000000, 1000000000])
pt = np.array([3.91E+09,3.83E+09,3.93E+09,3.54E+09,3.93E+09])
st =np.array([421605,329808,408730,327256,392719])
# plotting the points
plt.scatter(pt, st, c = ['r','g','b','c','m'], marker = 'o')
for i, txt in enumerate(ct):
    plt.annotate(txt, (pt[i],st[i]))
#plt.xscale('log')
plt.yscale('log')
# naming the x axis
plt.xlabel('PolicyTime(micro sec)')
# naming the y axis
plt.ylabel('Scan Time(micro sec)')
#plt.xticks(xi, x)
# giving a title to my graph
plt.title('MAP Uniform Workload')
#plt.legend(loc='upper right', fancybox=True, framealpha=0.5, frameon=False)
plt.show()
font = {'family' : 'Times New Roman',
        'size'   : 8}
f.savefig("/Users/darshanabalakrishnan/Desktop/JITD-ICDE-2018/policyTimeVsScanTimeVsCrackThresholdMAPUni.pdf",dpi = '300', bbox_inches='tight', format = 'pdf',transparent= 'true')

f = plt.figure(3)
ct = np.array([100000, 1000000, 10000000, 100000000, 1000000000])
pt = np.array([1.99216e+09,1.77965e+09,1.49794e+09,1.20429e+09,7.92637e+07])
st =np.array([599482,446773,428990,372912,288356])
# plotting the points
plt.scatter(pt, st, c = ['r','g','b','c','m'], marker = 'o')
for i, txt in enumerate(ct):
    plt.annotate(txt, (pt[i],st[i]))
#plt.xscale('log')
plt.yscale('log')
# naming the x axis
plt.xlabel('PolicyTime(micro sec)')
# naming the y axis
plt.ylabel('Scan Time(micro sec)')
#plt.xticks(xi, x)
# giving a title to my graph
plt.title('JITD HeavyHitter Workload')
#plt.legend(loc='upper right', fancybox=True, framealpha=0.5, frameon=False)
plt.show()
font = {'family' : 'Times New Roman',
        'size'   : 8}
f.savefig("/Users/darshanabalakrishnan/Desktop/JITD-ICDE-2018/policyTimeVsScanTimeVsCrackThresholdJITDHH.pdf",dpi = '300', bbox_inches='tight', format = 'pdf',transparent= 'true')

f = plt.figure(4)
ct = np.array([100000, 1000000, 10000000, 100000000, 1000000000])
pt = np.array([3.56488e+09,3.93551e+09,3.53743e+09,3.93351e+09,3.55376e+09])
st =np.array([321695,416301,315340,437716,334322])
# plotting the points
plt.scatter(pt, st, c = ['r','g','b','c','m'], marker = 'o')
for i, txt in enumerate(ct):
    plt.annotate(txt, (pt[i],st[i]))
#plt.xscale('log')
plt.yscale('log')
# naming the x axis
plt.xlabel('PolicyTime(micro sec)')
# naming the y axis
plt.ylabel('Scan Time(micro sec)')
#plt.xticks(xi, x)
# giving a title to my graph
plt.title('MAP HeavyHitter Workload')
#plt.legend(loc='upper right', fancybox=True, framealpha=0.5, frameon=False)
plt.show()
font = {'family' : 'Times New Roman',
        'size'   : 8}
f.savefig("/Users/darshanabalakrishnan/Desktop/JITD-ICDE-2018/policyTimeVsScanTimeVsCrackThresholdMAPHH.pdf",dpi = '300', bbox_inches='tight', format = 'pdf',transparent= 'true')