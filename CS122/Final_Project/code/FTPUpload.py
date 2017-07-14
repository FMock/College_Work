from tkinter import *
import tkinter.messagebox
from tkinter.filedialog import askopenfilename
import ftplib

# Frank Mock
# CS122 Final Project
# GUI program that allows a user to upload a file to a server using FTP

def openFile(): 
    filenameforReading = askopenfilename()
    filename.set(filenameforReading)
    
def uploadFile():
    f = "data.txt" #name the file will be given (re-named), after uploaded to server
    text.insert(END, "Opening File...\n")
    myfile = open(filename.get(), 'rb')
    text.insert(END, "Trying to connect to server...\n")
    try:
        ftp = ftplib.FTP('ftp.franks_website.com')

        connect = ftp.login("franks_username", "franks_password")
        message.set(str(connect))
        text.insert(END, message.get() + "\n")
        
        changeDir = ftp.cwd('public_html/CS122')
        message.set(str(changeDir))
        text.insert(END, message.get() + "\n")
        
        text.insert(END, "Uploading file...\n")
        
        transfer = ftp.storlines('STOR '+ f, myfile)
        message.set(str(transfer))
        text.insert(END, message.get())
    except:
        message.set("Could not connect to server")
        
    ftp.quit()
    myfile.close()
    
    
    
window = Tk() # Create a window
window.title("Upload and Graph Data") # Set title

frame1 = Frame(window)
frame1.pack()

scrollbar = Scrollbar(frame1)
scrollbar.pack(side = RIGHT, fill = Y)
text = Text(frame1, width = 40, height = 10, wrap = WORD, 
            yscrollcommand = scrollbar.set)
text.pack()
scrollbar.config(command = text.yview)

frame2 = Frame(window)
frame2.pack()

Label(frame2, text = "Enter a filename: ").pack(side = LEFT)
filename = StringVar()
message = StringVar()
Entry(frame2, width = 20, textvariable = filename).pack(side = LEFT)
Button(frame2, text = "Browse", command = openFile).pack(side = LEFT)
Button(frame2, text = "Upload File", command = uploadFile).pack(side = LEFT)
text.insert(END, "Choose a file to upload to server\n")
window.mainloop() # Create an event loop
