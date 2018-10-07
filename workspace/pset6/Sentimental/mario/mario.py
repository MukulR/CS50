from cs50 import get_int

def main():
    height = get_int("Height: ")
    while(height < 0 or height > 23):
        height = get_int("Height: ")


    count = 1
    count2 = 1
    for j in range(height):
        for i in range(height - count):
            print(" ", end = "")

        count += 1
        for k in range(count - 1):
            print("#", end = "")

        print(" ", end = "")
        print(" ", end = "")
        for l in range(count2):
            print("#", end = "")

        count2 += 1
        #new line
        print(" ")

if __name__ == "__main__":
    main()