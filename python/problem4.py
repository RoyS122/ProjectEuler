def is_palindrome(nbr):
    s_nbr = str(nbr)
    r_side, l_side = s_nbr[len(s_nbr) // 2:], s_nbr[:len(s_nbr) // 2]
    if l_side == "".join(list(reversed(r_side))):   return True
    return False

def get_largest_palindrome():
    max = 0
    for i in range(100, 999):
        for j in range(100, 999):
            if is_palindrome(i * j) == True:
                if max < i * j:
                    max = i * j
    return max

print(get_largest_palindrome())
