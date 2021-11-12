import re


def bigram(string: str):
    tokenized = []
    for i in range(0, len(string) - 1):
        tokenized.append(string[i:i + 2])
    return " ".join(tokenized)


def tokenize(string: str):
    # 아스키 문자열 분리
    chars = re.findall(r'[\x00-\x7f]+', string, re.IGNORECASE)
    for i in chars:
        string = string.replace(i, f" {i} ", 1)

    # 한글 이외 문자열 분리
    chars = re.findall(r'[^가-힣]+', string, re.IGNORECASE)
    for i in chars:
        string = string.replace(i, f" {i} ", 1)

    # 한글 텍스트 부분을 추출한 후에 bigram 음절로 분리하여 저장
    words = re.findall(r'\b[가-힣]+\b', string)
    for i in words:
        replaced = bigram(f"_{i}_")
        string = string.replace(i, f" {replaced} ", 1)
    string = re.sub(" +", " ", string)
    return string


def cosine_similarity(u: dict, v: dict):
    u_length = sum(i ** 2 for i in u.values()) ** 0.5
    v_length = sum(i ** 2 for i in v.values()) ** 0.5
    dot = sum([j * v[i] for i, j in u.items() if i in v])
    return dot / ((u_length * v_length) + 1e-5)

