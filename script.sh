#!/bin/bash

make debug=true
./hash_table > res.txt
python3 1.py 'res.txt' 'murmur.png' 'Murmur хеш.'