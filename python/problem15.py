from typing import List

def PascalTriangle(rows: int) -> List[int]: 
    res: List[List[int]] = [[1],[1,1]]
    while(len(res)-1 != rows):
        newrow: List[int] = [1]
        lastrow: int = len(res) - 1
        for i in range(1, len(res[lastrow])):
            newrow.append(res[lastrow][i - 1] + res[lastrow][i])
        newrow.append(1)
        res.append(newrow)
    return newrow

res: List[int] = PascalTriangle(4 / 2 * 20) # Le calcul ici fait reference, au triangle de pascal, en effet pour atteindre le resultat escompté dans la consigne (reponse 6 pour 2x2 je divise donc le nombre de lignes necessaires par le nombre de case du tableau)

print(res[int(round(len(res) / 2))])