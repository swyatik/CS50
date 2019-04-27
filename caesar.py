import sys
if int(len(sys.argv)) != 2 or sys.argv[1].isdigit() == False:
    sys.exit("Usage: python caesar.py k")
key = int(sys.argv[1])
text = input("plaintext: ")
print("ciphertext: ", end="")
for i in range (len(text)):
    if text[i].isupper():
        print(chr(65 + (ord(text[i]) - 65 + key) % 26), end="")
    elif text[i].islower():
        print(chr(97 + (ord(text[i]) - 97 + key) % 26), end="")
    else:
        print(text[i], end="")
print()
