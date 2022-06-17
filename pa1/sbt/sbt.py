#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
Created on Mon Jun  6 15:14:48 2022

@author: rahelmizrahi
"""
import os
#print(os.getcwd())
#print("\n")

os.chdir("/Users/rahelmizrahi/Library/Mobile Documents/com~apple~CloudDocs/CSC352/cs352_pas/pa1/pythagorean/")
#Library/"Mobile Documents"/com~apple~CloudDocs/CSC352/cs352_pas/pa1/pythagorean/
#print(os.getcwd())

#cpath = input("C source file path:")
cpath = "pythagorean.c"
#test_dir = input("Test file directory path:")
test_dir = "/tests"
#command_result = os.popen("gcc -Wall -Werror -std=c11 pythagorean.c")
command_result = os.popen("gcc -Wall -Werror -std=c11 " + cpath)

command_result = command_result.read()
print(command_result)

if command_result == '': #compilation succeful!
    for i in sorted(os.listdir("./tests")):
        if i == ".DS_Store":
            continue
        else:
            exe_output = os.popen("./a.out < tests/{}/input.txt".format(i)).read()
            
            #print("exe output")
            #print(exe_output)
            
            expected_output = os.popen("cat tests/{}/output.txt".format(i)).read()
            #print("expected output")
            #print(expected_output.read())

            if expected_output.strip() == exe_output.strip():
                print("#### Test: {} passed! ####".format(i))
            else:
                print("#### Test: {} failed! ####".format(i))


else:
    print("failed to compile your code")