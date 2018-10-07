from cs50 import get_float
import math

def main():
    userinput = 0.0

    userinput = get_float("Input: ")
    while(userinput <= 0.0):
        userinput = get_int("Input: ")


    change = round(userinput * 100)
    print(f"Change = {change} cents")

    numQuarters = 0
    numDimes = 0
    numNickels = 0
    numPennies = 0
    if change / 25 > 0:
        numQuarters = math.floor(change / 25)
        change = change % 25
    if change / 10 > 0:
        numDimes = math.floor(change / 10)
        change = change % 10
    if change / 5 > 0:
        numNickels = math.floor(change / 5)
        change = change % 5

    numPennies = change

    val =  numQuarters + numDimes + numNickels + numPennies
    print(f"{val}")

if __name__ == "__main__":
    main()