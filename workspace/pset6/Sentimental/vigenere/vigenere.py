from cs50 import get_string
import sys

def main():
    if(len(sys.argv) != 2):
        print("Error: Expected only ONE KEY STRING parameter")

    keyword = sys.argv[1]
    i = 0
    while(i < len(keyword)):
        if(((keyword[i] < 'a' and keyword[i] > 'z') or (keyword[i] < 'A' and keyword[i] > 'Z'))):
            print("Error: Expected only alphabets in keyword.")
        i = i + 1

    string = get_string("Plaintext: ")
    msg = list(string)
    newMsg = modifymsg(msg, keyword)
    print("Ciphertext: ", end = "")
    print(''.join(newMsg))



def modifymsg(msg, keyword):
    j = 0
    i = 0
    ciphertext = []
    while(i < len(msg)):
        if((msg[i] >= 'A' and msg[i] <= 'Z') or (msg[i] >= 'a' and msg[i] <= 'z')):
            if(isLower(keyword[j])):
                key = ord(keyword[j]) - 97
            else:
                key = ord(keyword[j]) - 65

            if(isLower(msg[i]) == True):
                val = 97
            else:
                val = 65
            newChar = (ord(msg[i]) - val + key) % 26 + val
            ciphertext.append(chr(newChar))
            j = j + 1
            if(j > len(keyword) - 1):
                j = 0

        i = i + 1

    return ciphertext


def isLower(c):
    if(c >= 'a'and c <= 'z'):
        return True
    else:
        return False



if __name__ == "__main__":
    main()
