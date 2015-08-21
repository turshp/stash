#!/usr/bin/env python
# -*- coding:utf-8 -*-


def log(func):
    def wrapper(*args, **kw):
        print "function %s called." % func.__name__
        return func(*args, **kw)

    wrapper.__name__ = func.__name__
    return wrapper

@log
def main():
    print "this is main function"


if __name__ == '__main__':
    main()

