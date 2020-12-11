<p align="center">CS 211 Homework 1</p>
<p align="center">Jeff Ames</p>
<p align="center">Fall 2020</p>

## Introduction

This assignment will give you some initial experience with programming in C. 
Your task is to write the following small C programs.

- Please be careful to foilow the I/O formats exactly. 
- You can assume that inputs will be correctly formatted.
  
## sortArray.c (20 points)

Write a program that will read an array from a file and sort the given array. 
It should return the array sorted with all even numbers in ascending order at the front
followed by all odd numbers in descending order. You may assume that input array will not 
have more than 20 elements.  

You can use any sorting algorithm you like, but you must implement
it yourself (no using library sort functions).  

**Input format:** Your program will take the file name as a command-line input. The first line 
in the file provides the total number of values in the array. The second line will contain a list 
of numbers separated by tabs. For example a sample input file `file1.txt` is:
```  
6  
25 10 1 99 4 2  
```  
**Output format:** Your output will be the sorted list of numbers, even numbers (ascending) and then odd
numbers (descending), each separated by tabs.  
```
$ ./sortArray file1.txt
2 4 10 99 25 1
```

## linkedList.c (20 points)
In this part, you’ll implement a linked list that maintains a list of integers in sorted (increasing) order. 
The list can contain duplicate elements.  

**Input format:** This program takes a file name as an command-lineargument. The file contains a number of lines of 
input (possibly 0). Each line contains a character, either `i` or `d`, followed by a tab character, and then an integer.  
If the line starts with `i`, your program should insert that number in the linked list in sorted order. If it is already 
present, your program can insert it before or after the existing entry.  

If the line starts with a `d`, your program should delete the value from the linked list. If there are duplicates, your 
program should delete only the first occurrence of the value. If the requested value is not present in the linked list, 
your program should ignore this line of the input.  

**Output format:** If the input file doesn’t exist, your program should print `error`.  

Otherwise, your program should print two lines of output:
- the number of nodes in the list (including duplicates)
- a tab-separated list of the values of the linked list in order, with duplicate values only printed once.  
### Example Execution  
Let's assume we have 3 text files with the following contents:  
```
file1.txt:  
d       7  
i       10  
i       12  
d       10  
i       12  
i       10  
```
Then the result will be:  
```
$ ./linkedList file1.txt  
3  
10       12  
```
