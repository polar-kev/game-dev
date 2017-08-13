//
//  FBullCowGame.cpp
//  BullCowGame
//
//  Created by Kevin Semple on 2017-08-12.
//  Copyright © 2017 ksemp. All rights reserved.
//

//#include <stdio.h>
#include <iostream>
#include "FBullCowGame.h"
#include <map>
#define TMap std::map

using FString = std::string;//Needed for use with Unreal Engine. FString is mutable.
using int32 = int;//Needed for use with Unreal Engine. Allows mult-platform deployment.

FBullCowGame::FBullCowGame(){
    reset();
}

void FBullCowGame::reset(){
    goalWord = "but";
    guessWord = "";
    attempts = 5;
    bWin = false;
}

int32 FBullCowGame::getBulls() const {
    //Bull- letters in the guess word are in the same index position as the goal word
    int32 count = 0;
    for(int32 i=0;i<goalWord.length();i++){
        if(goalWord[i] == guessWord[i]){
            count++;
        }
    }
    return count;
}

int32 FBullCowGame::getCows() const {
    //cow- a letter in the guess word can also be found in the goal word but the letters are not in the same index position
    int32 count = 0;
    for(int32 i=0;i<goalWord.length();i++){
        for(int32 j=0;j<goalWord.length();j++){
            if(i==j && goalWord[i] == guessWord[j]){
                break;
            }
            if(goalWord[i] == guessWord[j]){
                count++;
            }
        }
    }
    return count;
}

void FBullCowGame::setGuess(){
    //Ensures validity of guess and decreases attempts
    FString newWord;
    EWordStatus status = EWordStatus::INVALID_STATUS;
    
    std::cout << "Please guess a word.\n";
    
    do{
        std::getline(std::cin,newWord);
        status = isValid(newWord);
        switch (status) {
            case EWordStatus::WRONG_LENGTH :
                std::cout << "Please enter a " << getGoalWordLength() << " letter word.\n";
                break;
            case EWordStatus::NOT_ISOGRAM :
                std::cout << "Please enter a valid isogram.\n";
                break;
            case EWordStatus::NOT_LOWERCASE :
                std::cout << "Please make sure all the letters are lowercase.\n";
                break;
            case EWordStatus::NUMBERS :
                std::cout << "Please make sure your word had no numbers.\n";
                break;
            default:
                break;
        }
    }while(status != EWordStatus::OK);
    
    guessWord=newWord;
    bWin = (guessWord==goalWord);
    attempts-=1;
}

EWordStatus FBullCowGame::isValid(FString newWord){
    if(!bIsIsogram(newWord)){
        return EWordStatus::NOT_ISOGRAM;
    }
    else if(goalWord.length() != newWord.length()){
        return EWordStatus::WRONG_LENGTH;
    }else if(bHasNumber(newWord)){
        return EWordStatus::NUMBERS;
    }else if(!bIsLowerCase(newWord)){
        return EWordStatus::NOT_LOWERCASE;
    }else{
       return EWordStatus::OK;
    }
}

bool FBullCowGame::bIsIsogram(FString newWord){
    //treat 0 and 1 letter words as isograms
    if(newWord.length()<=1){return true;}
    
    TMap<char,bool> letterSeen;
    for(auto Letter : newWord){
        Letter = tolower(Letter);//only want to work with lowercase letters
        if(letterSeen[Letter] == true){//if the letter is in the map
            return false;//We do not have an isogram
        } else{
            letterSeen[Letter]=true;
        }
    }
    
    /*Old implementation
    //isogram = a word where each letter only appears once
    for(int32 i=0;i<newWord.length();i++){
        for(int32 j=0;j<newWord.length();j++){
            if(i==j){
                break;
            }
            if(newWord[i] == newWord[j]){return false;}
        }
    }
    return true;
     */
    
    return true;//for example in cases where /0 is entered
}

bool FBullCowGame::bIsLowerCase(FString word){
    for(auto letter : word){
        if(!isalpha(letter) || !islower(letter)){
            return false;
        }
    }
    return true;
}

bool FBullCowGame::bHasNumber(FString word){
    for(auto letter : word){
        if(isdigit(letter)){
            return true;
        }
    }
    return false;
}

void FBullCowGame::printGameSummary(){
    if(bWinCheck()){
        std::cout << "YOU WIN!" << std::endl << "The word was " << getGuessWord() << "!" << std::endl << std::endl;
    }else{
        std::cout << "YOU LOSE!\n\n";
    }
}

bool FBullCowGame::bWinCheck() const {return bWin;}

int32 FBullCowGame::getGoalWordLength() const {return (uint32_t)goalWord.length();}//word length is unlikely to be too large for int data type

FString FBullCowGame::getGuessWord() const {return guessWord;}

int32 FBullCowGame::getAttempts() const {return attempts;}
