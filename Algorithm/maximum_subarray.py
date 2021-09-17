def find_maximum_cross_subarray(arr, left, mid, right):
    l_sum = -2 ** 32
    temp = 0
    max_left, max_right, max_sum = left, right, 0
    for i in range(mid, left - 1, -1):
        temp += arr[i]
        if temp > l_sum:
            l_sum = temp
            max_left = i
    r_sum = -2 ** 32
    temp = 0
    for i in range(mid + 1, right + 1):
        temp += arr[i]
        if temp > r_sum:
            r_sum = temp
            max_right = i
    max_sum = l_sum + r_sum
    return max_left, max_right, max_sum


def find_maximum_subarray(arr, left, right):
    if left == right:
        return left, right, arr[left]
    else:
        mid = (left + right) // 2
        l_left, l_right, l_sum = find_maximum_subarray(arr, left, mid)
        r_left, r_right, r_sum = find_maximum_subarray(arr, mid + 1, right)
        m_left, m_right, m_sum = find_maximum_cross_subarray(arr, left, mid, right)
        max_sum = max([l_sum, m_sum, r_sum])
        if max_sum == l_sum:
            return l_left, l_right, l_sum
        elif max_sum == m_sum:
            return m_left, m_right, m_sum
        else:
            return r_left, r_right, r_sum
