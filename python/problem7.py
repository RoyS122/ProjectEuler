def get_list_prime(n):
    list = []
    i = 1
    l_list = 0
    while l_list != 10001:
        i += 1
        is_p = True
        for k in list:
            if i % k == 0:
                is_p = False
                break;

        if is_p == True:
            list.append(i)
            l_list += 1

    return list

last = get_list_prime(6)
last = last[len(last) - 1]
print(last)
