import sys
import matplotlib
import matplotlib.pyplot as plt
f = plt.figure(1)
font = {
#	'family' : 'Times New Roman',
  'size'   : 12
}
matplotlib.rc('font', **font)
# lineStyle = ['-', ':', '-.', '--', '-']
lineStyle = ['-','--','-',':','-']
marker = ['o', 'x', '^', '*', 'D']
colors = ['r', 'g', 'b', 'c', 'm']

for fileNo in range(1,len(sys.argv)):
	m = fileNo -1
	inFile = sys.argv[fileNo]
	with open(inFile,'r') as i:
	    lines = i.readlines()
	arrSizes = []
	x = []
	y = []
	x.append(0)
	for line in lines:
		nums = line.split()
		arrSizes.append(float(nums[1]))
		xi = ((float(nums[2])/1000000)+x[-1])
		x.append(xi)
		x.append(xi)
		y.append(float(nums[3])/1000000.0)
		y.append(y[-1])
	x.pop(0)
	y.pop(-1)
	y.insert(0,y[0])

	plt.plot(x,y, color = colors[m], label = inFile,linewidth = 3.0,linestyle = lineStyle[m],marker = marker[m],markevery = 10000,markersize = 7.0)
plt.xlabel('Transformation Time(sec)')
plt.ylabel('Lookup Time(sec)')
plt.yscale('log')
#plt.xlim(50,2500)
# plt.ylim(int(10.0e-06),10)
#plt.xlim(100,100000)
plt.legend(loc='best', fancybox=True, framealpha=0.1, frameon=False)
plt.ylim([0.000001,10])
plt.show()

#f.savefig("/Users/darshanabalakrishnan/GitLab/Paper-JITD-ICDE2108/TransformationTimeVsScanTimeEstimated.pdf", bbox_inches='tight', format = 'pdf',transparent= 'true')
