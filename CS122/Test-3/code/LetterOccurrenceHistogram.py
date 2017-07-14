from tkinter import *
import tkinter.messagebox

# Class used to display the bar chart
from BarChart import BarChart

# Needed to allow user to browse and select a file
from tkinter.filedialog import askopenfilename

# This program will determine which letters occur the
# most frequently in text file. The program lets the
# user select the text file by using the tkinter
# askopenfilename dialog. The program will display the
# results in text form and as a bar chart


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
            
            
        # A list to hold the data that will be represented in
        # the bar chart
        data = []
        
        # Build the data multidimensional list that
        # the BarChart object will use
        for i in range(len(counts)):
            s = chr(ord('a') + i)
            data.append([counts[i] + 8, s, "red"])
                    
        # Create a BarChart object and pack it in to the GUI window
        # This will display the bar chart in the window
        c = BarChart(window, data)
        c.pack()
        
        # Display textual number occurrence results
        for i in range(len(counts)):
            if counts[i] != 0:
                text.insert(END, chr(ord('a') + i) + 
                            " appears  " + str(counts[i])
                  + (" time" if counts[i] == 1 else " times") +
                                                          "\n")
        # Close file
        infile.close()
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
                              
                              
# Create an event loop
window.mainloop()
