def main():
    _sum = 0
    while True:
        try:
            a, b = map(int, input().split(" "))
            difference = a - b
            _sum += difference
        except EOFError:
            break
    return 0


if __name__ == '__main__':
    main()
