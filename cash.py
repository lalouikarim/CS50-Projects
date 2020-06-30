from cs50 import get_float
change = get_float("How much change are you owed?\n")
while change < 0:
    change = get_float("How much change are you owed?\n")
coins_number = 0
while change > 0.0:
    coins_number += 1
    if change >= 0.25:
        change -= 0.25
    elif change >= 0.1:
        change -= 0.1
    elif change >= 0.05:
        change -= 0.05
    else:
        change -= 0.01
    change=round(change,2)
print(coins_number)
