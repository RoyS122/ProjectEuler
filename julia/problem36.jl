function isPalindromic(number::Vector{UInt8})::Bool # check recursively if the digits of a number is palindromic
    l_number = length(number)
    if l_number <= 1
        return true
    end
    return number[1] == number[end] && isPalindromic(number[2:end-1])
end

function getDigits(nbr::BigInt, base::Int)::Vector{UInt8} # Get the digits of a number
    listnbr = Vector{UInt8}()
    while nbr > 0
        push!(listnbr, UInt8(nbr % base))
        nbr ÷= base
    end
    return listnbr
end

function getPalindromicUntil(until::BigInt)::Vector{BigInt} # get the list of palindromic number in the two bases of the 
    list = Vector{BigInt}()
    for i in 1:until
        if isPalindromic(getDigits(i, 10)) && isPalindromic(getDigits(i,2))
            push!(list ,i)
        end
    end
    return list
end 

println(sum(getPalindromicUntil(BigInt(1000000))))