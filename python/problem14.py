def GetLongestCollatzSeq( maxStart: int) -> list: 
    res = [0, 0]
    for i in range(1, maxStart, 1):
        if i == 0:
            continue
        check = GetCollatzSeqLen(i)
        if check > res[0]:
            res = [check, i]

    return res


def GetCollatzSeqLen(val: int) -> int:
    val = val
    x = 0
    while val != 1:
        if val % 2 == 0:
            val = val / 2
        else: 
            val = 3 * val + 1
        x += 1
    return x
    


print(GetLongestCollatzSeq(1000000))