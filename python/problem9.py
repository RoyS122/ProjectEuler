def is_a_triplet(a,b,c):
    if a * a + b * b == c * c:
        return True

    return False

print(is_a_triplet(3,4,5))
for a in range(1000):
    for b in range(a + 1, 1000):
        for c in range(b + 1, 1000):
            if a + b + c == 1000 and is_a_triplet(a,b,c) == True:
                print(a*b*c)

print(is_a_triplet(3,4,5))
