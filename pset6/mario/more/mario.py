from cs50 import get_int


height = 0

while True:
    height = get_int("Height: ")
    if height >= 1 and height <= 8:
        break
    
for i in range(1, height+1, 1):
    for j in range(height-i):
        print(" ", end='')
    for k in range(i):
        print("#", end='')
    for x in range(2):
        print(" ", end='')
    for z in range(i):
        print("#", end='')
    print()