# Imports
import os
import sys
from moviepy.editor import VideoFileClip
from pydub import AudioSegment
import numpy as np

# Global variables
fileName = sys.argv[1]
fileType = fileName[-3:]

# Function that checks every folder on the computer to see if it exists
def findFile(fileName, searchPath='/'):

    # Loops through ever directory
    for root, dirs, files in os.walk(searchPath):

        # Will return the file path
        if fileName in files:
            return os.path.join(root, fileName)
    
    # Return for the function
    return

# Converts a txt file into bytes, then bits
def byteCreatorTxt(filePath):

    # Open the in binary mode
    with open(filePath, 'rb') as file:

        # Reads the contents of the file
        content = file.read()

    # Loops through the bytes in the content
    for byte in content:

        # Converts the byte into its bit representation
        bitRepresentation = bin(byte)[2:].zfill(8)

        # Prints the 8 bits
        print(bitRepresentation)

# Converts a pdf file into bytes, then bits
def byteCreatorPdf(filePath):

    # Open the in binary mode
    with open(filePath, 'rb') as file:

        # Reads the contents of the file
        content = file.read()

    # Loops through the bytes in the content
    for byte in content:

        # Converts the byte into its bit representation
        bitRepresentation = bin(byte)[2:].zfill(8)

        # Prints the 8 bits
        print(bitRepresentation)

# Converts a png file into bytes, then bits
def byteCreatorPng(filePath):

    # Open the in binary mode
    with open(filePath, 'rb') as file:

        # Reads the contents of the file
        content = file.read()

    # Loops through the bytes in the content
    for byte in content:

        # Converts the byte into its bit representation
        bitRepresentation = bin(byte)[2:].zfill(8)

        # Prints the 8 bits
        print(bitRepresentation)

# Converts a jpg file into bytes, then bits
def byteCreatorJpg(filePath):

    # Open the in binary mode
    with open(filePath, 'rb') as file:

        # Reads the contents of the file
        content = file.read()

    # Loops through the bytes in the content
    for byte in content:

        # Converts the byte into its bit representation
        bitRepresentation = bin(byte)[2:].zfill(8)

        # Prints the 8 bits
        print(bitRepresentation)

# Converts a mp3 file into bytes, then bits
def byteCreatorMp3(filePath):

    with open(filePath, 'rb') as mp3File:
        content = mp3File.read()

    # Loops through the bytes in the content
    for byte in content:

        # Converts the byte into its bit representation
        bitRepresentation = bin(byte)[2:].zfill(8)

        # Prints the 8 bits
        print(bitRepresentation)

# Convrts a mp4 file into bytes, then bits
def byteCreatorMp4(filePath):
    # Grabs the video file
    clip = VideoFileClip(filePath)

        # Get the byte representation of the video
    content = np.array(list(clip.iter_frames())).tobytes()

        # Loop through the bytes in the content
    for byte in content:

        # Converts the byte into its bit representation
        bitRepresentation = bin(byte)[2:].zfill(8)

        # Prints the 8 bits
        print(bitRepresentation)

# Grabs the resultin filepath
result = findFile(fileName)

# If there is a file path, then it will print 
if result: 

    # Will run if the file is a txt file
    if fileType == "txt":
        print(f"The file {fileName} exists at the path {result}.")
        byteCreatorTxt(result)

    # Will run if the file is a png file
    elif fileType == "pdf":
        print(f"The file {fileName} exists at the path {result}.")
        byteCreatorPdf(result)

    # Will run if the file is a png file
    elif fileType == "png":
        print(f"The file {fileName} exists at the path {result}.")
        byteCreatorPng(result)

    # Will run if the file is a png file
    elif fileType == "jpg":
        print(f"The file {fileName} exists at the path {result}.")
        byteCreatorJpg(result)

    # Will run if the file is a mp3 file
    elif fileType == "mp3":
        print(f"The file {fileName} exists at the path {result}.")
        byteCreatorMp3(result)

    # Will run if the file is a mp3 file
    elif fileType == "mp4":
        print(f"The file {fileName} exists at the path {result}.")
        byteCreatorMp4(result)

# Else, a print statement saying the file doesn't exist
else:
    print("File does not exist")