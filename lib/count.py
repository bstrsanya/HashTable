import numpy as np
from scipy import stats

data = [5881534229,
5833019032,
5777887889,
5726513981,
5873145815,
5748730643,
5772092347,
5778776028,
5867040606,
5737314455,
5808208287,
5798202422,
5778608838,
5735838178,
5844096473,
5805067855,
5750380438,
5838022887,
5845881465,
5822732517]

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