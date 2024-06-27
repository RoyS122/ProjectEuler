def fibo_even(max_term):
    n = 1
    last_two = [0,0]
    even_sum = 0
    while n < max_term:
        last_two.pop(0)
        last_two.append(n)
        n = last_two[0] + last_two[1]
        if n % 2 == 0:
            even_sum += n
    return even_sum

print(fibo_even(4000000))
