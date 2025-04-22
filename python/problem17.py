from math import floor
intletters :dict = {
    1: "one",
    2: "two",
    3: "three",
    4: "four",
    5: "five",
    6: "six",
    7: "seven",
    8: "eight",
    9: "nine",
    10: "ten",
    11: "eleven",
    12: "twelve",
    13: "thirteen",
    14: "fourteen",
    15: "fifteen",
    16: "sixteen",
    17: "seventeen",
    18: "eighteen",
    19: "nineteen",
    20: "twenty",
    30: "thirty",
    40: "forty",
    50: "fifty",
    60: "sixty",
    70: "seventy",
    80: "eighty",
    90: "ninety" 
}

def translate_int_to_word(nb :int, dict_intletters :dict) -> str: 
    res :str = ""
   
    if (nb // 1000 >= 1): 
        res += dict_intletters[nb // 1000] + "thousand"
        nb -= 1000 * (nb // 1000)
    
    if (nb // 100 >= 1):    
        if 100 <= nb <= 900 and nb % 100 == 0:
            res += dict_intletters[nb // 100] + "hundred"
        else:
            res += intletters[nb // 100] + "hundredand"
        nb -= 100 * (nb // 100)
        
    if(nb > 19):
        res += dict_intletters[nb // 10 * 10]
        nb -= 10 * (nb // 10)
    if(nb != 0):
        res += dict_intletters[nb]
    return res


def get_number_of_letters(nbr: int) -> int:
    res = ""
    for i in range(1, nbr + 1) :
        res += translate_int_to_word(i, intletters)
    return len(res)

print(get_number_of_letters(1000))