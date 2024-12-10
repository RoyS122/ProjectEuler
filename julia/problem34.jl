function sumDigitFactorial(nbr::Int)::BigInt # Make the sum of the digit as factorial of a number
    s = BigInt(0);
    while nbr > 0
        s += factorial(nbr % 10)
        nbr ÷= 10;
    end
    return s
end 

function DigitFactorialList()::Vector{BigInt} # Get the list of factorial sum
    list = Vector{BigInt}()
    for x in 10:7*factorial(9)
        if x == sumDigitFactorial(x)
            push!(list, x)
        end
    end
    list
end

println(sum(DigitFactorialList()));