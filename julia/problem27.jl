primelist = [2] # Initialize the primelist to optimize loading time



function isPrime(val::Int) # Check if a number is a prime number and add it to the prime list if it's 
    if val == 1 || val < 0
        return false
    end
    for p in primelist
        if p == val 
            return true
        end 
        if val % p == 0
            return false
        end
    end
    push!(primelist, val)
    return true
end

function quadratic(a::Int, b::Int, n::Int) # Get the result of the quadratic formula
    return n*n + a*n + b
end 

function getPrimeConsecutiveLength(a::Int, b::Int) # Return the length of the prime numbers streak
    n = 0
    while isPrime(quadratic(a, b, n))
        n += 1;
    end

    return n
end

function checkQuadratic(absoluteAMax, absoluteBMax) # return the maximum length of a prime number streak 
    max = [1, 1, 0]
    for a in -absoluteAMax:absoluteAMax
        for b in -absoluteBMax:absoluteBMax
            res = getPrimeConsecutiveLength(a, b)
            if (res > max[3]) 
                max = [a, b, res]
            end

        end
    end

    return max
end

getFirstPrimesNumbers(1000)
res = checkQuadratic(1000, 1000)
println(res, res[1] * res[2])