from werkzeug.exceptions import default_exceptions
from werkzeug.security import check_password_hash, generate_password_hash


def main():
    print(generate_password_hash("mynameisbob"))



if __name__ == "__main__":
    main()

