
# Fraction type definition

struct Fraction
    n::Int
    d::Int
end

Base.:*(a::Fraction, b::Fraction) = Fraction(a.n * b.n, a.d * b.d)
Base.:(==)(a::Fraction, b::Fraction) = (a.n * b.d == a.d * b.n)


function hasCommonDigit(f::Fraction)::Bool # check if there is a common digit on a fraction
    return length(intersect(digits(f.n), digits(f.d))) > 0
end



function deleteCommonDigit(f::Fraction)::Fraction # delete the common digit on a fraction
    digits_a = digits(f.n)
    digits_b = digits(f.d)
    commons = intersect(digits_a, digits_b)
    filter!(d -> !(d in commons), digits_a)
    filter!(d -> !(d in commons), digits_b)
    new_fraction = Fraction(
        isempty(digits_a) ? 1 : parse(Int, join(reverse(digits_a))),
        isempty(digits_b) ? 1 : parse(Int, join(reverse(digits_b)))
    )
    return new_fraction
end

function getCuriousFractions()::Vector{Fraction} # Get the list of curious fractions like following the definition in the problem page
    res = Vector{Fraction}()
    for d in 10:99
        for n in 10:d - 1
            if hasCommonDigit(Fraction(Int(n), Int(d))) 
                f1 = Fraction(Int(n), Int(d))
                f2 = deleteCommonDigit(f1)
                if (f2 == f1 && !(n % 10 == 0 && d % 10 == 0))
                    push!(res, f2)
                end 
            end 
        end
    end
    return res
end 

function ProductOfFractions(v::Vector{Fraction})::Fraction # Do the product of a list of fraction
    fres = Fraction(1, 1)
    for f in v 
        fres *= f
    end 
    return reduce(fres)
end


function gcd(a::Int, b::Int)::Int # Return the higher common denominator
    while b != 0
        a, b = b, a % b
    end
    return a
end

function reduce(f::Fraction)::Fraction # Simplify the fraction 
    g = gcd(f.n, f.d) 
    return Fraction(f.n ÷ g, f.d ÷ g)  
end
println(ProductOfFractions(getCuriousFractions()))