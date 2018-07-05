# Python

### boolean 자료형 비교 if greeting: 

```
def main():
    greeting = True

    if greeting:
        print ("no operation")

if __name__ == "__main__":
    main()
```
## 변수
### global 키워드
전역변수를 사용하기 위해서 함수에서 global 키워드로 전역변수를 선언
```
msg = "Hello"

def write():
    global msg
    msg += " World"
    print (msg)

def main():
    print ("=== print msg ===")
    print (msg)

    print ("=== write function ===")
    write()

    print ("=== print msg ===")
    print (msg)


if __name__ == "__main__":
    main()
```
### nonlocal 키워드
local변수가 아님을 선언
```
def greeting(name):
    greeting_msg = "Hello"

    def add_name():
        nonlocal greeting_msg

        greeting_msg += " "
        return ("%s%s" % (greeting_msg, name))

    msg = add_name()
    print (msg)

if __name__ == "__main__":
    greeting("python")
```
## First-Class
### First-Class Function
함수 자체를 인자 (argument) 로써 다른 함수에 전달하거나 다른 함수의 결과값으로 리턴 할수도 있고, 함수를 변수에 할당하거나 데이터 구조안에 저장할 수 있는 함수를 뜻
```
def square(x):
    return x+2

def bind(func, arg_list):
    result = []
    for arg in arg_list:
        result.append(func(arg))
    return result

def main():
    arg_list = [5, 10]
    squares = bind(square, arg_list)
    print (squares)
```
결과 [7, 12]
### High-order-function
High-order-function이란 2가지 중 하나이상을 만족하는 함수
- 함수를 파라미터로 전달 받는 함수
- 함수를 리턴하는 함수
```
LOWER_LIST = ["python", "python2", "python3"]
UPPER_LIST = []

def convert(data):
    return data.upper()

def main():
    print ("=== print result ===")
    UPPER_LIST = map(convert, LOWER_LIST)
    print (LOWER_LIST)
    print (list(UPPER_LIST))
```
결과
```
=== print result ===
['python', 'python2', 'python3']
['PYTHON', 'PYTHON2', 'PYTHON3']
```
### Nested function
- 함수 내부에 정의된 또 다른 함수
- 중첩함수는 해당 함수가 정의된 함수 내에서 호출 및 반환 가능
```
def calculator(x):

    def add(y):
        return x+y

    return add


if __name__ == "__main__":
    print ("=== print calculation ===")
    f = calculator(10)
    print (f(5))
    print (f(10))
```
### closure function
함수와 해당 함수가 가지고 있는 데이터를 함께 복사, 저장해서 별도 함수로 활용하는 기법으로 First-class 함수와 동일\
외부 함수가 소멸되더라도, 외부 함수 안에 있는 로컬 변수 값과 중첩함수(내부함수)를 사용할 수 있는 기법
```
import datetime
import time

def logger(group):
    def print_log(msg):
        now = datetime.datetime.now()
        return ("%s [%s] %s" % (now, group, msg))
    return print_log
def main():
    log = logger("ERROR")
    print (log("log"))
    print (log("log2"))
if __name__ == "__main__":
    main()
```
```
2018-07-03 10:41:51.051808 [ERROR] log
2018-07-03 10:41:51.052440 [ERROR] log2
```
## Partial Application
### *args **kwargs
```
def test(name, *args, **kwargs):
    print ("=== fixed argument ===")
    print ("Fixed argument : %s" % name)

    print ("=== args list ===")
    for arg in args:
        print ("Argument : %s" % arg)

    print ("=== kwargs list ===")
    for keyword, arg in kwargs.items():
        print ("Argument keyword : %s, arg : %s" % (keyword, arg))

def main():
    args = ["red", "blue", "first", "second"]
    kwargs = {"red":"color", "blue":"color", "first":"number", "second":"number"}


    test("python", *args, **kwargs)
    test("python", "red", "blue", "green", red="color", blue="color")


if __name__ == "__main__":
    main()
```
```
=== fixed argument ===
Fixed argument : python
=== args list ===
Argument : red
Argument : blue
Argument : green
=== kwargs list ===
Argument keyword : blue, arg : color
Argument keyword : red, arg : color
```
### Closure를 이용한 Partial Application
```
def partial(func, *partial_args):
    def wrapper(*extra_args):
        args = list(partial_args)
        args.extend(extra_args)
        return func(*args)
    return wrapper

def logging(year, month, day, title, content):
    print ("%s-%s-%s %s:%s" % (year, month, day, title, content))

def main():
    print ("=== use logging function ===")
    logging("2017", "12", "28", "python2", "End of support in 2020")
    logging("2017", "12", "28", "python3", "Updating")

    print ("=== use partial function ===")
    f = partial(logging, "2017", "12", "28")
    f("python2", "End of support in 2020")
    f("python3", "Updating")


if __name__ == "__main__":
    main()
```

```
=== use logging function ===
2017-12-28 python2:End of support in 2020
2017-12-28 python3:Updating
=== use partial function ===
2017-12-28 python2:End of support in 2020
2017-12-28 python3:Updating
```
### 파이썬 내장 모듈 partial를 사용예
```
from functools import partial

def logging(year, month, day, title, content):
    print ("%s-%s-%s %s:%s" % (year, month, day, title, content))

def main():
    print ("=== use partial function ===")
    f = partial(logging, "2017", "12", "28")
    f("python2", "End of support in 2020")
    f("python3", "Updating")
```
## Decorator
```
def deco(func):
    def wrapper():
        print ("before")
        ret = func()
        print ("after")
        return ret
    return wrapper

@deco
def base():
    print ("base function")

print ("start")
base()
```
결과
```
start
before
base function
after
```
### 다중 Decorator
데코레이터를 여러개 사용할 경우 가장 밑에 작성된 데코레이터부터 실행
```
import time
import datetime

def measure_run_time(func):

    def wrapper(*args, **kwargs):
        print ("[measure_run_time] args : %s, kwargs : %s" % (args, kwargs))
        result = func(*args, **kwargs)
        print ("[measure_run_time] end")
        return result
    return wrapper

def parameter_logger(func):

    def wrapper(*args, **kwargs):
        print ("[parameter_logger] args : %s, kwargs : %s" % (args, kwargs))
        result = func(*args, **kwargs)
        print ("[parameter_logger] end")
        return result
    return wrapper

@measure_run_time
@parameter_logger
def worker(delay_time):
    time.sleep(delay_time)

worker(1)
```

### 클래스 Decorator
```

import time
from functools import update_wrapper

class MeasureRuntime:
    def __init__(self, f):
        print ("[MeasureRuntime] __init__")
        self.func = f
        update_wrapper(self, self.func)
    def __call__(self, *args, **kwargs):
        print ("[MeasureRuntime] __call__")
        start = time.time()
        result = self.func(*args, **kwargs)
        end = time.time()
        print ("[MeasureRuntime]'%s' function running time : %s" % (self.func.__name__, end - start))
        print ("[MeasureRuntime] __call__ end")
        return result

@MeasureRuntime
def worker(delay_time):
    print ("[worker] start")
    time.sleep(delay_time)
    print ("[worker] end")
    
if __name__ == "__main__":
    print ("[main] start")
    worker(5)
    print ("[main] end")
```
결과
```
[MeasureRuntime] __init__
[main] start
[MeasureRuntime] __call__
[worker] start
[worker] end
[MeasureRuntime]'worker' function running time : 5.0057079792022705
[MeasureRuntime] __call__ end
[main] end
```

## Iterator
```
def main():
    x = [1, 2, 3]
    x_iterator = iter(x)

    print ("=== print iterator ===")
    print (next(x_iterator))
    print (next(x_iterator))
    print (next(x_iterator))
    print (next(x_iterator))

if __name__ == "__main__":
    main()
```
결과
```    
def main():
    x = [1, 2, 3]
    x_iterator = iter(x)

    print ("=== print iterator ===")
    print (next(x_iterator))
    print (next(x_iterator))
    print (next(x_iterator))
    print (next(x_iterator))

if __name__ == "__main__":
    main()
```
## Generator
Generator는 Iterator 인터페이스를 쉽고 유연하게 구현할 수 있는 방법을 제공합니다.\
Iterator는 이미 메모리에 전부 올라와 있거나, 모두 메로리로 올려도 부담이 없는 작은 규모의 데이터에 적합\
큰 데이터를 다루는 경우에는, 성능 및 자원 관리의 측면에 있어서라도 부분적인 접근에 따라 생성 또는 접근하는 것이 효율적이라 generator를 이용

### Yield 구문
```
def gen():
    yield 1
    yield 2
    yield 3

def main():
    print ("=== print gen function in loop ===")
    for g in gen():
        print (g)

main()
```
결과
```
=== print gen function in loop ===
1
2
3
```
### Stateful Generator

```
def gen(items):
    count = 0
    for item in items:
        if count == 5:
            return -1
        count += 1
        yield item
if __name__ == "__main__":
    print ("=== print gen ===")
    for i in gen(range(15)):
        print (i)
```
결과
```
=== print gen ===
0
1
2
3
4
```
## Comprehension & Expression
Comprehension & Expression는 코드를 더 간결하게 작성하기 위한 문법\
Lambda식과 유사하지만 보다 간결하고 직관적으로 사용이 가능
```
v_list = [1, 2, 3]
v_dict_key = ["korea", "japen", "china"]
v_dict_value = [82, 81, 86]

def print_list_with_comprehension():
    v_list_comprehension = [x*x for x in v_list]
    print (v_list_comprehension)
def print_dict_with_comprehension():
    v_dict_comprehension = {k:v for k, v in zip(v_dict_key, v_dict_value)}
    print (v_dict_comprehension)
print ("=== print list ===")
print (v_list)
print_list_with_comprehension()

print ("=== print dict ===")
print (v_dict_key)
print (v_dict_value)
print_dict_with_comprehension()
```
결과
```
=== print list ===
[1, 2, 3]
[1, 4, 9]
=== print dict ===
['korea', 'japen', 'china']
[82, 81, 86]
{'china': 86, 'japen': 81, 'korea': 82}
```
### Generator Expression
```
SAMPLE_LIST = [1, 2, 3, 4, 5]

def generate_sample_list():
    result = (x*x for x in SAMPLE_LIST)
    print (result)
    return result

def print_generator(items):
    for item in items:
        print (item)

print ("=== print list ===")
print_generator(generate_sample_list())
```
### Lazy Evaluation
계산의 결과값이 필요할 때까지 계산을 늦추는 기법\
아래예에서 generator expression의 경우 wait_return 함수가 리스트를 만드는 시점에 호출된것이 아니라 실제 값을 출력하는 print_items 함수에서 실행

```
import time

def wait_return(num):
    print ("sleep")
    time.sleep(0.5)
    return num

def print_items(items):
    for i in items:
        print (i)

print ("=== print list comprehension ===")
iterator_list = [wait_return(i) for i in range(3)]
print ("start print")
print_items(iterator_list)

print ("=== print generator expression ===")
iterator_list = (wait_return(i) for i in range(3))
print ("start print")
print_items(iterator_list)
```
결과
```
=== print list comprehension ===
sleep
sleep
sleep
start print
0
1
2
=== print generator expression ===
start print
sleep
0
sleep
1
sleep
2
```
### Equality vs Identity
True/False를 비교할때는 if문에 변수만 사용\
- 동일성(identity) 확인은 *is* 나 *is not* 사용\
- - 동일한 변수인지를 확인
- - Equality 보다 속도가 빠르다
- 동등성(Equality) 확인은 = 나 != 연산자 사용
- - 변수의 값을 확인
```
$ python3
Python 3.5.2 (default, Nov 23 2017, 16:37:01)
[GCC 5.4.0 20160609] on linux
Type "help", "copyright", "credits" or "license" for more information.
>>> print (999 is 999)
True
>>> x = 999; y = 999;
>>> print (x is y)
True
>>> z = 999;
>>> print (x is z)
False
>>> print (id(x))
139950066208560
>>> print (id(y))
139950066208560
>>> print (id(z))
139950042394704
>>> print (x == y)
True
>>> print (x == z)
True
```
## Thread
### Function Thread
```
import threading

def worker(count):
    print ("name : %s, argument : %s" % (threading.currentThread().getName(), count))

def main():
    for i in range(5):
        t = threading.Thread(target=worker, name="thread %i" % i, args=(i,))
        t.start()
if __name__ == "__main__":
    main()
```
결과
```
name : thread 0, argument : 0
name : thread 1, argument : 1
name : thread 2, argument : 2
name : thread 3, argument : 3
name : thread 4, argument : 4
```
### Class Thread
```
import threading

class Worker(threading.Thread):

    def __init__(self, args, name=""):
        threading.Thread.__init__(self)
        self.args = args

    def run(self):
        print ("name : %s, argument : %s" % (threading.currentThread().getName(), self.args[0]))


def main():
    for i in range(5):
        t = Worker(name="thread %i" % i, args=(i,))
        t.start()


if __name__ == "__main__":
    main()
```
### Thread Logging
t.setDaemon(True)로 할경우 main이 종료가 되면 해당 thread 모두가 종료가 되는 반면 False나 없는경우는 thread가 모두 처리될때까지 main이 기다립니다.
```
import time
import logging
import threading

logging.basicConfig(level=logging.DEBUG, format="name : %(threadName)s, argument : %(message)s")

def worker(count):
    logging.debug(count)

def main():
    for i in range(5):
        t = threading.Thread(target=worker, name="thread %i" % i, args=(i,))
        #t.setDaemon(True)
        t.start()
if __name__ == "__main__":
    main()
```
결과
```
name : thread 0, argument : 0
name : thread 1, argument : 1
name : thread 2, argument : 2
name : thread 3, argument : 3
name : thread 4, argument : 4
```
### Thread Example

```

import time
import logging
import threading


logging.basicConfig(level=logging.DEBUG, format="(%(threadName)s) %(message)s")


class ResourcePool():

    def __init__(self):
        self.active_thread_list = []
        self.lock = threading.Lock()

    def use(self, name):
        with self.lock:
            self.active_thread_list.append(name)
            logging.debug("List of threads in resource pool : %s", self.active_thread_list)

    def unuse(self, name):
        with self.lock:
            self.active_thread_list.remove(name)
            logging.debug("List of threads in resource pool : %s", self.active_thread_list)


def worker(semaphore, pool):
    logging.debug("Waiting to enter the pool.")
    time.sleep(1)
    with semaphore:
        logging.debug("Enter the pool.")
        thread_name = threading.currentThread().getName()
        pool.use(thread_name)
        time.sleep(1)
        pool.unuse(thread_name)

def main():
    pool = ResourcePool()
    semaphore = threading.Semaphore(4)

    for i in range(5):
        t = threading.Thread(target=worker, name=("thread-%s" % i), args=(semaphore, pool))
        t.start()
    time.sleep(5)

if __name__ == "__main__":
    main()
```
결과
```
thread-0) Waiting to enter the pool.
(thread-1) Waiting to enter the pool.
(thread-2) Waiting to enter the pool.
(thread-3) Waiting to enter the pool.
(thread-4) Waiting to enter the pool.
(thread-0) Enter the pool.
(thread-1) Enter the pool.
(thread-0) List of threads in resource pool : ['thread-0']
(thread-2) Enter the pool.
(thread-3) Enter the pool.
(thread-1) List of threads in resource pool : ['thread-0', 'thread-1']
(thread-2) List of threads in resource pool : ['thread-0', 'thread-1', 'thread-2']
(thread-3) List of threads in resource pool : ['thread-0', 'thread-1', 'thread-2', 'thread-3']
(thread-0) List of threads in resource pool : ['thread-1', 'thread-2', 'thread-3']
(thread-4) Enter the pool.
(thread-4) List of threads in resource pool : ['thread-1', 'thread-2', 'thread-3', 'thread-4']
(thread-1) List of threads in resource pool : ['thread-2', 'thread-3', 'thread-4']
(thread-2) List of threads in resource pool : ['thread-3', 'thread-4']
(thread-3) List of threads in resource pool : ['thread-4']
(thread-4) List of threads in resource pool : []
```
### Thread local Data
threading.local()을 이용합니다.
```
import logging
import threading

logging.basicConfig(level=logging.DEBUG, format="(%(threadName)s) %(message)s")

def print_local_data(local_data, msg):
    try:
        data = local_data.index
    except:
        logging.debug("[%s] Value not set yet." % msg)
    else:
        logging.debug("[%s] value : %s" % (msg,data))
def set_local_data(local_data, index):
    print_local_data(local_data, "before")
    local_data.index = index
    print_local_data(local_data, "after")
def main():
    local_data = threading.local()   
    print_local_data(local_data, "before")
    local_data.index = 0
    print_local_data(local_data, "after")
    for i in range(5):
        t = threading.Thread(target=set_local_data, name=("thread-%s" % i), args=(local_data, i+1))
        t.start()
if __name__ == "__main__":
    main()
```
결과
```
(MainThread) [before] Value not set yet.
(MainThread) [after] value : 0
(thread-0) [before] Value not set yet.
(thread-1) [before] Value not set yet.
(thread-0) [after] value : 1
(thread-2) [before] Value not set yet.
(thread-1) [after] value : 2
(thread-3) [before] Value not set yet.
(thread-4) [before] Value not set yet.
(thread-2) [after] value : 3
(thread-3) [after] value : 4
(thread-4) [after] value : 5
```
## Multiprocess
### process logging
```
import logging
import multiprocessing

def worker(count):
    print ("count : %s" % count)
    logger = multiprocessing.get_logger()
    logger.info("count : %s" % count)

def main():
    multiprocessing.log_to_stderr()
    logger = multiprocessing.get_logger()
    logger.setLevel(logging.INFO)
    logger.info("start")

    for i in range(3):
        t = multiprocessing.Process(target=worker, args=(i,))
        t.start()

if __name__ == "__main__":
    main()
```
결과
```
[INFO/MainProcess] start
[INFO/MainProcess] process shutting down
[INFO/MainProcess] calling join() for process Process-2
[INFO/Process-1] child process calling self.run()
count : 0
[INFO/Process-2] child process calling self.run()
count : 1
[INFO/Process-3] child process calling self.run()
count : 2
[INFO/Process-1] count : 0
[INFO/Process-2] count : 1
[INFO/Process-3] count : 2
[INFO/Process-1] process shutting down
[INFO/Process-3] process shutting down
[INFO/Process-2] process shutting down
[INFO/Process-1] process exiting with exitcode 0
[INFO/Process-2] process exiting with exitcode 0
[INFO/Process-3] process exiting with exitcode 0
[INFO/MainProcess] calling join() for process Process-3
[INFO/MainProcess] calling join() for process Process-1
```
### process queue
```
import time
import multiprocessing

def set_data(q):
    p = multiprocessing.current_process()
    msg = "Hello World"
    q.put(msg)
    print ("[%s] set queue data : %s" % (p.name, msg))

def get_data(q):
    time.sleep(1)
    p = multiprocessing.current_process()
    print ("[%s] get queue data : %s" % (p.name, q.get()))

def main():
    queue = multiprocessing.Queue()

    p1 = multiprocessing.Process(name="set_data", target=set_data, args=(queue,))
    p1.start()

    p2 = multiprocessing.Process(name="get_data", target=get_data, args=(queue,))
    p2.start()

    p1.join()
    p2.join()

if __name__ == "__main__":
    main()
```
결과
```
[set_data] set queue data : Hello World
[get_data] get queue data : Hello World
```
### process pipe
```
import logging
import multiprocessing

def pipe_data(pipe):
    p = multiprocessing.current_process()
    logger = multiprocessing.get_logger()
    logger.info ("Send a message to pipe : %s" % p.name)
    pipe.send(p.name)
    logger.info ("wait msg")
    logger.info ("Recieved message : %s" % pipe.recv())
 
def main():
    multiprocessing.log_to_stderr()
    logger = multiprocessing.get_logger()
    logger.setLevel(logging.INFO)

    parent_pipe, child_pipe = multiprocessing.Pipe()
    p1 = multiprocessing.Process(name="child", target=pipe_data, args=(child_pipe,))
    p2 = multiprocessing.Process(name="parent", target=pipe_data, args=(parent_pipe,))
    p1.start()
    p2.start()
    p1.join()
    p2.join()

if __name__ == "__main__":
    main()
```
결과
```
[INFO/child] child process calling self.run()
[INFO/parent] child process calling self.run()
[INFO/child] Send a message to pipe : child
[INFO/parent] Send a message to pipe : parent
[INFO/child] wait msg
[INFO/parent] wait msg
[INFO/child] Recieved message : parent
[INFO/parent] Recieved message : child
[INFO/child] process shutting down
[INFO/parent] process shutting down
[INFO/child] process exiting with exitcode 0
[INFO/parent] process exiting with exitcode 0
[INFO/MainProcess] process shutting down
```
## Coroutine
```

import time
import random
import logging

TOTAL_WORK_LOAD = 20

def worker():
    total_work_load = 0
    worker_name = ""

    while True:
        print ("[%s] 1 wait" % worker_name)
        worker_name, total_work_load = yield (worker_name, total_work_load)
        work_load = random.randrange(1, 10)
        print ("[%s] 2 total_work_load : %s, work_load : %s" % (worker_name, total_work_load, work_load))
        work_load = work_load if total_work_load >= work_load else total_work_load
        total_work_load -= work_load
        print ("[%s] 3 Total : %s, work : %s" % (worker_name, total_work_load, work_load))
        yield total_work_load

def main():
    w1 = worker()
    w2 = worker()

    ret = TOTAL_WORK_LOAD
    while ret > 0:
        next(w1)
        ret = w1.send(("w1", ret))
        next(w2)
        ret = w2.send(("w2", ret))

if __name__ == "__main__":
    main()
```
결과
```
[] 1 wait
[w1] 2 total_work_load : 20, work_load : 8
[w1] 3 Total : 12, work : 8
[] 1 wait
[w2] 2 total_work_load : 12, work_load : 3
[w2] 3 Total : 9, work : 3
[w1] 1 wait
[w1] 2 total_work_load : 9, work_load : 2
[w1] 3 Total : 7, work : 2
[w2] 1 wait
[w2] 2 total_work_load : 7, work_load : 6
[w2] 3 Total : 1, work : 6
[w1] 1 wait
[w1] 2 total_work_load : 1, work_load : 9
[w1] 3 Total : 0, work : 1
[w2] 1 wait
[w2] 2 total_work_load : 0, work_load : 1
[w2] 3 Total : 0, work : 0
```
## Future
### Future
```
import time
import concurrent.futures

def worker(index):
    print ("Worker Index : %s" % index)
    time.sleep(index)
    return ("Completed %s worker job" % index)
def main():
    with concurrent.futures.ProcessPoolExecutor(max_workers=3) as executor:
        future_list = []
        for i in range(5):
            future = executor.submit(worker, i)
            future_list.append(future)

        finished, pending = concurrent.futures.wait(future_list, timeout=2,
                                return_when=concurrent.futures.ALL_COMPLETED)

        for w in finished:
            print ("Finished worker : %s" % w.result())

        for w in pending:
            print ("Not finished worker : %s" % w.result())
if __name__ == "__main__":
    main()
```
결과
```
Worker Index : 0
Worker Index : 1
Worker Index : 2
Worker Index : 3
Worker Index : 4
Finished worker : Completed 1 worker job
Finished worker : Completed 0 worker job
Not finished worker : Completed 3 worker job
Not finished worker : Completed 2 worker job
Not finished worker : Completed 4 worker job
```
## Asyncio
```
import asyncio
import random
import datetime
import logging

logging.basicConfig(level=logging.DEBUG, format="%(asctime)-15s [%(threadName)s] %(message)s")

@asyncio.coroutine
def print_time(idx):
    sleep_time = random.randrange(1, 10)
    yield from asyncio.sleep(sleep_time)
    logging.debug ("[%s] Sleep time : %s, Complete time : %s" % (idx, sleep_time, datetime.datetime.now()))

def main():
    logging.debug("start");
    futures = [print_time(i) for i in range(10)]
    loop = asyncio.get_event_loop()
    loop.run_until_complete(asyncio.wait(futures))
    loop.close()

if __name__ == "__main__":
    main()
```
결과
```
2018-07-05 17:21:43,323 [MainThread] start
2018-07-05 17:21:43,324 [MainThread] Using selector: EpollSelector
2018-07-05 17:21:44,335 [MainThread] [2] Sleep time : 1, Complete time : 2018-07-05 17:21:44.334906
2018-07-05 17:21:44,337 [MainThread] [0] Sleep time : 1, Complete time : 2018-07-05 17:21:44.337290
2018-07-05 17:21:46,334 [MainThread] [1] Sleep time : 3, Complete time : 2018-07-05 17:21:46.333862
2018-07-05 17:21:47,334 [MainThread] [3] Sleep time : 4, Complete time : 2018-07-05 17:21:47.334067
2018-07-05 17:21:48,333 [MainThread] [7] Sleep time : 5, Complete time : 2018-07-05 17:21:48.333280
2018-07-05 17:21:49,335 [MainThread] [5] Sleep time : 6, Complete time : 2018-07-05 17:21:49.335043
2018-07-05 17:21:51,335 [MainThread] [8] Sleep time : 8, Complete time : 2018-07-05 17:21:51.335038
2018-07-05 17:21:51,337 [MainThread] [9] Sleep time : 8, Complete time : 2018-07-05 17:21:51.337434
2018-07-05 17:21:52,335 [MainThread] [4] Sleep time : 9, Complete time : 2018-07-05 17:21:52.335569
2018-07-05 17:21:52,338 [MainThread] [6] Sleep time : 9, Complete time : 2018-07-05 17:21:52.338192
```


## Reference
<https://github.com/bjpublic/pythonic>
