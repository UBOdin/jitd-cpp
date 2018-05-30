import sys
import matplotlib.pyplot as plt
fig, ax = plt.subplots()
ax.set_axisbelow(True)
ax.minorticks_on()
# ax.grid(which='major', linestyle='-', linewidth=0.5)
# ax.grid(which='minor', linestyle=':', linewidth=0.5)
for fileNo in range(1,len(sys.argv)):
	inFile = sys.argv[fileNo]
	with open(inFile,'r') as i:
	    lines = i.readlines()
	arrSizes = []
	x = []
	y = []
	x.append(0)
	for line in lines:
		nums = line.split()
		arrSizes.append(int(nums[1]))
		xi = (float(nums[0])/1000000000.0)+x[-1]
		x.append(xi)
		x.append(xi)
		y.append(float(nums[2])/1000000000.0)
		y.append(y[-1])
	x.pop(0)
	y.pop(-1)
	y.insert(0,y[0])
# print(type(x[0]))
# print(type(y[0]))

        plt.plot(x, y, 'o-', ms=2, label=inFile)
plt.xlim(0,1000)
plt.xscale('log')
plt.yscale('log')

plt.xlabel('idle time (s)')
plt.ylabel('response (sec)')
plt.legend(loc = 'best')
plt.show()