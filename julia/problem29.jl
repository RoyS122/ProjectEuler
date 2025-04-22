function PowerCombinations(rangeA::Array, rangeB::Array) 
    list = Set{BigInt}() # Set is a list type without double
    for a in rangeA[1]:rangeA[2]
        for b in rangeB[1]:rangeB[2]
            println("Calculating $a^$b")
            push!(list, BigInt(a)^b) # Forced to use BigInt because UInt128 not reach 100^100
        end
    end
    return list
end

println(length(PowerCombinations([2, 100], [2, 100])))
