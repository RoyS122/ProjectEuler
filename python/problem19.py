days: list[str] = ["monday", "tuesday", "wednesday", "thursday", "friday", "saturday", "sunday"]

def get_number_days_at_first(day: int, startYear: int) -> int:
    nbr: int = 0
    days: int = 0
    month: int = 0
    year: int = startYear

    for i in range(100 * 12):
        
        if month % 12 == 2:
           days += 28 + 1 if (year % 4 == 0 or year % 400 == 0) else 0 
        else:
            if month % 12 == 0:
                year += 1
            days += month % 2 + 30
        
        if days % 7 == day: 
            nbr += 1
        month += 1
    return nbr 


print(get_number_days_at_first(6, 1901))