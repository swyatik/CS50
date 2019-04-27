import sys

def main():
    if int(len(sys.argv)) != 2:
        sys.exit("Usage: python bleep.py dictionary")
    dictionary = open(sys.argv[1], "r")
    dic = dictionary.read().split()
    if not dic:
        sys.exit("Your dictionary is empty")
    print("What message would you like to censor?")
    text = input().split()
    for i in range (len(text)):
        text_low = text[i].lower()
        if text_low in dic:
            for j in range (len(text[i])):
                print("*", end="")
            print(end=" ")
        else:
            print(text[i], end=" ")
    print()
    dictionary.close()


if __name__ == "__main__":
    main()
