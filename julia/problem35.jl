function CircularPrime(before::BigInt)
    PrimeArray = GetPrimeNumbersUntil(before, [BigInt(2)])
    println(GetCircularPrimeAmmount(PrimeArray))
end

function isPrime(v::BigInt, array::Vector{BigInt})
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

function getDigits(nbr::BigInt)::Vector{UInt8}
    listnbr = Vector{UInt8}()
    while nbr > 0
        push!(listnbr, UInt8(nbr % 10))
        nbr ÷= 10
    end
    return reverse(listnbr)  # Reverse the digits to keep the correct order
end

function GetCircularPrimeAmmount(array::Vector{BigInt})
    count = 0
    for d in array
        isAllPrime = true
        rotations = getRotations(d)
        for rot in rotations
            if !isPrime(rot, array)
                isAllPrime = false
                break
            end
        end
        if isAllPrime
            count += 1
        end
    end
    return count
end

function getRotations(nbr::BigInt)::Vector{BigInt}
    digits = getDigits(nbr)
    rotations = Vector{BigInt}()
    push!(rotations, nbr)

    for i in 1:length(digits)-1
        digits = [digits[end]; digits[1:end-1]]  # Move the last digit to the front
        rotated = reduce((x, y) -> 10*x + y, digits)  # Convert digits back to number
        push!(rotations, rotated)
    end
    return rotations
end

function GetPrimeNumbersUntil(until::BigInt, array::Vector{BigInt})::Vector{BigInt}
    for i in array[end]+1:2:until
        if isPrime(i, array)
            push!(array, BigInt(i))
        end
    end
    return array
end

CircularPrime(BigInt(1000000))
