from cs50 import get_int
import math

def main():
    userinput = get_int("Number: ")
    numList = []

    while(userinput > 9):
        numList.append(userinput % 10)
        userinput = math.floor(userinput / 10)

    numList.append(userinput)
    length = len(numList)
    if length != 13 and length != 15 and length != 16:
        print("INVALID")

    ccdigits = []
    j = length - 1

    for j in range(length - 1, -1, -1):
        ccdigits.append(numList[j])

    validChecksum = isValidChecksum(ccdigits, length)

    if(validChecksum == False):
        print("Invalid")
    if(length == 15 and ccdigits[0] == 3 and (ccdigits[1] == 4 or ccdigits[1 == 7])):
        print("AMEX")
    if (length == 13 and ccdigits[0] == 4):
        print("VISA")
    if (length == 16):
        if(ccdigits[0] == 4):
            print("VISA")
        if(ccdigits[0] == 5 and (ccdigits[1] == 1 or ccdigits[1] == 2 or ccdigits[1] == 3 or ccdigits[1] == 4 or ccdigits[1] == 5)):
            print("MASTERCARD")


def isValidChecksum(ccdigits, length):
    sumTotal = 0;
    digits = []

    for i in range(length - 2, -1, -2):
        product = ccdigits[i] * 2
        if(product > 9):
            digits.append(product % 10)
            digits.append(math.floor(product / 10))
        else:
            digits.append(product)

    for i in range(0, len(digits)):
        sumTotal = sumTotal + digits[i]

    val = 0

    for j in range(length - 1, -1, -2):
        val = val + ccdigits[j]

    sumTotal = sumTotal + val

    if(sumTotal % 10 == 0):
        return True
    else:
        return False

if __name__ == "__main__":
    main()
