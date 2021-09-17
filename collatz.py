from matplotlib import pyplot as plt


def T(n):
    if n % 2:
        return 3 * n + 1
    else:
        return n // 2


def main():
    plt.figure(figsize=(16, 9))
    for i in range(2, 40 + 1, 2):
        I = i
        temp = [i]
        while i != 1:
            i = T(i)
            temp.append(i)
        plt.plot(temp, label=I)
    plt.legend()
    plt.show()


if __name__ == '__main__':
    main()
