import os
import time


def main():
    start = time.time()
    os.system(r'C:\Users\FURO\PycharmProjects\Study\cmake-build-debug\dynamic_alloc.exe')
    end = time.time()
    c_time = end - start
    print(f'C      execution time: {c_time}')
    start = time.time()
    os.system(r'python C:\Users\FURO\PycharmProjects\Study\Misc\dynamic_alloc.py')
    end = time.time()
    p_time = end - start
    print(f'Python execution time: {p_time}')
    print(f"Python {p_time // c_time}x slower than C")


if __name__ == '__main__':
    main()
