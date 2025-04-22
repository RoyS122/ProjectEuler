def factorial(n: int):
    if n == 1: 
        return 1
    return n * factorial(n - 1)


print(sum([int(x) for x in str(factorial(100))]))