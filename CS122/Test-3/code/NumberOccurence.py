# This program determines which numbers occur the
# from a given list of numbers

def main():
    print("This program determines which numbers occur the most ")
    print("frequently in a list of numbers")
    print("")
    
    # Main loop of program
    while True:
        s = input("Enter numbers, each separated by a space: ").strip()
        numbers = [eval(x) for x in s.split()]
    
        # Create an empty dictionary
        dictionary = {}
        
        # Count the number occurences and store values in
        # dictionary
        for number in numbers:
            if number in dictionary:
                dictionary[number] += 1
            else:
                dictionary[number] = 1
        
        # Get the maximum values
        maxCount = max(dictionary.values())
    
        pairs = list(dictionary.items())
        
        # Reverse pairs in the list
        items = [[x, y] for (x, y) in pairs]
		
		# Display numbers to the user
        print("The numbers that occur the most are ", end = "")
        for (x, y) in items:
            if y == maxCount:
                print(x, end = " ")
        
		# Ask the user if they would like to play again
        again = input("Again? (y/n)")
        if again == 'n':
            print("Goodbye")
            break

main()