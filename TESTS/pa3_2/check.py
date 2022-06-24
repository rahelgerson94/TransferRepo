#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
Created on Fri Jun 24 05:36:01 2022

@author: rahelmizrahi
"""

def scut_line(string, cols, mode):
    cols = [c-1 for c in cols]
    cut_s = ""
    if mode == 'l':
        for c in cols:
            cut_s += string[c] + " "
    else:
        cut_s = ""
        d = delim_locs(mode, string)
        sow = 0
        eow = d[cols[0]]
        cut_s += string[sow: eow] + " "
        for c in cols[1:]:
            eow = d[c]
            sow = d[c-1] + 1
            cut_s += string[sow: eow] + " "
    print(cut_s)
    return cut_s
            
def scut(strings, cols, mode):
    new_ls = delim_locs('n', strings)
    
    
    for i, eol in enumerate(new_ls):
        if i == 0:
            start = 0
            eol = new_ls[0] 
        else:
            eol = new_ls[i] -1
            start = new_ls[i-1] + 1
        
        curr = strings[start:eol]
        scut_line(curr, cols, mode)
        
        #print(cut_s)
        
        
def delim_locs(mode, s):
    delim_locs = []
    if mode == 'c': 
        for i,c in enumerate(s):
            if c == ',':
                delim_locs.append(i)
    elif mode == 'w': 
        comma_locs = []
        for i,c in enumerate(s):
            if c == ' ':
                delim_locs.append(i)
    else: # mode == 'n': 
        comma_locs = []
        for i,c in enumerate(s):
            if c == '\n':
                delim_locs.append(i)
    return delim_locs

def expand(string):
    start = int(string[0])
    end = int(string[2])
    cols = [i for i in range(start, end+1)]
    return cols
    
    
if __name__ == '__main__':
    s = '\n\nalice,30,532,AZ,S\nbob,25,3411,CA,Z\njonas,40,8192,AZ,T\ngreg,50,400,UT,C'
    mode = 'l'
    d = delim_locs(mode, s)
    n = delim_locs('n', s)
    cols = [1,2,7,8,9,10,11,12,13,14,15]
    
    #scut_line(s, cols, mode)
    scut(s, cols, mode)
    