function getSolutionsForPerimeter(p::Int)::Vector{Tuple{Int, Int, Int}}
    array = Vector{Tuple{Int, Int, Int}}()
    for a in 1:p
        for b in 1:p
            for c in 1:p
                peri = a + b + c
                if peri > p
                    break;
                end 
                if peri == p
                    if a * a + b * b == c * c 
                        already = false
                        for t in array 
                            if (t[1] == a || t[2] == a) && (t[1] == b || t[2] == b)
                               already = true
                               break;
                            end
                        end 
                        if !already 
                            push!(array, (a, b, c))
                        end         
                    end
                end
            end
        end
    end
    return array
end

function getMaximumLengthSolution(MaxP::Int)::Int
    max = 0
    maxid = 0
    for i in 1:MaxP
        l = length(getSolutionsForPerimeter(i))
        if l > max
            max = l
            maxid = i
        end
    end
    return maxid
end
println(getMaximumLengthSolution(1000))