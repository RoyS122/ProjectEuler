class Pyramid():
    def __init__(self, val: int, right = None, left = None):
        self.value: int = val
        self.right: Pyramid = right
        self.left: Pyramid  = left  

    def GetMaximumPathSum(self) -> int: #By reccursion
        val1: int = self.value
        val2: int = self.value
        if(self.left != None):
            val1 += self.left.GetMaximumPathSum()
        
        if(self.right != None):
            val2 += self.right.GetMaximumPathSum()
           
        return max(val1, val2)


def string_to_values_list(input_string):
    # Diviser la chaîne par les nouvelles lignes pour obtenir des lignes séparées
    lines: list[str] = input_string.strip().split('\n')
    
    # Diviser chaque ligne par les espaces et convertir les valeurs en entiers
    values_list: list[list[int]]= [list(map(int, line.split())) for line in lines]
    
    return values_list


def build_pyramid(string: str) -> list[int]:
    pyramid: list[list[int]] = []
    for row in values:
        current_row: list[int]= [Pyramid(val) for val in row]
        pyramid.append(current_row)
        if len(pyramid) > 1:
            for i in range(len(pyramid[-2])):
                pyramid[-2][i].left = pyramid[-1][i]
                pyramid[-2][i].right = pyramid[-1][i+1]
    return pyramid[0][0]

str_values: str = """75
95 64
17 47 82
18 35 87 10
20 04 82 47 65
19 01 23 75 03 34
88 02 77 73 07 63 67
99 65 04 28 06 16 70 92
41 41 26 56 83 40 80 70 33
41 48 72 33 47 32 37 16 94 29
53 71 44 65 25 43 91 52 97 51 14
70 11 33 28 77 73 17 78 39 68 17 57
91 71 52 38 17 14 91 43 58 50 27 29 48
63 66 04 68 89 53 67 30 73 16 69 87 40 31
04 62 98 27 23 09 70 98 73 93 38 53 60 04 23"""

values: list[int]= string_to_values_list(str_values)

root: Pyramid = build_pyramid(values)
print(root.GetMaximumPathSum())  # Output the maximum path sum