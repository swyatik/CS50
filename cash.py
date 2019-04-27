while True:
    n = input("Change owed: ")
    # http://qaru.site/questions/1283/how-do-i-check-if-a-string-is-a-number-float-in-python
    if n.replace(".", "", 1).isdigit():
        break
n = int(float(n) * 100)
quarter = 0;
if n >= 25:
    quarter = n // 25
dime = 0
if n >= 10:
    dime = (n - quarter * 25) // 10
nickel = 0
if n >= 5:
    nickel = (n - quarter * 25 - dime * 10) // 5
peny = n - quarter * 25 - dime * 10 - nickel * 5
print(quarter + dime + nickel + peny)
