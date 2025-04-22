function getPermutations(list) # List all the permutations
   
    len_list = length(list)
    
    if len_list == 1
        return [list]
    else
        permutations = []
        for i in 1:len_list
            wo_i = copy(list)
            deleteat!(wo_i, i)
            wo_i_perms = getPermutations(wo_i)
            for perm in wo_i_perms
                push!(perm, list[i]);
                push!(permutations, perm)
            end
        end
        return permutations
    end
end

function permToNumber(perm) # convert a permutation in numbers(Integers)
    reverse!(perm)
    l_perm = length(perm)
    res = 0
    for i in 1:l_perm
        res += perm[i] * (10 ^ (i - 1))
    end
    return res
end

function permListToNumberList(permutations) # Apply the convertion on all the list and return the new list
    list = []
    for perm in permutations
        push!(list, permToNumber(perm))
    end
    return list
end


print(sort(permListToNumberList(getPermutations([0,1,2,3,4,5,6,7,8,9])))[1000000])