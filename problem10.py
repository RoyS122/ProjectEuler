def get_sum_prime(n):

    p_list = [2, 3, 5]
    sum = 2 + 3 + 5
    for i in range(5, n, 2):
        is_p = True
        for k in p_list:
            if i % k == 0:
                is_p = False

        if is_p:
            if i * i < n:
                p_list.append(i)

            sum += i


    return sum

print(get_sum_prime(2000000))
