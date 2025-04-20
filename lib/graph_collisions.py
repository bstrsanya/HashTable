import matplotlib.pyplot as plt
import sys
import os

with open (os.devnull, 'w') as sys.stderr:
    pass

file_path = sys.argv[1]
with open(file_path, 'r') as f:
    collisions = [int(line.strip()) for line in f if line.strip()]

plt.figure(figsize=(12, 7))
plt.bar(range(len(collisions)), collisions, color='green', width=1.0)
plt.xlabel('Номер хеш-бакета')
plt.ylabel('Количество коллизий')
plt.title('Коллизии в хеш-функции.' + ' ' + sys.argv[3])
plt.savefig(sys.argv[2])
