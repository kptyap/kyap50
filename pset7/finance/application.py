from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session, url_for
from flask_session import Session
from passlib.apps import custom_app_context as pwd_context
from passlib.hash import bcrypt
from tempfile import gettempdir
from decimal import *

from helpers import *

# configure application
app = Flask(__name__)

# ensure responses aren't cached
if app.config["DEBUG"]:
    @app.after_request
    def after_request(response):
        response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
        response.headers["Expires"] = 0
        response.headers["Pragma"] = "no-cache"
        return response

# custom filter
app.jinja_env.filters["usd"] = usd

# configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = gettempdir()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

@app.route("/")
@login_required
def index():
    
    #query user's current cash position
    dict_list_cash = db.execute("SELECT cash FROM users WHERE id =:id", id=session.get("user_id"))
    
    #error handle if cash is zero
    if (dict_list_cash[0]['cash']) is None:
        cash = 0
    else:
        #convert to currency friendly format
        cash = Decimal(dict_list_cash[0]['cash']).quantize(Decimal('.01'), rounding=ROUND_DOWN)
    
    #query user's current stocks and all details
    dict_list_stocks = db.execute("SELECT symbol, price, shares, name, total FROM holdings WHERE user_id =:id", id=session.get("user_id"))
    
    #sum cash and stock to display total
    dict_list_sum = db.execute("SELECT SUM (total) AS total_shares FROM holdings WHERE user_id =:id", id=session.get("user_id"))
    if (dict_list_sum[0]['total_shares']) is None:
        sum_stocks = 0
    else:
        sum_stocks = Decimal(dict_list_sum[0]['total_shares']).quantize(Decimal('.01'), rounding=ROUND_DOWN)
    
    grand_total = cash + sum_stocks
    
    
    return render_template("index.html", grand_total=grand_total, dict_list_stocks=dict_list_stocks, cash=cash) 
    
    
@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    if request.method == "POST":
        
        # ensure username was submitted
        if not request.form.get("symbol"):
            return apology("Please provide a stock symbol on which to buy")
    
        # query stock symbol to check if stock exists 
        if not lookup(request.form.get("symbol")):
            return apology("Stock does not exist, try a different symbol")
        else:
            stock = lookup(request.form.get("symbol"))
            name = stock["name"]
            price = Decimal(stock["price"])
            symbol = stock["symbol"]
            
        if not request.form.get("shares"):
            return apology("Please enter the number of shares you wish to buy")
            
            #error handle if shares is not an integer
        if not int(request.form.get("shares")):
            return apology("Invalid shares")
        
        else:
         #select amount of cash user currently has - this is returned as a list of dicts
            dict_list = db.execute("SELECT cash FROM users WHERE id =:id", id=session.get("user_id"))
            
            #select the first amount from the list of dicts that was returned - http://stackoverflow.com/questions/17585898
            if (dict_list[0]['cash']) is None:
                cash = 0
            else:
                cash = Decimal(dict_list[0]['cash'])
         
            #calculate cost of purchase
            shares = request.form.get("shares")
            cost = price * Decimal(shares)
            cashremain = Decimal(cash) - Decimal(cost)
         
            #return error if cash insufficient
            if (cash - cost) < 0:
                return apology("Insufficient cash mate")
                
            else:
                #if successful, add stock purchase to transactions table
                db.execute("INSERT INTO transactions (type, symbol, shares, price, user_id) VALUES('buy', :symbol, :shares, :price, :user_id)", symbol=symbol, shares=shares, price=price, user_id=session.get("user_id"))
                
                #then update user's holdings table
                #if user already has this stock
                rows = db.execute("SELECT symbol, shares FROM holdings WHERE user_id = :id AND symbol = :symbol", id=session.get("user_id"), symbol=symbol)
                if len(rows) > 0:
                    #then add some more
                    new_shares = Decimal(shares) + Decimal(s[0]['shares'])
                    new_total = Decimal(new_shares) * price
                    if new_total is not None:
                        new_total = Decimal(new_total).quantize(Decimal('.01'), rounding=ROUND_DOWN)
                        
                    db.execute("UPDATE holdings SET shares =:new_shares, total =:new_total WHERE user_id =:id AND symbol = :symbol", new_shares=new_shares, new_total=new_total, id=session.get("user_id"), symbol=symbol)
                
                #else create a new holding
                else:
                    total = Decimal(cost).quantize(Decimal('.01'), rounding=ROUND_DOWN)
                    db.execute("INSERT INTO holdings VALUES(:symbol, :price, :shares, :user_id, :name, :total)",  symbol=symbol, price=price, shares=shares, user_id=session.get("user_id"), name=name, total=total)
                
                #then minus amount of cash by cost of purchase
                db.execute("UPDATE users SET cash =:cash WHERE id =:id", cash=cashremain, id=session.get("user_id"))
                
                return redirect(url_for("index"))

    # else if user reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("buy.html") 

@app.route("/history")
@login_required
def history():
    """Show history of transactions."""
    return apology("TODO")

@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in."""

    # forget any user_id
    session.clear()

    # if user reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username")

        # ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password")

        # query database for username
        rows = db.execute("SELECT * FROM users WHERE username =:username", username=request.form.get("username"))

        # ensure username exists and password is correct
        if len(rows) != 1 or not pwd_context.verify(request.form.get("password"), rows[0]["hash"]):
            return apology("invalid username and/or password")

        # remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # redirect user to home page
        return redirect(url_for("index"))

    # else if user reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")

@app.route("/logout")
def logout():
    """Log user out."""

    # forget any user_id
    session.clear()
 
    # redirect user to login form
    return redirect(url_for("login"))

@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    if request.method == "POST":
        
        # ensure username was submitted
        if not request.form.get("symbol"):
            return apology("Please provide a stock symbol to quote on")
    
        # query stock symbol to check if stock exists 
        if not lookup(request.form.get("symbol")):
            return apology("Stock does not exist, try a different symbol")
            
        #if it does, lookup the stock information, return and display it    
        else:
            stock = lookup(request.form.get("symbol"))
            name = stock["name"]
            price = Decimal(stock["price"])
            symbol = stock["symbol"]
            
            return render_template("quoted.html", name=name, price=price, symbol=symbol)
    
    # else if user reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("quote.html")   
    
@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user."""
    session.clear()
    
    if request.method == "POST":

        # ensure username was submitted
        if not request.form.get("username"):
            return apology("plz provide username")

        # ensure password was submitted
        elif not request.form.get("password"):
            return apology("plz provide password")

        # ensure confirm password was submitted and matches
        elif not request.form.get("confirm_password"):
            return apology("must confirm password")
        elif (request.form.get("confirm_password") != request.form.get("password")):
            return apology("passwords must match!")
            
        # query database for username to check if username exists 
        rows = db.execute("SELECT * FROM users WHERE username = :username", username=request.form.get("username"))
        if len(rows) == 1:
            return apology("username already exists")

        # if all is well, write username and hashed passwoSrd to database
        db.execute("INSERT INTO users (username, hash) VALUES(:username, :hash)", username=request.form["username"], hash=pwd_context.encrypt(request.form["password"]))
        
        # then log user in automatically
        return redirect(url_for("index"))
        
    # else if user reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")
    

@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    if request.method == "POST":
        
        # ensure username was submitted
        if not request.form.get("symbol"):
            return apology("Please provide a stock symbol on which to sell")
    
        # query stock symbol to check if stock exists 
        if not lookup(request.form.get("symbol")):
            return apology("Stock does not exist, try a different symbol")
        else:
            stock = lookup(request.form.get("symbol"))
            name = stock["name"]
            price = Decimal(stock["price"])
            symbol = stock["symbol"]
            
        if not request.form.get("shares"):
            return apology("Please enter the number of shares you wish to sell")
            
        #error handle if shares is not an integer
        if not int(request.form.get("shares")):
            return apology("Invalid shares")

        #query holdings to determine if sufficient number of shares to sell
        rows = db.execute("SELECT shares FROM holdings WHERE user_id =:id AND symbol =:symbol", symbol=symbol, id=session.get("user_id"))
        if len(rows)<1:
            return apology("You don't have any shares of this company!")
        
        #calculate holdings after sale
        shares = (rows[0]['shares'])   
        sell_shares = int(request.form.get("shares"))
        new_shares = shares - sell_shares
        new_total = new_shares * price
        
        if new_shares < 0:
            return apology("You don't have enough shares for the amount you wish to sell")
        
        #select amount of cash user currently has
        dict_list = db.execute("SELECT cash FROM users WHERE id =:id", id=session.get("user_id"))
        if (dict_list[0]['cash']) is None:
            cash = 0
        else:
            cash = Decimal(dict_list[0]['cash'])
         
        #calculate cash after sale
        earnings = price * Decimal(shares)
        cashafter = Decimal(cash) + Decimal(earnings)
        
        #at this point sale is successful so update cash, transaction list and holdings
        db.execute("UPDATE users SET cash =:cash WHERE id =:id", cash=cashafter, id=session.get("user_id"))
        db.execute("INSERT INTO transactions (type, symbol, shares, price, user_id) VALUES('sell', :symbol, :shares, :price, :user_id)", symbol=symbol, shares=shares, price=price, user_id=session.get("user_id"))
        if new_shares == 0:
            db.execute("DELETE FROM holdings WHERE user_id =:id AND symbol =:symbol", symbol=symbol, id=session.get("user_id"))
        else:
            db.execute("UPDATE holdings SET shares =:new_shares, total =:new_total WHERE user_id =:id AND symbol = :symbol", new_shares=new_shares, new_total=new_total, id=session.get("user_id"), symbol=symbol)
        
        return redirect(url_for("index"))
        
    else:
        return render_template("sell.html") 