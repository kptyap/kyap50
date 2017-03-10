import string
import itertools

my_string = "alex"
for letter1 in string.ascii_letters:
    if letter1 == my_string:
        print("success")
    for letter2 in string.ascii_letters:
        if letter1 + letter2 == my_string:
            print("success")
        for letter3 in string.ascii_letters:
            if letter1 + letter2 + letter3 == my_string:
                print("success")
            for letter4 in string.ascii_letters:
                if letter1 + letter2 + letter3 + letter4 == my_string:
                    print("success")
                    
    
    