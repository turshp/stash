#!/usr/bin/env python

import pdb

def fib(max):
    n, a, b = 0, 0, 1
    while n < max:
        yield b
        pdb.set_trace()
        a, b = b, a + b
        n = n + 1


if __name__ == '__main__':
    for n in fib(10):
        print n, ""
