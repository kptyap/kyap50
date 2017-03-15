import nltk
from nltk.tokenize import TweetTokenizer

class Analyzer():
    """Implements sentiment analysis."""

    def __init__(self, positives, negatives): #load positive and negative text files into memory
        """Initialize Analyzer."""
        self.positives = set()
        self.negatives = set()
       
        filep = open('positive-words.txt', "r")
        for line in filep:
           if not (line.startswith(";")):
                self.positives.add(line.strip())

        filep.close  
        
        filen = open('negative-words.txt', "r")
        for line in filen:
            if not (line.startswith(";")): 
                self.negatives.add(line.strip())
        filen.close
        
    def analyze(self, text):
        """Analyze text for sentiment, returning its score."""
        
        tknzr = TweetTokenizer()
        tokens = tknzr.tokenize(text)
        
        #sentiment counter
        positivecounter = 0
        negativecounter = 0
        
        #check each word if it corresponds to a word in a text file
        for word in tokens:
            if (word.lower() in self.positives):
                positivecounter += 1
            elif (word.lower() in self.negatives):
                negativecounter += 1
                
        sentimentcounter = positivecounter - negativecounter
        
        return sentimentcounter
        
        

        
