function digitFractionalPart(nbr::Int)::Int
    res = 1
    current_step = 0
    id = 1
    for i in 1:10^nbr
        current = reverse(digits(i))
        l_current = length(current)
        for j in 1:l_current
            if (id - 1 + j) % (10^current_step) == 0 
                println(current)
                res *= current[j]
                current_step += 1
            end
        end 
        id += l_current
    end
    return res
end

println(digitFractionalPart(6))