# Chapter 12, Problem 12.22
# This program displays a 3x3 grid of
# CoinLabels that flip when a user
# clicks on them

from tkinter import *

# CoinLabel extends Label
# Button-1 is bound to the flip method
class CoinLabel(Label):
    def __init__(self, container, text):
        Label.__init__(self, container, 
                        text = text, font = "Arial 28 bold")
        self.bind("<Button-1>", self.flip)
    
    # The flip method changes the text on a CoinLabel object
    # The left mouse button is bound to this method  
    def flip(self, event):
        if self["text"] == "H":
            self["text"] = "T"    
        else:   
            self["text"] = "H"


# The main class creates the GUI window and creates the 3X3
# grid of CoinLables. The application runs the root window
# loop.
class MainClass:
    def __init__(self):
        # Create a root window and give it a title
        root = Tk()
        root.title("Flip Coins")
        
        # Frame is a child of the root window
        frame = Frame(root)
        
        # Place the frame in the root window
        frame.pack()
        
        # Create a 3X3 grid of CoinLables
        for i in range(3):
            for j in range(3):
                CoinLabel(frame, text = "H").grid(row = i, column = j)
        
        root.mainloop() # Create an event loop

# Create a MainClass object
MainClass()