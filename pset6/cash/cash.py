from cs50 import get_float


while True:
    dollars = get_float("Change owed: ")
    if dollars > 0.0:
        break
cents = (dollars * 100)
nCoins = 0

while cents != 0:
    while cents >= 25:
        cents = cents - 25
        nCoins += 1
    while cents >= 10:
        cents = cents - 10
        nCoins += 1
    while cents >= 5:
        cents = cents - 5
        nCoins += 1
    while cents >= 1:
        cents = cents - 1
        nCoins += 1

print(nCoins)