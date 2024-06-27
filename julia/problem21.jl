function getDivisors(n)
    array = Int[]
    for i in 1:n-1
        if n % i == 0
            push!(array, i)
        end
    end
    return array
end

# Fonction pour obtenir les nombres amicaux jusqu'à n
function getAmicableNumbers(n)
    sums = Dict{Int, Int}()
    amicables = Int[]
    
    # Calcule la somme des diviseurs propres pour chaque nombre jusqu'à n
    for i in 1:n
        localSum = sum(getDivisors(i))
        sums[i] = localSum
    end
    
    
    for (key, value) in sums
        if value <= n && value != key && get(sums, value, 0) == key
            if !(key in amicables)
                push!(amicables, key)
            end
            if !(value in amicables)
                push!(amicables, value)
            end
        end
    end
    
    return amicables
end


amicable_numbers = getAmicableNumbers(10000)

println(sum(amicable_numbers))
