# Frank Mock CS 122 Test 3


# This program determines if a bank is unsafe
# The user enters a unsafe limit and if a bank's
# total assets are below this limit the bank is
# unsafe


# Get the number of banks and unsafe limit
rows = eval(input("Enter the number of banks "))
limit = eval(input("Enter the asset limit "))


# Create a master list to hold other lists of various sizes
masterList = []

# The number of columns is dynamic, it depends on how many
# banks borrowed from a particular bank of row(n)
columns = 0

# Get bank input data from user and populate masterList
# Put each bank's data in a row
for i in range(rows):
    row = [] # Add an empty new Row
    columns = 2
    balance = eval(input("What is the balance of bank " + str(i) + "? "))
    b = eval(input("How many banks borrowed from bank " + str(i) + "? "))
    columns += 2*b
    for j in range(columns):
        if j == 0:
            row.append(balance)
        elif j == 1:
            row.append(b)
        elif j > 1 and j%2 == 0:
            id = eval(input("Enter Bank ID "))
            row.append(id)
        elif j > 1 and j%2 != 0:
            borrowed = eval(input("Enter the amount bank borrowed "))
            row.append(borrowed)
    masterList.append(row)

# A list to hold the unsafe banks    
unsafeBanks = []

# Determine which banks are unsafe
# A bank's total assets < limit == unsafe
for i in range(rows):
    assets = 0
    bank = i
    for j in range(len(masterList[i])):
        if j == 0:
            assets += masterList[i][j]
        elif j > 1 and j%2 != 0:
            assets += masterList[i][j]
        else:
            pass
    print("Total assets of bank " + str(bank) + " = " + str(assets))
    if assets < limit:
        unsafeBanks.append(bank)
        
# Print the results to the user        
numUnsafeBanks = len(unsafeBanks)
print("There are " + str(numUnsafeBanks) + " unsafe banks.")

if numUnsafeBanks > 0:
    print("The unsafe banks are: ", end="")
    for i in unsafeBanks:
        print(str(i) + " ")