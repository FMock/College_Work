# Frank Mock  CS 122  Test 3
# Chapter 13, Problem 13.13

from tkinter import *

def displayGraph(canvas, vertices, edges):
    radius = 3
    
    # Draw the nodes and the node numbers
    for vertex, x, y in vertices:
        canvas.create_text(x - 2 * radius, y - 2 * radius,
                           text = str(vertex), tags = "graph")
        canvas.create_oval(x - radius, y - radius, x + radius,
                           y + radius, fill = "black", tags = "graph")
    
    # Draw each vertex   
    for v1, v2 in edges:
        canvas.create_line(vertices[v1][1], vertices[v1][2],
                           vertices[v2][1], vertices[v2][2], tags = "graph")


# The main function gets the graph input file from the user and
# uses the displayGraph function to draw a graphic representation
# of the graph        
def main():
    # Prompt the user to enter a file name
    f1 = input("Enter the file for the graph: ").strip()
    
    # open file for input
    infile = open(f1, "r")
    
    # Read the first line from the file
    numberOfVertices = eval(infile.readline())
    
    #print(numberOfVertices)
   
    # Create a list to hold vertices and one to hold edges 
    vertices = []
    edges = []
    
    # Fill the vertices and edges list with data from the graph file
    for i in range(numberOfVertices):
        # Read the info for one vertex
        items = infile.readline().strip().split()
        vertices.append([eval(items[0]), eval(items[1]), eval(items[2])])
        for j in range(3, len(items)):
            edges.append([eval(items[0]), eval(items[j])])
            
    #print(vertices)
    #print(edges)
    # Create a window
    window = Tk()
    window.title("Display Graph")
    
    # Create a frame to hold a canvas object
    frame1 = Frame(window)
    frame1.pack()
    
    # The canvas object will have text, ovals and lines drawn on it
    # by the display graph function
    canvas = Canvas(frame1, width = 300, height = 200)
    canvas.pack()
    
    # Call the displayGraph function to draw the graph
    displayGraph(canvas, vertices, edges)
    
    # The main loop 
    window.mainloop()
    
main() 