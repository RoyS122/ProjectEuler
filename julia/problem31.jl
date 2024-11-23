coins = [200, 100, 50, 20, 10, 5, 2, 1]

function CoinsSum(total::Int, coins::Array)
    decomp = [0 for _ in 0:total]
    decomp[1] = 1;
    # We are getting the count for every step before our target
    for coin in coins
        for ammount in coin:total
            decomp[ammount + 1] += decomp[ammount - coin + 1]
        end
    end
    return decomp[total + 1]
end


function CoinsSumRecursive(total::Int, step::Int) # the same program but recursively
    if step >= length(coins) return 1 end
    res = 0
    while total >= 0 
        res += CoinsSumRecursive(total, step + 1)
        total -= coins[step] 
    end
    return res
end
println(CoinsSum(200, coins)," ", CoinsSumRecursive(200, 1))
