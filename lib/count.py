import numpy as np
from scipy import stats

data = [7739590879,
7671466836,
7738425617,
7774943909,
7795791212,
7779729443,
7789517882,
7987983792,
7687711539,
7849323531,
7798982638,
7675867131,
7760526657,
7857723213,
7969213439,
8244068245,
8062560929,
8078368159,
7973105991,
7985581220]

n = len(data)                  
mean = np.mean(data)           
print (mean)
sum = 0
for i in data:
    sum += (mean - i) ** 2
sum /= 19 * 20
print (sum ** 0.5)
std = np.std(data, ddof=1)
sem = std / np.sqrt(n)         

print (std)
print (sem)
# print (9 * sem / mean)