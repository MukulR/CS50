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
db = SQL("sqlite:///finance.db")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    stocks = db.execute("SELECT Symbol, Company, SUM(NumberOfShares) AS Shares, UnitPrice, SUM(TotalPrice) AS TotalPrice FROM "
                            "portfolio WHERE UserID = :userid GROUP BY Symbol", userid=session.get("user_id"))

    symbol = db.execute("SELECT Symbol FROM portfolio WHERE UserID = :userid", userid=session.get("user_id"))

    cash = db.execute("SELECT cash FROM users WHERE id = :userid", userid=session.get("user_id"))

    balance = cash[0]["cash"]
    grandTotal = 0
    for stock in stocks:
        grandTotal = grandTotal + stock["TotalPrice"]

    grandTotal = grandTotal + balance

    return render_template("index.html", stockList=stocks, cash=balance, totalAssets=grandTotal, currentUser=session.get("user_id"))

@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    if request.method == "POST":
        numShares = 0
        try:
            numShares = float(request.form.get("shares"))
        except ValueError:
            return apology("Enter a numerical value!", 400)
        if numShares % 1 != 0:
            return apology("Fractional Shares not allowed!", 400)
        if numShares <= 0:
            return apology("Enter a number greater than 0!", 400)
        if not request.form.get("symbol"):
            return apology("Enter a symbol!", 400)
        if not request.form.get("shares"):
            return apology("Enter a number of shares!", 400)

        company = lookup(request.form.get("symbol"))
        if not company:
            return apology("Invalid ticker symbol", 400)
        price = float(company["price"])
        total = float(price * numShares)
        symbl = company["symbol"]
        userRows = db.execute("SELECT cash FROM users WHERE id = :userid", userid=session.get("user_id"))
        remainingCash = float(userRows[0]["cash"])
        if total > remainingCash:
            return apology("You cannot afford the stock(s)!", 400)
        else:
            currentUser = session.get("user_id")
            purchased = db.execute("INSERT INTO portfolio (UserID, Symbol, Company, NumberOfShares, UnitPrice, TotalPrice) VALUES(:userid, :symbol, :name, :shares, :unitPrice, :totalPrice)", userid=currentUser, symbol=symbl, name=company['name'], shares=numShares, unitPrice=price, totalPrice=total)


            if not purchased:
                return apology("Unable to purchase", 400)
            else:
                remainingCash = remainingCash - total
                db.execute("UPDATE users set cash=:balance WHERE id=:userid", balance=remainingCash, userid=currentUser)
                '''Update history'''
                dateNow = datetime.datetime.now()
                historized = db.execute("INSERT INTO history (Symbol, Shares, Price, Date, UserID) VALUES(:symbol, :shares, :price, :date, :userid)", symbol = symbl, shares = numShares, price = total, date = dateNow, userid = session.get("user_id"))
                '''Update history end'''
                return redirect("/")


    else:
        return render_template("buy.html")

@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    transactions = db.execute("SELECT Symbol, Shares, Price, Date FROM history WHERE UserID = :userid", userid=session.get("user_id"))
    return render_template("history.html", transactionList = transactions, currentUser=session.get("user_id"))


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


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        if not lookup(request.form.get("symbol")):
            return apology("Please enter a valid symbol", 400)
        else:
            quote = lookup(request.form.get("symbol"))
            return render_template("quoted.html", symbol=quote["symbol"], price=quote["price"], name=quote["name"])
    else:
        return render_template("quote.html")

@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
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


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        sharesToSell = int(request.form.get("shares"))
        if sharesToSell < 0:
            return apology("Shares to sell cannot be negative", 400)

        sharesRows = db.execute("SELECT * FROM portfolio WHERE UserID = :userid AND Symbol = :enteredSymbol",
                                    userid=session.get("user_id"), enteredSymbol = symbol)

        numSharesOwned = 0
        for row in sharesRows:
            numSharesOwned += row["NumberOfShares"]

        if numSharesOwned < sharesToSell:
            return apology("You don't own that many shares!", 400)

        remainingSharesToSell = sharesToSell
        for row in sharesRows:
            numShares = row["NumberOfShares"]
            if remainingSharesToSell >= numShares:
                '''delete row'''
                delete = db.execute("DELETE FROM portfolio WHERE id = :rowid", rowid = row["id"])
                remainingSharesToSell -= numShares
            else:
                '''update row'''
                updatedShares = numShares - remainingSharesToSell
                update = db.execute("UPDATE portfolio SET NumberOfShares = :numshares, TotalPrice = :tp WHERE id = :rowid",
                                        numshares = updatedShares, tp = updatedShares * row["UnitPrice"], rowid = row["id"])
                remainingSharesToSell = 0

            if remainingSharesToSell == 0:
                break;

        quote = lookup(symbol)
        cashToReturn = quote["price"] * sharesToSell
        userRows = db.execute("SELECT cash FROM users WHERE id = :userid", userid = session.get("user_id"))
        usersCurrentCash = userRows[0]["cash"]

        updatedBalance = usersCurrentCash + cashToReturn
        db.execute("UPDATE users SET cash = :cash WHERE id = :userid", cash = updatedBalance, userid = session.get("user_id"))
        '''Update history'''
        dateNow = datetime.datetime.now()
        db.execute("INSERT INTO history (Symbol, Shares, Price, Date, UserID) VALUES(:symbl, :shares, :price, :date, :userid)", symbl = symbol, shares = -1 * sharesToSell, price = -1 * cashToReturn, date = dateNow, userid = session.get("user_id"))
        '''Update history end'''
        return redirect("/")

    else:
        symbolRows = db.execute("SELECT Symbol FROM portfolio WHERE UserID = :userid GROUP BY Symbol", userid=session.get("user_id"))
        symbls = []
        for row in symbolRows:
            symbls.append(row["Symbol"])

        return render_template("sell.html", symbols=symbls)


@app.route("/password", methods=["GET", "POST"])
@login_required
def password():
    if request.method == "POST":
        temp1 = request.form.get("newpassword1")
        temp2 = request.form.get("newpassword2")

        newPwd1 = str(temp1)
        newPwd2 = str(temp2)
        actualPwd = db.execute("SELECT hash FROM users WHERE id = :userid", userid=session.get("user_id"))

        if newPwd1 != newPwd2:
            return apology("Make sure the new passwords match!")
        else:
            updatePwd = db.execute("UPDATE users SET hash = :pwd", pwd = generate_password_hash(newPwd1))

        if not updatePwd:
            return apology("Something went wrong 1")

        return redirect("/")

    else:
        return render_template("password.html")

def errorhandler(e):
    """Handle error"""
    return apology(e.name, e.code)

# listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
