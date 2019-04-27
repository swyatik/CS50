# перевірка вводу вихідних даних
while True:
    n = input("Height: ")
    if n.isdigit():
        if int(n) > 0:
            if int(n) < 9:
                break
# друк пірамід
for i in range(int(n)):
    space = int(n) - i - 1
    for j in range(space):
        print(" ", end="")
    for c in range(int(n) - space):
        print("#", end="")
    print("  ", end="")
    for l in range(int(n) - space):
        print("#", end="")
    print()
