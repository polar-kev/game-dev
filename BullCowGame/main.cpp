//
//  main.cpp
//  BullCowGame
//
//  Created by Kevin Semple on 2017-08-12.
//  Copyright © 2017 ksemp. All rights reserved.
//

#include <iostream>

bool isogramCheck(std::string myword);
int bullCheck(std::string goalWord, std::string guess);
int cowCheck(std::string goalWord, std::string guess);
bool isValid(std::string goalWord,std::string myword);
void init();
bool winCheck(std::string goalWord, std::string guess);


int main(int argc, const char * argv[]) {
    int choice;
    std::string garbage;
    
    do{
        std::cout   << "Welcome to Bulls and Cows.\n"
                    << "Can you guess the isogram I've got in my head?\n"
                    << "Please make a selection: \n"
                    << "1.\t Play Bulls and Cows\n"
                    << "2.\t Explain the Rules\n"
                    << "3.\t Change the Difficulty\n"
                    << "4.\t Quit\n";
        std::cin >> choice;
        
        switch(choice){
            case 1:
                //initialize game
                std::getline(std::cin,garbage);
                init();
                break;
            case 2:
                //Explain the Rules
                break;
            case 3:
                //change the difficulty
                break;
            case 4:
                std::cout << "Quitting Bulls and Cows";
                return 0;
            default:
                break;
        }
    }while(choice != 4);
    
   
}


//initialize the game
void init(){
    std::string guessWord;
    std::string goalWord = "clown";
    int bulls;
    int cows;
    int attempts = 10;
    
    while(attempts > 0){
        std::cout << "\nGuess a " << goalWord.length() << " letter word.\n";
        std::cout << "You have " << attempts-- << " remaining attempts.\n";
        std::getline(std::cin,guessWord);
        std::cout << "You guessed: " << guessWord << std::endl;
        if(isValid(goalWord, guessWord)){
            bulls = bullCheck(goalWord, guessWord);
            cows = cowCheck(goalWord, guessWord);
            std::cout << "Bulls: " << bulls << std::endl;
            std::cout << "Cows: " << cows << std::endl;
            
            if(winCheck(goalWord, guessWord)){
                std::cout << "You win! The word was " << goalWord << "!" << std::endl << std::endl;
                break;
            }
        }else{
            std::cout << "Make sure you enter a valid word.\n";
        }
    }//end while
    if(attempts==0){
        std::cout << "You have 0 attempts left. YOU LOSE!\n\n";
    }
}//end of init()

//isogram is a word where each letter only appears once
bool isogramCheck(std::string myword){
    for(int i=0;i<myword.length();i++){
        for(int j=0;j<myword.length();j++){
            if(i==j){
                break;
            }
            if(myword[i] == myword[j]){return false;}
        }
    }
    return true;
}

//Bull- letters in the guess word are in the same index position as the goal word
int bullCheck(std::string myword, std::string guess){
    int count = 0;
    for(int i=0;i<myword.length();i++){
        if(myword[i] == guess[i]){
            count++;
        }
    }
    return count;
}//end of bullCheck


//cow- a letter in the guess word can also be found in the goal word but the letters are not in the same index position
int cowCheck(std::string myword, std::string guess){
    int count = 0;
    for(int i=0;i<=5;i++){
        for(int j=0;j<=5;j++){
            if(i==j){
                break;
            }
            if(myword[i] == guess[j]){
                count++;
            }
        }
    }
    return count;
}//end of cowCheck

//The win condition for this game is that goalword matches the guessword
bool winCheck(std::string goalWord, std::string guess){
    if(goalWord == guess){
        return true;
    }
    return false;
}

bool isValid(std::string goalWord,std::string myword){
    if(myword.length() != goalWord.length() || isogramCheck(myword) == false){
        return false;
    }
    return true;
}//end of isValid
