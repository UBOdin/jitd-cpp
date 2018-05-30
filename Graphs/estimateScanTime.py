import math

CrackMultiplier = 19.0639176
# CrackMultiplier = 47.8836025
SortMultiplier = 197.1873772
ScanUnsortedMultiplier = 2.5988664
ScanSortedMultiplier = 1.6e-5
StartSize = 1000000000

def getTimeToTarget(targetScanTime, crackThreshold):
    # crackThreshold = 100000
    # targetScanTime = 300000
    totalElapsedTime = 0
    arraysizes = []
    crackedarraysizes = []
    sortedarraysizes = []
    crackSizes = []
    sortSizes = []
    timeToCrack = []
    timeToSort = []
    scanTimes = []
    arraysizes.append(StartSize)
    currentScanTime = StartSize * ScanUnsortedMultiplier
    scanTimes.append(currentScanTime)
    while not len(arraysizes) == 0 and currentScanTime > targetScanTime:
        arraysizes.sort(reverse=True)
        a = arraysizes[0]
        arraysizes = arraysizes[1:]
        if a <= crackThreshold:
            crackedarraysizes.append(a)
            continue
        crackSizes.append(a)
        timeToCrack.append(a * CrackMultiplier)
        totalElapsedTime = totalElapsedTime + timeToCrack[-1]
        newA = int(a * 0.75)
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
            TotalScanTime = TotalScanTime + (x * x * ScanUnsortedMultiplier)
        for x in crackedarraysizes:
            TotalScanTime = TotalScanTime + (x * x * ScanUnsortedMultiplier)
        averageScanTime = TotalScanTime / StartSize
        currentScanTime = averageScanTime
        scanTimes.append(averageScanTime)

    scanTimes = scanTimes[1:]
    if len(arraysizes) != 0:
        return totalElapsedTime
    else:
        crackedarraysizes.sort(reverse=True)
        scanTimes2 = []
        while len(crackedarraysizes) != 0 and currentScanTime > targetScanTime:
            a = crackedarraysizes[0]
            crackedarraysizes = crackedarraysizes[1:]
            sortSizes.append(a)
            timeToSort.append(a * math.log(a, 2) * SortMultiplier)
            totalElapsedTime = totalElapsedTime + timeToSort[-1]
            sortedarraysizes.append(a)
            TotalScanTime = 0
            for x in crackedarraysizes:
                TotalScanTime = TotalScanTime + (x * x * ScanUnsortedMultiplier)
            for x in sortedarraysizes:
                TotalScanTime = TotalScanTime + (x * math.log(x, 2) * ScanSortedMultiplier)
            averageScanTime = TotalScanTime / StartSize
            currentScanTime = averageScanTime
            scanTimes2.append(averageScanTime)
        return totalElapsedTime


def findMaxN(targetScanTime):
    n = 100000
    N = StartSize
    opt = getTimeToTarget(targetScanTime, n)
    i = int((n + N) / 2)
    while i > n:
        timeToTarget = getTimeToTarget(targetScanTime, i)
        if timeToTarget == opt:
            n = i
        else:
            N = i
        i = int((n + N) / 2)
    return N, opt


times = range(100000000,int(StartSize*ScanUnsortedMultiplier),10000000)
for time in times:
    N, opt = findMaxN(time)
    print str(time) + "\t" + str(N) + "\t" + str(opt)