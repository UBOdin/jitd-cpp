import math
import random
import numpy as np
random.seed(32767)
CrackMultiplier = 0.08557022
betaCrackMul = 6643.378
SortMultiplier = 0.0299551537012
betaSortMul = 10289.3666667
ScanUnsortedMultiplier = 0.008474124
betaScanUnsortedMul = 598.1876
ScanSortedMultiplier = 0.105842748535
betaScanSortedMul = -0.944748833333
crackThreshold = 100000
StartSize = 1000000000
arraysizes = []
crackedarraysizes = []
sortedarraysizes = []
crackSizes = []
sortSizes = []
timeToCrack = []
timeToSort = []
scanTimes = []
arraysizes.append(StartSize)
scanTimes.append((StartSize*ScanUnsortedMultiplier)+betaScanUnsortedMul)
while not len(arraysizes) == 0:
	arraysizes.sort(reverse = True)
	a = arraysizes[0]
	arraysizes = arraysizes[1:]
	if a <= crackThreshold:
		crackedarraysizes.append(a)
		continue
	crackSizes.append(a)
	timeToCrack.append((a*CrackMultiplier)+betaCrackMul)
	crack_probability = random.random()
	newA = int(a*crack_probability)
	newB = a - newA
	if newA > crackThreshold:
		arraysizes.append(newA)
	else:
		crackedarraysizes.append(newA)
	if newB > crackThreshold:
		arraysizes.append(newB)
	else:
		crackedarraysizes.append(newB)
	TotalScanTime = 0
	for x in arraysizes:
		TotalScanTime = TotalScanTime + (x*((x*ScanUnsortedMultiplier)+betaScanUnsortedMul))
	for x in crackedarraysizes:
		TotalScanTime = TotalScanTime + (x*((x*ScanUnsortedMultiplier)+betaScanUnsortedMul))
	averageScanTime = TotalScanTime/StartSize
	scanTimes.append(averageScanTime)
print 'c\t0\t0\t'+str(int(scanTimes[0]))
#print 'c\t0\t'+str(float(StartSize*ScanUnsortedMultiplier))
scanTimes = scanTimes[1:]
for i in range(0,len(crackSizes)):
	print 'c\t'+str(crackSizes[i])+'\t'+str(float(timeToCrack[i]))+'\t'+str(float(scanTimes[i]))
	#print 'c\t'+str(int(timeToCrack[i]))+'\t'+str(int(scanTimes[i]))
crackedarraysizes.sort(reverse = True)
scanTimes2 = []
while not len(crackedarraysizes) == 0:
	a = crackedarraysizes[0]
	crackedarraysizes = crackedarraysizes[1:]
	sortSizes.append(a)
	timeToSort.append(math.log(a,2)*((a*SortMultiplier)+betaSortMul))
	sortedarraysizes.append(a)
	TotalScanTime = 0
	for x in crackedarraysizes:
		TotalScanTime = TotalScanTime + (x*((x*ScanUnsortedMultiplier)+betaScanUnsortedMul))
	for x in sortedarraysizes:
		TotalScanTime = TotalScanTime + (math.log(x,2)*((x*ScanSortedMultiplier)+betaScanSortedMul))
	averageScanTime = TotalScanTime/StartSize
	scanTimes2.append(averageScanTime)
for i in range(0,len(sortSizes)):
	print 's\t'+str(sortSizes[i])+'\t'+str(float(timeToSort[i]))+'\t'+str(float(scanTimes2[i]))
	#print 's\t'+str(int(timeToSort[i]))+'\t'+str(int(scanTimes2[i]))