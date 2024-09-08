// CSCI 411 - Spring 2024
// Project Implementation
// Author: Taiga O'Donnell
// Last Edited: 4/4/2024
// Description: This program is an implementation of the Boyer Moore string matching algorithm. This Boyer Moore algorithm uses both the good suffix rule and the bad character rule to 
//              skip alignments along the text to maximize the efficiency of the algorithm. Therefore if the pattern is large and doesn't match the text often, it can skip many alignments.

#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

void badCharacterRule(string pattern, map<char, int> &badCharTable);
void goodSuffixRule(string pattern, vector<int> &goodSuffixTable);
int findSuffixLength(string pattern, int position);
bool isPrefix(string pattern, int position);
int BoyerMoore(string text, string pattern);


void badCharacterRule(string pattern, map<char, int> &badCharTable){
    for(int i = 0;i < pattern.length(); i++){                           //sets up the bad character table with each letter of the pattern
        badCharTable[pattern[i]] = pattern.length()-1-i;
    }
}
void goodSuffixRule(string pattern, vector<int> &goodSuffixTable){
    int suffixLength;                                   //case 1 + 2

    for(int i = 0;i < pattern.length()-1;i++){
        suffixLength = findSuffixLength(pattern, i);
        if(pattern[i-suffixLength] != pattern[pattern.length() - 1 - suffixLength]){
            goodSuffixTable[pattern.length()-1-suffixLength] = pattern.length() - 1 - i + suffixLength;
        }
    }
    int lastPrefix = 1;                                 //case 3
     for(int i = pattern.length() - 1; i >= 0; i--){
        if(goodSuffixTable[i] == 0){
            goodSuffixTable[i] = lastPrefix + pattern.length() - 1 - i;
        }
        if(isPrefix(pattern, i + 1)){
            lastPrefix = i + 1;
        }
    }
}
int findSuffixLength(string pattern, int position){         //function finds the suffix length of the given pattern based on the position
    int length = pattern.length();
    int i = 0;
    
    while( i <= position && pattern[position - i] == pattern[length - i - 1])
        i = i + 1;
    return i;
}
bool isPrefix(string pattern, int position){                 //function to check if the pattern at the position is a prefix of the pattern
    int suffixLength = pattern.length() - position;

    for(int i = 0; i < suffixLength; i++){
        if(pattern[i] != pattern[position + i]){
            return false;
        }
    }
    return true;
}
int BoyerMoore(string text, string pattern){
    int patternLength = pattern.length();
    int textLength = text.length();
    map<char,int> badCharTable;                             //our bad character table will be used as a map and our key will be the letters of the pattern and the data will be alignment to move
    badCharacterRule(pattern, badCharTable);
    vector<int> goodSuffixTable(patternLength,0);
    goodSuffixRule(pattern, goodSuffixTable);               //good suffix table is similar but used as an array since each letter represents as a index so we dont need a map
    map<char,int>::iterator it; 
    int i = patternLength -1;
    int j = 0;
    int shift = 0;
    int badCharShift = 0;

    while(i < textLength){                                  //loop while patternlength -1 is less than the text length else break
        j = patternLength - 1;                              //index starting at the end of the pattern and will be after every i iteration
        while(j >= 0 && pattern[j] == text[i]){             //if there are more letters to match in our pattern and if the letter in both pattern and text match 
            j--;                                            //if it is decrement and move on to the next letter to the left
            i--;
        }
        if(j < 0){                                          //if we've reached the end fo the pattern, that means we found where the pattern occurs in the text
            return i+1;                                     //return where i+1 is because that is where the pattern starts
        }
        else{                                               //if there is a mismatch, then we try to maximize the amount of alignments to move using bad character rule and good suffix rule
            it = badCharTable.find(text[i]);
            if (it == badCharTable.end()){                  //if letter is not in the table
                badCharShift = pattern.length();            //then we move the whole pattern over
            }
            else{                                           //if letter is in the table
                badCharShift = badCharTable[text[i]];       //then we shift based off the table
            }
            shift = max(1, max(badCharShift, goodSuffixTable[j]));      //we find which rule gives us the greatest alignment: bad character table or the good suffix table 
            i += shift;                                                 //then we shift i that amount
        }
    }
    return -1;                                                      //if the pattern  is not in the text at all, then we returned -1 
}

int main(){
    string text = "";
    string pattern = "";

    cout << "Enter the text: ";
    getline(cin, text);

    cout << "Enter the pattern: ";
    getline(cin, pattern);

    if (pattern.empty() || text.empty()) {                          //if either of the pattern or the text is empty then we just quit
        cout << "Pattern or Text is empty." << endl;
    } 
    else {
        int returnVal = BoyerMoore(text, pattern);
        if(returnVal == -1)
            cout << "Pattern is not in text";
        else
            cout << "Boyer Moore: pattern is in text starting at index " << returnVal << endl;
    }
}
