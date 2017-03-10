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

letters = string.ascii_letters
lcounter = 0
i = 0
j = 0
k = 0
l = 0
tryhash = "a"
word = [letters[i]]

while(tryhash != hash):
    for c in letters:
        word = [letters[i]]
        tryword = ''.join(word)
        tryhash = crypt.crypt(tryword, "50")
        
        if (tryhash == hash):
            print(word)
            break
            
        i += 1
        
        if (lcounter > 0) and (i == 52):
            i = 0
            if (lcounter == 1) and (j == 0):
                word.insert(lcounter, letters[j])
            j += 1
           
            if (lcounter > 1) and (k == 52):
                j = 0
                if (lcounter == 2) and (k == 0):
                    word.insert(lcounter, letters[k])
                k += 1
                
                if (lcounter > 2) and (k == 52):
                    k = 0
                    if (lcounter == 3) and (l == 0):
                        word.insert(lcounter, letters[l])
                    l += 1
        
    lcounter += 1