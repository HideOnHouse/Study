import random
import os
import time


def main():
    for i in [1000, 10000, 100000, 1000000, 10000000]:
        with open(r'C:\Users\FURO\PycharmProjects\Study\cmake-build-debug\input.txt', 'w') as f:
            for _ in range(i):
                a, b = random.randint(-100, 100), random.randint(-100, 100)
                f.write(f"{a} {b}\n")
        start = time.time()
        os.system(
            r'C:\Users\FURO\PycharmProjects\Study\cmake-build-debug\string_parse.exe < C:\Users\FURO\PycharmProjects\Study\cmake-build-debug\input.txt')
        end = time.time()
        c_time = end - start
        print(f"====={i} Lines to parse=====")
        print(f'C      execution time: {c_time}')
        start = time.time()
        os.system(
            r'python C:\Users\FURO\PycharmProjects\Study\Misc\string_parse.py < C:\Users\FURO\PycharmProjects\Study\cmake-build-debug\input.txt')
        end = time.time()
        p_time = end - start
        print(f'Python execution time: {p_time}')
        print(f"Python {p_time // c_time}x slower than C")


if __name__ == '__main__':
    main()
