proc GetTriangle(n: int): int = n * (n+1) div 2

proc GetSquare(n: int): int = n * n

proc GetPentagonal(n: int): int = n * (3 * n - 1) div 2

proc GetHexagonal(n: int): int = n * (n * 2 - 1)

proc GetHeptagonal(n: int): int = n * (5 * n - 3) div 2

proc GetOctogonal(n: int): int = n * (3 * n - 2)

proc Solve(): string =
    var r: string = "2"
    r



echo Solve()