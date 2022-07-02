import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from datetime import datetime
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
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

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    # Get all transactions made by the user just to later check if he made any
    transactions = db.execute("SELECT * FROM transactions WHERE username_id = ?", session["user_id"])

    # Get all info about the user just to later check how much cash he has (could be changed to select only the cash in the first place but who cares..)
    user = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])

    # Get the info about all shares owned by the user
    shares = db.execute(
        "SELECT stock_symbol, SUM(shares) AS sum_shares, stocks_name FROM transactions WHERE username_id = ? GROUP BY stock_symbol HAVING SUM(shares) > 0", session["user_id"])

    # Creating a variable that later sums the total value of shares owned
    total = 0

    # Iterate throught all shares, check each share's price, calculate value of share's owned, add each share value to the total variable.
    for share in shares:
        stock = lookup(share['stock_symbol'])
        stock_price = stock['price']
        share['total'] = stock_price * share['sum_shares']
        share['price'] = stock_price
        total = total + share['total']

    return render_template("index.html", transactions=transactions, user=user, shares=shares, total=total)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":

        # Get the symbol from the user
        symbol = request.form.get("symbol").upper()
        if not symbol:
            return apology("Must provide symbol")
        if lookup(symbol) == None:
            return apology("Symbol doesn't exist")
        shares = request.form.get("shares")
        try:
            shares = int(shares)
        except ValueError:
            return apology("Shares must be an integer")
        shares = int(shares)
        if not shares:
            return apology("Must provide amount of shares")
        if not isinstance(shares, int):
            return apology("Shares must be a positive integer")
        if shares <= 0:
            return apology("Shares must be a positive integer")

        # Get stock's symbol and name
        stock = lookup(symbol)
        stocks_name = stock["name"]

        # Variable for Stock's price
        current_price = stock["price"]

        # Variable of user's balance
        current_balance = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])

        # Variable of user's name
        username = db.execute("SELECT username FROM users WHERE id = ?", session["user_id"])

        # Set transaction type to bought
        transaction_type = "Purchase"

        # Calculate the value of shares bought * it's price
        amount = int(shares) * float(stock["price"])

        # Check's if the user can afford it
        if (current_balance[0]["cash"] - amount) < 0:
            return apology("Sorry, You can't afford it.")

        # Add the transaction to database
        db.execute("INSERT INTO transactions (username_id, username, transaction_type, stock_symbol, amount, shares, stocks_name, total_bought) VALUES (?, ?, ?, ?, ?, ?, ?, ?)",
                   session["user_id"], username[0]["username"], transaction_type, symbol, stock["price"], shares, stocks_name, amount)

        # Calculate the balance of the user after the transaction
        new_balance = current_balance[0]["cash"] - amount
        db.execute("UPDATE users SET cash = ? WHERE id = ?", new_balance, session["user_id"])

        # Redirect the user to frontpage
        flash("Bought!")
        return redirect("/")

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    transactions = db.execute("SELECT * FROM transactions WHERE username_id = ?", session["user_id"])

    return render_template("history.html", transactions=transactions)


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
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

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
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("Must provide symbol")
        Symbol = lookup(symbol)
        if not Symbol:
            return apology("Symbol doesn't exist")
        return render_template("quoted.html", Symbol=lookup(symbol))
    return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        username = request.form.get("username")
        # Check if the username already exists
        check_database = db.execute("SELECT * FROM users WHERE username = ?", username)
        if len(check_database) != 0:
            return apology("User already exists")
        # Check if the Username field wasn't left empty
        if not username:
            return apology("Username cannot be empty")

        password = request.form.get("password")
        confirmation = request.form.get("confirmation")
        if password != confirmation:
            return apology("password doesnt match")
        if not password:
            return apology("password cannot be empty")
        passwordhash = generate_password_hash(password, method='pbkdf2:sha256')
        db.execute("INSERT INTO users (username, hash) VALUES(?, ?)", username, passwordhash)
        return redirect("/")

    return render_template("register.html")


@app.route("/account", methods=["GET", "POST"])
@login_required
def account():
    """ Let the user change his account settings """

    if request.method == "POST":
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")
        if password != confirmation:
            return apology("password doesnt match")
        if not password:
            return apology("password cannot be empty")
        passwordhash = generate_password_hash(password, method='pbkdf2:sha256')
        db.execute("UPDATE users SET hash = ? WHERE id = ?", passwordhash, session["user_id"])
        flash("Password changed")
        return redirect("/")

    return render_template("account.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    shares_get = db.execute(
        "SELECT stock_symbol, SUM(shares) AS sum_shares FROM transactions WHERE username_id = ? GROUP BY stock_symbol", session["user_id"])
    print(shares_get)

    if request.method == "POST":

        symbol = request.form.get("symbol")
        print(symbol)
        if not symbol:
            return apology("Must choose share")
        print(search(symbol, shares_get))
        if search(symbol, shares_get) == []:
            return apology("You think your'e clever, huh?")
        if lookup(symbol) == None:
            return apology("Symbol doesn't exist")
        shares = request.form.get("shares")
        if not shares:
            return apology("Must provide amount of shares")
        if int(shares) <= 0:
            return apology("Shares must be a positive integer", 403)

        stock = lookup(symbol)
        stocks_name = stock["name"]
        current_price = stock["price"]
        current_balance = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
        username = db.execute("SELECT username FROM users WHERE id = ?", session["user_id"])
        transaction_type = "Sell"
        amount = int(shares) * float(stock["price"])

        shares_purchased = db.execute(
            "SELECT stock_symbol, SUM(shares) AS sum_shares, stocks_name FROM transactions WHERE username_id = ? AND stock_symbol = ?", session["user_id"], stock["symbol"])

        total_owned = int(shares_purchased[0]["sum_shares"])

        if int(shares) > total_owned:
            return apology("You don't have enough shares")

        shares = int(shares) - (int(shares) * 2)
        db.execute("INSERT INTO transactions (username_id, username, transaction_type, stock_symbol, amount, shares, stocks_name, total_bought) VALUES (?, ?, ?, ?, ?, ?, ?, ?)",
                   session["user_id"], username[0]["username"], transaction_type, symbol, stock["price"], shares, stocks_name, amount)

        new_balance = current_balance[0]["cash"] + amount
        db.execute("UPDATE users SET cash = ? WHERE id = ?", new_balance, session["user_id"])
        flash("Sold!")
        return redirect("/")

    return render_template("sell.html", shares=shares_get)


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


def search(name, people):
    return [element for element in people if element['stock_symbol'] == name]


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
