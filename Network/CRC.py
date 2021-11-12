def get_crc(d, g):
    r = 0
    temp = g
    while temp > 1:
        temp >>= 1
        r += 1
    d = d << (r + 1)

    print(bin(r))


def main():
    d = 0b101110
    g = 0b1001
    get_crc(d, g)


if __name__ == '__main__':
    main()
