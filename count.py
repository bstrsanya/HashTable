import numpy as np
from scipy import stats

data = [17006718515,
16283023670,
16827703962,
17263016207,
16996689119,
16407424345,
16977873345,
16928678841,
16875471021,
16896366935,
16948697480,
16862963674,
17619355537,
16969661596,
16925959317,
17399540855,
16916232605,
16471390749,
16918230182,
16947062219]

n = len(data)                  
mean = np.mean(data)           
print (mean)
std = np.std(data, ddof=1)
sem = std / np.sqrt(n)         

for i in data:
    if (mean - sem * 11 > i) or (mean + sem * 11  < i):
        print (i)

print (std)
print (sem)
print (11 * sem / mean)