def mult_check(list, n):
    result_list = []
    result = 0
    for k in list:
        for i in range(0, n, k):
            if i % k == 0:
                if not i in result_list:
                    result_list.append(i)
                    result += i
    return result

print(mult_check([3,5], 1000))
