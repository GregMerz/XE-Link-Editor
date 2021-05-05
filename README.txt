Members: Cameron Burley(cssc3770) & Greg Merz(cssc3707)
Class: CS 530, Spring 2021
Assignment: Assigmnet #2, Linkage editor

The purpose of the project is to build a link editor program. 
A linkage-editor reads in files and provides corresponding object programs with modification records.
It states any references or definitions for each particular control section
it hands this file to the loader for relocation. Modification records provide support for it's relocation

What it does:
    1. Opens the listing files and generates corresponding object files.
    2. Runs a check on memeory mapping

How to use it:
    1. Compile project by using the makefile. 
        a.Run the command "make". 
    2. Then type in the following command to run “led <file1> <file2> ... <filen>”
    3. Corresponding files will be placed in folder

How we did it:
    1. We parse our listing files
    2. Contigent on it's representation we used that information to build our Estab and object program
    Note: We built interfaces to handle our formatting and our objects
    Note: Our primary objects include; Estab and object program

Objects & Design decisions:
    1. Estab: Our Estab is a hash map (key = control section string, value = Info object containing symbols)
    2. Info: This serves as the key in our ESTAB. This contains information on the control section as well as symbols for said control section;
    3. Object program: This contains information about our current program. This contains information on the actual program
        a. Text record is a struct containing a list of addresses
        b. Modification record is also a struct, containing relevent information
    4. Our main program is the driver for all of this.
        a. It reads in our files and creates objects corresponding to the files.
        b. Creates Estab

Input:
    1. SIC/XE program files

Output:
    1. Object program files for each input file
    2. ESTAB

File Manifest:
    1. main.cpp
    2. estab.cpp
    3. estab.h
    4. info.cpp
    5. info.h
    6. objectprogram.cpp
    7. objectprogram.h

Lessons Learned:
    1. We learned how to work with someone else on a project of this scale,
        a. Communication was vital, but as important as it was it was just as difficult to make decisions and communicate our code 
    2. We learned about different programming styles and how there are multiple ways to solve the question
    3. We learned how to efficiently parse everything given and making simple strings to something more
