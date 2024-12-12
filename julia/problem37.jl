function getDigits(nbr::BigInt, base::Int)::Vector{UInt8} # Get the digits of a number
    listnbr = Vector{UInt8}()
    while nbr > 0
        push!(listnbr, UInt8(nbr % base))
        nbr ÷= base
    end
    return reverse(listnbr)
end

function isPrime(v::BigInt, array::Vector{BigInt})::Bool # Check if a number is prime
    if v < 2
        return false
    end
    limit = floor(BigInt, sqrt(v))
    for k in array
        if k > limit
            break
        end
        if v % k == 0
            return false
        end
    end
    return true
end

function GetPrimeNumbersUntil(until::BigInt, array::Vector{BigInt})::Vector{BigInt} # Get a list of prime number until a defined number
    for i in array[end] + 1:2:until
        if isPrime(i, array)
            push!(array, BigInt(i))
        end
    end
    return array
end

function isTruncable(nbr::BigInt, prime_array::Vector{BigInt}, right::Bool)::Bool # Check if number is truncable (with the direction at the last argument)
  
    if !isPrime(nbr, prime_array) 
        return false
    end 
    digits_l = getDigits(nbr, 10) 
    if length(digits_l) <= 1
        return true
    end 
    digit_as_str = join(digits_l)
    
    if right
        truncated_right = parse(BigInt, digit_as_str[1:end-1], base=10)
        if !isTruncable(truncated_right, prime_array, true)
            return false
        end
    else
        truncated_left = parse(BigInt, digit_as_str[2:end], base=10)
        if !isTruncable(truncated_left, prime_array, false)
            return false
        end
    end
    return true 
end

function getTruncablePrimeNumber()::Vector{BigInt} # Get the list of truncables prime numbers
    truncables = Vector{BigInt}()
    primes = Vector{BigInt}([2])
    primes = GetPrimeNumbersUntil(BigInt(10^6), primes)
    for i in primes[5:end]
        if isTruncable(i, primes, true) && isTruncable(i, primes, false) && i > 7
            println("Troncable trouvé : $i")
            push!(truncables, i)
        end
    end
    
    return truncables
end


println(sum(getTruncablePrimeNumber()))