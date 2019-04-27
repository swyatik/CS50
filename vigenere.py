import sys
if int(len(sys.argv)) != 2 or sys.argv[1].isalpha() == False:
    sys.exit("Usage: python vigenere.py k")
key = sys.argv[1].upper()
k = len(key)
index_k = 0
text = input("plaintext: ")
print("ciphertext: ", end="")
for i in range (len(text)):
    if text[i].isupper():
        print(chr(65 + (ord(text[i]) - 65 + ord(key[index_k % k]) - 65) % 26), end="")
        index_k += 1
    elif text[i].islower():
        print(chr(97 + (ord(text[i]) - 97 + ord(key[index_k % k]) - 65) % 26), end="")
        index_k += 1
    else:
        print(text[i], end="")
print()
