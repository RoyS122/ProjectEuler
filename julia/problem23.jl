function getFactors(nbr) 
    divisors = []
    # println("test")
    for n in 1:nbr/2 + 1 
        if nbr % n == 0 
            push!(divisors, n)
        end
    end
    
    return divisors
end

function isAbundant(nbr) 
    factors = getFactors(nbr)
    if sum(factors) > nbr 
        return true
    else 
        return false
    end
end

function nonAbundantSum() 
    tot = 0
    max_num = 28123
    abundants = []
    can_be_write = falses(max_num)

    for n in 12:max_num
        if isAbundant(n)
            push!(abundants, n)
        end
    end

    for c1 in eachindex(abundants) 
        for c2 in c1:length(abundants)
            sum = abundants[c1] + abundants[c2]
            if sum  <= max_num
                can_be_write[sum] = true
            else
                break
            end 
        end
    end
    for n in 1:max_num 
        if !can_be_write[n]
            tot += n
        end
    end
    return tot
end
println(nonAbundantSum())
