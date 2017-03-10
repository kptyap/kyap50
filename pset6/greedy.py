#-- Greedy in Python --
#K.Yap March 2017
#Finds the least number of coins 'greedy algorithm' that can be given for a user defined amount of money
#
#american coin values for reference:
#q = 25
#d = 10
#n = 5
#p = 1

#ask for input and check it is a positive, non-zero integer
while True:
    try:
        amnt = float(input("How much $$$ are you owed?"))
    except ValueError:
        print("Please enter a dollar amount")
        continue
    if (amnt < 0):
        print("Please enter an amount greater than 0")
        continue
    else:
        break
    
iamnt = 100*amnt
count = 0
coins = [25 , 10, 5, 1]
c = 0   #to traverse the coins list

while (iamnt - coins[c] >= 0):
    iamnt-=coins[c]
    count+=1
    
    if (iamnt - coins[c] >= 0):
        continue
    elif (iamnt == 0):
        break
    else:
        c+=1
        continue

print(count)
