function getSumOfSpiralDiagonal(size) 
    if size > 1
        totDiag = 0;
        for i in 0:3 # Add to total the n - 1 (size of the side of spiral)
            totDiag +=  (size * size) - (size - 1) * i # Multiply the side - 1 by number of side number of side to get the corner
        end
        return getSumOfSpiralDiagonal(size - 2) + totDiag # recursively add the total to the previous total
    end
    return 1 # if we get the center we return the 1
end

println(getSumOfSpiralDiagonal(5))