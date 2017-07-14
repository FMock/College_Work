from tkinter import *
import tkinter.messagebox

# Needed to allow user to browse and select a file
from tkinter.filedialog import askopenfilename

# This program will determine which letters occur the
# most frequently in text file. The program lets the
# user select the text file by using the tkinter
# askopenfilename dialog.


# Gets the file name and passes it to the analyzeFile
# function
def showResult():
    analyzeFile(filename.get())

# This function opens a file for reading and then analyzes
# the contents by counting the occurences of each letter
def analyzeFile(filename):
    try:
        infile = open(filename, "r") # Open the file
    
        counts = 26 * [0] # Create and initialize counts
        for line in infile:
            # Invoke the countLetters function to count each letter
            countLetters(line.lower(), counts)
        
        # Display results
        for i in range(len(counts)):
            if counts[i] != 0:
                text.insert(END, chr(ord('a') + i) + 
                            " appears  " + str(counts[i])
                  + (" time" if counts[i] == 1 else " times") +
                                                          "\n")
    
        infile.close() # Close file
    except IOError:
        tkinter.messagebox.showwarning("Analyze File", 
                                    "File " + filename 
                                            + " does not exist")  
# Count each letter in the string 
def countLetters(line, counts): 
    for ch in line:
        if ch.isalpha():
            counts[ord(ch) - ord('a')] += 1

# Presents the user with a file dialog so they may
# choose the file to be analyzed           
def openFile(): 
    filenameforReading = askopenfilename()
    filename.set(filenameforReading)


########  Begin creating the GUI  #########

# Create a window and give it a title      
window = Tk()
window.title("Occurrence of Letters")

f1 = Frame(window)
f1.pack()

scrollbar = Scrollbar(f1)
scrollbar.pack(side = RIGHT, fill = Y)
text = Text(f1, width = 40, height = 10, wrap = WORD, 
            yscrollcommand = scrollbar.set)
text.pack()
scrollbar.config(command = text.yview)

f2 = Frame(window)
f2.pack()

Label(f2, text = "Enter a filename: ").pack(side = LEFT)
filename = StringVar()
Entry(f2, width = 20, textvariable = filename).pack(side = LEFT)
Button(f2, text = "Browse", command = openFile).pack(side = LEFT)
Button(f2, text = "Show Result",
                              command = showResult).pack(side = LEFT)

window.mainloop() # Create an event loop
