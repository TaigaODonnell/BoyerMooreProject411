# Boyer Moore Algorithm Project Implementation 
By Taiga O'Donnell

## Small Description
This program is an implementation of the Boyer Moore string matching algorithm. It uses both the good suffix rule and the bad character rule to skip alignments along the text to maximize the efficiency of the algorithm. Therefore if the pattern is large and doesn't match the text often, it can skip many alignments.


## How to to run the Program
Given that the tests work, here is how to run the program:
1) Using the provided tests
   * Unzip the Tests.zip folder
   * Compile the program
   * The tests can be used by using the script runTests: ./runTests \<executable> \<test folder>
3) Providing user input
   * The first input is the text string. The text string can be of any length and with spaces. Do not provide nothing or else the algorithm does not work.
   * The second input is the pattern string. The pattern string can also be of any length and with spaces as well. Do not provide anything or else the algorithm does not work. 

## The result of the program
The result of the text will be of 3 cases. Either
1) The pattern or the text string is empty
2) The pattern is not in the text
3) The pattern is in the text and will give the index at which the pattern starts at in the text string
