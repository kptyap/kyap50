#-- Mario in Python --
#K.Yap March 2017
#Creates a half pyramid of hashes with the height based off a user's input
#

# ask valid user input (from http://stackoverflow.com/questions/23294658/asking-the-user-for-input-until-they-give-a-valid-response)
while True:
    try:
        height = int(input("Height: "))
    except ValueError:
        print("Please enter a number between 1 and 23")
        continue #try again - return to start of the loop
    
    if (height < 0) or (height > 23):
        print("Please enter a number between 1 and 23")
        continue
    else:
        break #validated, we can now exit loop

#with that out of the way, time to actually print the pyramid
for i in range(height):
    for j in range (height-i-1): #print this number of spaces
        print(" ", end='')
    for k in range (i+2): #print this number of hashes
        print("#", end='')
    print() #go to the next line and repeat the above two loops
    