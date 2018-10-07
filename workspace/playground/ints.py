from cs50 import get_int

x = get_int("Enter Int: ")
y = get_int("Enter Int: ")

print(f"{x} + {y} = {x + y}")
print(f"{x} - {y} = {x - y}")
print(f"{x} * {y} = {x * y}")
print(f"Floor divided = {x // y}")
print(f"Truly divided = {x / y}")
print(f"remainder of {x} by {y} = {x % y}")

