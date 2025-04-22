function first1000Digits(n1, n2)
    step = 2  # Start at 2 because on fibonacci we considere the n1 is the first step(n2 the second)
    n1 = BigInt(n1) # I convert the n1 and n2 in big Int because standard int have a maximum too low(bigInt process the integer with dynamic memory alloc)
    n2 = BigInt(n2)
    DigitCheck = BigInt(10)^999 
    while (n1 < DigitCheck && n2 < DigitCheck)
        newN1 = n1 + n2
        newN2 = n2 * 2 + n1 
        n1 = newN1
        n2 = newN2
        
        step += 2
    end

    if length(string(n1)) >= 1000 
        return step - 1
    end
    return step, length(string(n1)), length(string(n2)) # Return the result
end

println(first1000Digits(1, 1))