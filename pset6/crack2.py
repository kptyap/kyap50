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
    except (ValueError, IndexError) as e:  #Multiple exceptions: http://stackoverflow.com/questions/6470428/catch-multiple-exceptions-in-one-line-except-block
        print("Please enter a hash")
        break
        
    if (len(hash) != 13):
        print("Hash must be of length 13")
        break
    else:
        break
    

#we know the salt is the 2-digit '50'
#we know the key is limited to 4 alphabetical letters
#cycle through all possibilities of the key till we match the hash
#credit to http://stackoverflow.com/questions/42673561/iterate-through-multiple-lists-of-characters-in-order

result = "fail" #default result

for letter1 in string.ascii_letters:
    if(crypt.crypt(letter1, "50") == hash):
        print(letter1)
        result = "success"
        break
        
    for letter2 in string.ascii_letters:
        if(crypt.crypt(letter1+letter2, "50") == hash):
            print(letter1+letter2)
            result = "success"
            break
            
        for letter3 in string.ascii_letters:
            if(crypt.crypt(letter1+letter2+letter3, "50") == hash):
                print(letter1+letter2+letter3)
                result = "success"
                break
                
            for letter4 in string.ascii_letters:
                if(crypt.crypt(letter1+letter2+letter3+letter4, "50") == hash):
                    print(letter1+letter2+letter3+letter4)
                    result = "success"
                    break
print(result)
