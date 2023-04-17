import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import datetime
from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    user_id = session["user_id"]
    holdings = db.execute(
        "SELECT symbol, SUM(shares) as shares FROM transactions WHERE user_id = ? GROUP BY symbol HAVING shares > 0", user_id)

    total_value = 0
    for holding in holdings:
        stock = lookup(holding["symbol"])
        holding["name"] = stock["name"]
        holding["price"] = stock["price"]
        holding["total"] = holding["shares"] * stock["price"]
        total_value += holding["total"]

    cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"]
    grand_total = total_value + cash

    return render_template("index.html", holdings=holdings, cash=cash, grand_total=grand_total)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol").upper()
        shares = request.form.get("shares")

        if not symbol:
            return apology("must provide stock symbol", 400)

        if not shares:
            return apology("must provide number of shares", 400)

        try:
            shares = int(shares)
            if shares <= 0:
                raise ValueError
        except ValueError:
            return apology("shares must be a positive integer", 400)

        stock = lookup(symbol)
        if not stock:
            return apology("invalid stock symbol", 400)

        price = stock["price"]
        total_cost = price * shares
        user_id = session["user_id"]
        cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"]

        if total_cost > cash:
            return apology("not enough cash to complete the purchase", 400)

        # Insert transaction with date
        from datetime import datetime
        current_time = datetime.now()
        db.execute("INSERT INTO transactions (user_id, symbol, shares, price, date) VALUES (?, ?, ?, ?, ?)",
                   user_id, symbol, shares, price, current_time)

        db.execute("UPDATE users SET cash = cash - ? WHERE id = ?", total_cost, user_id)

        flash("Bought!")
        return redirect("/")
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    user_id = session["user_id"]

    transactions = db.execute("SELECT symbol, shares, price, date FROM transactions WHERE user_id = ? ORDER BY date DESC", user_id)

    for transaction in transactions:
        transaction["type"] = "Buy" if transaction["shares"] > 0 else "Sell"
        transaction["shares"] = abs(transaction["shares"])
        transaction["price"] = usd(transaction["price"])
        # transaction["date"] = transaction["date"].strftime("%Y-%m-%d %H:%M:%S")
        if transaction["date"] is not None:
            transaction["date"] = transaction["date"].strftime("%Y-%m-%d %H:%M:%S")
        else:
            transaction["date"] = datetime.now().strftime("%Y-%m-%d %H:%M:%S")

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
            return apology("You must provide a stock symbol", 400)

        quote_info = lookup(symbol)
        if not quote_info:
            return apology("Invalid stock symbol", 400)

        return render_template("quoted.html", name=quote_info["name"], symbol=quote_info["symbol"], price=usd(quote_info["price"]))

    return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        # Check if the username and passwords are valid
        if not username:
            return apology("must provide username", 400)
        elif not password:
            return apology("must provide password", 400)
        elif not confirmation:
            return apology("must provide password confirmation", 400)
        elif password != confirmation:
            return apology("passwords do not match", 400)

        # Check if the username already exists
        user_exists = db.execute("SELECT * FROM users WHERE username = ?", username)
        if user_exists:
            return apology("username already exists", 400)

        # Insert the new user into the database
        password_hash = generate_password_hash(password)
        user_id = db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, password_hash)

        # Log the user in
        session["user_id"] = user_id

        # Redirect user to home page
        return redirect("/")

    else:
        return render_template("register.html")


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    user_id = session["user_id"]

    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = int(request.form.get("shares"))

        if not symbol:
            return apology("Must select a stock symbol")

        if shares < 1:
            return apology("Shares must be a positive integer")

        current_shares = db.execute("SELECT SUM(shares) as total_shares FROM transactions WHERE user_id = ? AND symbol = ?", user_id, symbol)[0][
            "total_shares"]

        if shares > current_shares:
            return apology("You don't have enough shares")

        stock = lookup(symbol)
        sell_value = shares * stock["price"]

        # Insert transaction with date
        from datetime import datetime
        current_time = datetime.now()
        db.execute("INSERT INTO transactions (user_id, symbol, shares, price, date) VALUES (?, ?, ?, ?, ?)",
                   user_id, symbol, -shares, stock["price"], current_time)

        db.execute("UPDATE users SET cash = cash + ? WHERE id = ?", sell_value, user_id)

        flash("Sold!")
        return redirect("/")
    else:
        symbols = db.execute("SELECT DISTINCT symbol FROM transactions WHERE user_id = ? AND shares > 0", user_id)
        symbols = [s["symbol"] for s in symbols]
        return render_template("sell.html", symbols=symbols)