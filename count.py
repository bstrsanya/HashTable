import numpy as np
from scipy import stats

data = [12940618975,
12868340568,
12854937667,
12873503059,
12876993436,
13013122809,
12973003112,
13011397975,
13042391247,
13075794135,
12926594777,
13023866235,
13164978278,
12923346114,
13168235747,
13264296157,
13322848879,
13289998540,
13109609876,
12945349433]

n = len(data)                  
mean = np.mean(data)           
print (mean)
std = np.std(data, ddof=1)
sem = std / np.sqrt(n)         

for i in data:
    if (mean - sem * 9 > i) or (mean + sem * 9  < i):
        print (i)

print (std)
print (sem)
print (9 * sem / mean)