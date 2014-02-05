#!/usr/bin/env python3

import sys

s = 0
c = 0
for l in sys.stdin:
    if (int(l) < 0):
        print(l)
    s+=int(l)
    c+=1

print(s/c)
print(c)
print(s)
