# Word-Search-Generator
A C++ program to generate every possible word search puzzle with a given grid size and set of words.

The input format consists of a line with dimensions, which is columns x rows, and floowing that is a list of words
separated by line each preceded by a '+' or a '-'.

A '+' indicates that this word should appear in the puzzle.
A '-' indicates that this word should not appear in the puzzle.

Here is a sample input:

3 2
\+ cat
\+ one


This input will give the output 

8 solution(s)
Board: 
  one
  cat
Board: 
  one
  tac
Board: 
  cat
  one
Board: 
  tac
  one
Board: 
  eno
  cat
Board: 
  eno
  tac
Board: 
  cat
  eno
Board: 
  tac
  eno
