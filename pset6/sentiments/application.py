from flask import Flask, redirect, render_template, request, url_for

import helpers
import sys
import os
from analyzer import Analyzer

app = Flask(__name__)

@app.route("/")
def index():
    return render_template("index.html")

@app.route("/search")
def search():

    # validate screen_name
    screen_name = request.args.get("screen_name", "").lstrip("@")
    if not screen_name:
        return redirect(url_for("index"))

    # get screen_name's tweets
    list_tweets = helpers.get_user_timeline(screen_name, 100)

    
    # instantiate analyzer
    positives = os.path.join(sys.path[0], "positive-words.txt")
    negatives = os.path.join(sys.path[0], "negative-words.txt")
    analyzer = Analyzer(positives, negatives)
    
    #set up counters
    positive= 0.0
    negative = 0.0
    neutral = 0.0
    
    #classify tweets
    for tweet in list_tweets:
        score = analyzer.analyze(tweet)
    
        if score > 0.0:
                positive += 1
        elif score < 0.0:
                negative += 1
        elif score == 0:
                neutral += 1

    # generate chart
    chart = helpers.chart(positive, negative, neutral)

    # render results
    return render_template("search.html", chart=chart, screen_name=screen_name)
