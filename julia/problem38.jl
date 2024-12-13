function isPandigit(nbr::BigInt)::Bool # Check if the number is a pandigit
    digits = Set{Int}()
    original_length = 0

    while nbr > 0
        digit = nbr % 10
        if digit == 0  
            return false
        end
        push!(digits, digit)
        nbr ÷= 10
        original_length += 1
    end

    return original_length == 9 && length(digits) == 9
end

function getMaxPandigitalDigit()::BigInt # Solve the problem
    max_pandigital = BigInt(0)
    
    for i in 1:10^4-1
        concatenated = ""
        j = 1
        while length(concatenated) < 9
            concatenated *= string(i * j)
            j += 1
        end
        if length(concatenated) == 9
            pandigital_candidate = parse(BigInt, concatenated)
            if isPandigit(pandigital_candidate) && pandigital_candidate > max_pandigital
                max_pandigital = pandigital_candidate
            end
        end
    end
    
    return max_pandigital
end

println(getMaxPandigitalDigit())
