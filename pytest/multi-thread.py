import time
import threading

balance = 0
lock = threading.Lock()

def change_it(n):
	global balance
	with lock:
		balance = balance + n
		balance = balance - n


def run_thread(n):
	print "thread  %s is running..." % threading.current_thread().name
	#for i in range(100000):
	while True:
		change_it(n)


t1 = threading.Thread(target=run_thread, args=(5,), name = 't1')
t2 = threading.Thread(target=run_thread, args=(8,), name = 't2')
t1.start()
t2.start()
t1.join()
t2.join()

print balance