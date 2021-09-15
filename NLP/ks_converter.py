import pickle


def main():
    with open(r'./convert_table.pickle', 'rb') as f:
        converter = pickle.load(f)

    while True:
        string = input("Input string to convert: ")
        for i in list(string):
            if i in converter:
                print(converter[i], end=" ")
            else:
                print(f"Invalid Char {i}", end=" ")
        print()


if __name__ == '__main__':
    main()
