from __future__ import division
import socket
import math
import os
import struct

from ctypes import *

# CS160 Frank Mock
# Performs entropy analysis on packet data
# using Shannon's Algorithm


class PacketAnalyzer:

    def __init__(self):


        self.entropyResult = 0


    # Converts the packets ascii values into their decimal values
    # and returns them in a list
    def getNumericList(self, packetData):
        numericList = []
        
        # Turn packetData into string
        s = "".join(packetData)

        # Turn each character in string into a decimal number
        for n in s:
            numericList.append(ord(n))

        return numericList
    
    # Counts the occurences of distinct characters
    # Counts the total number of characters
    # source is a string of decimal numbers
    # returns an character occurence map and total number of characters
    def hist(self,source):
        hist = {}
        l = 0
        for e in source:
            l += 1
            if e not in hist:
                hist[e] = 0
            hist[e] += 1
        return(l, hist)

    # Shannon's Entropy algorithm
    # Returns the entropy/character for the given data
    # result of algorithm is a real number
    def determineEntropy(self, hist, l):
        elist = []
        for v in hist.values():
            c = v / l
            elist.append(-c * math.log(c, 2))
        return sum(elist)
    
    # Passes packet data to Shannon's entropy algorithm
    # returns the results
    # Expected return value is a real number (eg. 2.89)
    def entropyAnalysis(self, packetData):
        print "Performing Entropy analysis\n"
        
        # Turn the packetData into decimal values
        numList = self.getNumericList(packetData)
        
        # Gets the number of occurences of each value in the list
        # and the total number of characters
        (l,h) = self.hist(numList)
        
        # Runs the Entropy algorithm on the list
        self.entropyResult = self.determineEntropy(h,l)
        return self.entropyResult
    
    # Accessor method that returns the entropy result
    def getEntropyResult(self):
        return self.entropyResult
