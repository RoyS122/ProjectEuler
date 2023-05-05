def smallest_divisibleby(n):
    i = 1
    divisible = False
    while divisible == False:
        i += 1
        divisible = True
        for j in range(1, n + 1):
            if i % j != 0:
                divisible = False
                break

    return i

print(smallest_divisibleby(20))
