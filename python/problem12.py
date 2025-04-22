def get_divisor(n):
    res = 0
    for i in range(1, int(n ** 0.5)):
        if n % i == 0:
            res += 2
    return res



def first_tn_div(x):
    n = 0
    max = 0
    found = False
    while found == False:
        n += 1
        tri = int(1/2 * (n*n + n))
        d = get_divisor(tri)
        if d > max:
            max = d
        if  d > x:
            found = True
    return tri

print(first_tn_div(501))
