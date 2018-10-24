import os
import datetime

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///bookshelf.db")


@app.route("/")
@login_required
def index():
    return render_template("index.html", currentUser=session.get("username"))


@app.route("/addbook", methods=["GET", "POST"])
@login_required
def addbook():
    if request.method == "POST":
        try:
            pages = int(request.form.get("pages"))
        except ValueError:
            return apology("Enter a numerical value!", 400)
        try:
            title = str(request.form.get("title"))
        except ValueError:
            return apology("Enter text for the title!", 400)
        try:
            author = str(request.form.get("author"))
        except ValueError:
            return apology("Enter text for the author!", 400)
        if not title:
            return apology("Enter a book title!", 400)
        if not author:
            return apology("Enter an author's name!", 400)
        if not pages:
            return apology("Enter the amount of pages in the book!", 400)



        dateNow = datetime.datetime.now()
        pushToDb = db.execute("INSERT INTO shelves (title, author, pages, userID, date) VALUES(:booktitle, :bookauthor, :bookpages, :user, :date)", booktitle = title, bookauthor = author, bookpages = pages, user = session.get("user_id"), date = dateNow)
        if not pushToDb:
            return apology("Something went wrong")
        return redirect("/history")
    else:
        return render_template("addbook.html")

@app.route("/history")
@login_required
def history():
    data = db.execute("SELECT * FROM shelves WHERE userID = :userid", userid = session.get("user_id"))
    return render_template("history.html", books = data)

@app.route("/search", methods=["GET", "POST"])
@login_required
def search():
    if request.method == "POST":
        keyword = request.form.get("keyword")
        if not keyword:
            return apology("Enter a keyword!", 400)

        keyword = '%' + keyword + '%'
        bookdata = db.execute("SELECT * FROM shelves WHERE userID = :userid AND (title LIKE :keywrd OR author LIKE :keywrd)", userid = session.get("user_id"), keywrd = keyword)
        return render_template("searched.html", books = bookdata, currentUser = session.get("user_id"))
    else:
        return render_template("search.html")


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]
        session['username'] = request.form['username']

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")



@app.route("/register", methods=["GET", "POST"])
def register():
    if request.method == "POST":

        if not request.form.get("username"):
            return apology("Please enter a username", 400)
        elif not request.form.get("password"):
            return apology("Please enter a password", 400)
        elif not request.form.get("confirmation"):
            return apology("Please enter your password again", 400)

        if request.form.get("password") != request.form.get("confirmation"):
            return apology("Passwords do not match!", 400)

        userID = db.execute("INSERT INTO users (username, hash) VALUES(:username, :pwdhash)",
                    username=request.form.get("username"), pwdhash=generate_password_hash(request.form.get("password")))
        if not userID:
            return apology("User already exists! Try logging in?", 400)

        session["user_id"] = userID
        return redirect("/")
    else:
        return render_template("register.html")

@app.route("/removebook", methods=["GET", "POST"])
@login_required
def removebook():
    """Sell shares of stock"""
    if request.method == "POST":
        title = request.form.get("title")
        author = request.form.get("author")
        if not title:
            return apology("Enter a title!", 400)
        if not author:
            return apology("Enter an author!", 400)
        try:
            title = str(request.form.get("title"))
        except ValueError:
            return apology("Enter text for the title!", 400)
        try:
            author = str(request.form.get("author"))
        except ValueError:
            return apology("Enter text for the author!", 400)

        found = db.execute("DELETE FROM shelves WHERE UserID = :userid AND author = :bookauthor AND title = :booktitle", userid = session.get("user_id"), bookauthor = author, booktitle = title)

        if not found:
            return apology("Record not found!", 400)
        return redirect("/")
    else:
        return render_template("removebook.html")


def errorhandler(e):
    """Handle error"""
    return apology(e.name, e.code)


# listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
