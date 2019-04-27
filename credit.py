while True:
    n = input("Number: ")
    if n.isdigit():
        break
strlen = len(n)

# алгоритм Luhn (Validation of a credit card number)
product_sum = 0
if strlen % 2 == 0:
    amount = int(strlen / 2)
else:
    amount = strlen // 2
x = strlen
for i in range(amount):
    if 2 * int(n[x - 2]) > 9:
        product_sum += (2 * int(n[x - 2])) % 10 + 1
        x -= 2
    else:
        product_sum += 2 * int(n[x - 2])
        x -= 2
x = strlen + 1
sum_2 = 0
for i in range(strlen - amount):
    sum_2 += int(n[x - 2])
    x -= 2
if (product_sum + sum_2) % 10 != 0:
    print("INVALID")

# перевірка
elif strlen == 13 or strlen == 15 or strlen == 16:
    if strlen == 13 or strlen == 16:
        if int(n[0]) == 4:
            print("VISA")
        elif int(n[0:2]) == 51 or int(n[0:2]) == 52 or int(n[0:2]) == 53 or int(n[0:2]) == 54 or int(n[0:2]) == 55:
            print("MASTERCARD")
        else:
            print("INVALID")
    elif strlen == 15:
        if int(n[0:2]) == 34 or int(n[0:2]) == 37:
            print("AMEX")
        else:
            print("INVALID")
    else:
        print("INVALID")
else:
    print("INVALID")
