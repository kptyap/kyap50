#-- Crack in Python --
#K.Yap March 2017
#Cracks a simple password that has been encrypted using the inbuilt crypt function

import sys
import crypt
import string


#take input from cmd line and checks it is a hash function of length 13
while True:
    try:
        hash = str(sys.argv[1])
    except ValueError:
        print("Please enter a hash")
        break
    if (len(hash) != 13):
        print("Hash must be of length 13")
        break
    else:
        break
# TODO: need to account for no arg entered
    

#we know the salt is the 2-digit '50'
#we know the key is limited to 4 alphabetical letters
#cycle through all possibilities of the key till we match the hash



for letter1 in string.ascii_letters:
    if(crypt.crypt(letter1, "50") == hash):
        print ("success")
    
        
