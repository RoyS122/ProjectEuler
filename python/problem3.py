def prime_factor(n):
    prime_list = [2]
    pfl = []
    for i in range(3, n, 2):
        is_prime = True
        for k in prime_list:
            if i % k == 0:
                is_prime = False
                break;
        if is_prime == True :
            prime_list.append(i)
            if n % i == 0:
                pfl.append(i)
                print(pfl)

    return pfl




n = 600851475143
i = 2
while i * i < n:
    while n % i == 0:
        n = n / i
    i = i + 1

print(n)
