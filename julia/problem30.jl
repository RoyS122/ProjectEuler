function digitXpowers(x)
    total = []
    # We are searching the max value of the sum of n digits power x 
    # With the formula n * (9 power x) 
    # If the check value (the value of 10 power x) is behind the maxvalue we reach the max value to check after
    check = 10
    ndigit = 2
    valeurmax = ndigit * (9 ^ x)
    while (check < valeurmax) 
        ndigit += 1
        valeurmax = ndigit * (9 ^ x)
        check *= 10

    end
    
    for num in 10:354294  # Parcours de tous les nombres pertinents
        digit = digits(num)  # Obtenez les chiffres de num
        if sum(d -> d^x, digit) == num  # Comparez la somme des 5e puissances
            push!(total, num)
        end
    end
    return total
end

println(sum(digitXpowers(5)))
