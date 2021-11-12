INITIAL_BASE = 0x1100
MEDIAL_BASE = 0x1161
FINAL_BASE = 0x11a7  # 0x11a8?


def main():
    while True:
        user_input = list(input("Please input Hangul\n>>> "))
        buffer = []
        for char in user_input:
            if char.isspace():
                buffer.append(char)
            else:
                base = ord(char) - 0xac00
                initial = ((base // 21 // 28) % 19) + INITIAL_BASE
                medial = ((base // 28) % 21) + MEDIAL_BASE
                final = (base % 28) + FINAL_BASE
                buffer.append(chr(initial))
                buffer.append(chr(medial))
                buffer.append(chr(final))
        print(buffer)
        print("".join(buffer))


if __name__ == '__main__':
    main()
