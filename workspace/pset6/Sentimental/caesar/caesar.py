from cs50 import get_string
import sys

def main():
    #print("Number of arguments:", len(sys.argv), "arguments.")
    #print("Argument List:", str(sys.argv))

    if(len(sys.argv) != 2):
        print("Error: Expected only ONE KEY parameter")

    key = int(str(sys.argv[1]))
    string = get_string("plaintext: ")
    msg = list(string)
    newMsg = modifymsg(msg, key)
    print("ciphertext: ", end = "")
    print(''.join(newMsg))



def modifymsg(msg, key):
    i = 0
    ciphertext = []
    val = 65
    while(i < len(msg)):
        if((msg[i] >= 'A' and msg[i] <= 'Z') or (msg[i] >= 'a' and msg[i] <= 'z')):
            if(isLower(msg[i]) == True):
                val = 97
            else:
                val = 65
            newChar = (ord(msg[i]) - val + key) % 26 + val
            ciphertext.append(chr(newChar))
        i = i + 1
    return ciphertext

def isLower(c):
    if(c >= 'a'and c <= 'z'):
        return True
    else:
        return False


if __name__ == "__main__":
    main()
