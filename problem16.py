def PowDigitSum(val: int) -> int:
    val: int = 2 ** val
    res: int = 0
    for i in str(val):
        res += int(i)
    return res

print(PowDigitSum(1000))