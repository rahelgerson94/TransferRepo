#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
Created on Fri Jul  8 12:38:23 2022

@author: rahelmizrahi
"""
import random as r
import re
def rand_name():
    alphabet = 'abcdefghijklmnopqrstuvwxyz'
    length = r.randint(1,20)
    name = ""
    for i in range(length):
        rand_char_idx = r.randint(0,25) 
        name+=alphabet[rand_char_idx]
    return name

def gen_line_data(start, num_games):
    
    g1 = [x for x in range(start,start+3)]
    line= ""
    for i in range(num_games):
        line+=str(g1)

    return line
     
def gen_data(numP, numG, path ):
    
   with open(path, "w+") as f:
        for i in range(0,numP):
            name = "a"+str(i)
            if i < numP-1:
                #name = rand_name() + " " + rand_name()
                data = gen_line_data(i,numG)
                
            else:
                data = data = gen_line_data(numP-2,numG)
                #print(name + data)
            data=re.sub(" ", "", data)
            f.write(name+data)
            f.write("\n")

if __name__ == '__main__':
    path = "/Users/rahelmizrahi/Library/Mobile_Documents/com~apple~CloudDocs/csc352/cs352_pas/TESTS/pa5/data100.txt"
    gen_data(100,100,path)
    # line = ""
    
    # numP = 100
    # numG = 100
    # for i in range(0,numP):
    #     name = rand_name() + " " + rand_name()
    #     data = gen_line_data(i,numG)
    #     print(name + data)
    
   
    