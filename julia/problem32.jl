function isPandigit(nbr::BigInt)::Bool # Check if the number is a pandigit number
    digits = Set{Int}()
    original_length = 0

    while nbr > 0
        digit = nbr % 10
        push!(digits, digit)
        nbr ÷= 10
        original_length += 1
    end

    if original_length != length(digits)
        return false
    end

    for d in digits
        if d < 1 || d > original_length
            return false
        end
    end

    return true
end

function getDigitLength(nbr::BigInt)::Int # Return the number if digit
    original_length = 0
    while (nbr > 0)
        nbr ÷= 10
        original_length += 1
    end
    return original_length
end 
function concatInt(a::BigInt, b::BigInt)::BigInt
    return BigInt(a * (10^getDigitLength(b) ) + b);
end
function getSumOfPandigitProduct()::Int 
    products = Set{BigInt}()

    for a in 1:99 
        for b in 1:9999
            prod = BigInt(a) * BigInt(b)
            check = concatInt(concatInt(BigInt(a),BigInt(b)), prod)
            if getDigitLength(check) != 9
                continue 
            end
            
            if isPandigit(check)
                push!(products, prod)
            end
        end 
    end 
    return sum(products)
end 
println(getSumOfPandigitProduct())  # Test case



