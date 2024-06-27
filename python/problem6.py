def sum_square(n):
    r = 0
    for i in range(1, n + 1):
        r += i ** 2
    return r

def square_sum(n):
    r = 0
    for i in range(1, n +1):
        r += i
    return r ** 2

print(square_sum(100) - sum_square(100))
