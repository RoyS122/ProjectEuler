function is_terminating(d::Int)
    # Cut d by divide by 5 and 2 
    while d % 2 == 0 || d % 5 == 0
        
        if d % 2 == 0
            d = d/2
            continue
        end
        d = d / 5
    end
    # If d == 1, the decimal number is finished
    return d == 1
end

function recurring_cycle_length(d::Int) # Check the length of recurring cycle
    if is_terminating(d)
        return 0
    end

    mod = 10 % d
    visited_mods = Dict{Int, Int}()
    position = 0
    
    while !haskey(visited_mods, mod)  # Check if the modulo has already b saved, because if modulo already seen it's the end of the cycle
        visited_mods[mod] = position    # Save the modulo and the position 
        mod = (mod * 10) % d # Go to the next modulo
        position += 1

        # If mod == 0 no recurring cycle
        if mod == 0
            return 0
        end
    end

    # The length of the cycle is the distance between the position saved and the actual position (distance between two same modulo) 
    return position - visited_mods[mod]
end

function longest_recurring_cycle(limit::Int)
    max_length = 0
    max_d = 0
    for d in 2:limit-1
        cycle_length = recurring_cycle_length(d)
        if cycle_length > max_length
            max_length = cycle_length
            max_d = d
        end
    end
    return max_d, max_length
end

d, cycle_length = longest_recurring_cycle(1000)
println("La valeur de d < 1000 avec le plus long cycle est $d avec une longueur de cycle de $cycle_length.")
