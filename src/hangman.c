#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

void showDrawing(int strikes){
    if (strikes == 0){
        printf("               \n");
        printf("               \n");
        printf("               \n");
        printf("               \n");
        printf("               \n");
        printf("               \n");
    }

    if (strikes == 1){
        printf("               \n");
        printf("               \n");
        printf("               \n");
        printf("               \n");
        printf("               \n");
        printf(" __            \n");
    }
    if (strikes == 2){
        printf("               \n");
        printf("  |            \n");
        printf("  |            \n");
        printf("  |            \n");
        printf("  |            \n");
        printf(" _|_           \n");
    }
    if (strikes == 3){
        printf("  __________   \n");
        printf("  |            \n");
        printf("  |            \n");
        printf("  |            \n");
        printf("  |            \n");
        printf(" _|_           \n");
    }
    if (strikes == 4){
        printf("  __________   \n");
        printf("  |        |   \n");
        printf("  |            \n");
        printf("  |            \n");
        printf("  |            \n");
        printf(" _|_           \n");
    }
    if (strikes == 5){
        printf("  __________   \n");
        printf("  |        |   \n");
        printf("  |        O   \n");
        printf("  |            \n");
        printf("  |            \n");
        printf(" _|_           \n");
    }
    if (strikes == 6){
        printf("  __________   \n");
        printf("  |        |   \n");
        printf("  |        O   \n");
        printf("  |        |   \n");
        printf("  |            \n");
        printf(" _|_           \n");
    }
    if (strikes == 7){
        printf("  __________   \n");
        printf("  |        |   \n");
        printf("  |        O   \n");
        printf("  |       -|   \n");
        printf("  |            \n");
        printf(" _|_           \n");
    }
    if (strikes == 8){
        printf("  __________   \n");
        printf("  |        |   \n");
        printf("  |        O   \n");
        printf("  |       -|-  \n");
        printf("  |            \n");
        printf(" _|_           \n");
    }
    if (strikes == 9){
        printf("  __________   \n");
        printf("  |        |   \n");
        printf("  |        O   \n");
        printf("  |       -|-  \n");
        printf("  |       /    \n");
        printf(" _|_           \n");
    }
    if (strikes == 10){
        printf("  __________   \n");
        printf("  |        |   \n");
        printf("  |        O   \n");
        printf("  |       -|-  \n");
        printf("  |       / %c \n", 92);
        printf(" _|_           \n");
        printf("               \n");
        printf("    YOU LOSE   \n");
    }
    printf("\n");
}

char askUserChar(char* used){
    char usr_input;
    char letters[] = "qwertyuiopasdfghjklzxcvbnm"; //these are the valid inputs
    printf("Enter letter: ");
    scanf(" %c", &usr_input);
    if ( (strchr(letters, usr_input) == NULL) || (strchr(used, usr_input) != NULL) ){ //checks for invalid input or a reused input
            printf("Invalid input / character already used\n");
            usr_input = askUserChar(used);
        }
    return usr_input;
}

char askIfFullWord(){
    char usr_input;
    char letters[] = "yn";
    printf("Guess full word? (y/n): ");
    scanf(" %c", &usr_input);
    if (strchr(letters, usr_input) == NULL){ //ensures that the input is either 'y' or 'n'
            usr_input = askIfFullWord();
        }
    return usr_input;
}

int setWin(char *random_word){
    printf("You win\n");
    printf("The correct word was \"%s\"\n\n", random_word);
    return 1;
}

void showUsedLetters(char *used, int usedAvailIndex){
    for (int i = 0; i < usedAvailIndex; i++){ //prints all of the used characters. Stops when it reaches a 0.
        if (i == usedAvailIndex - 1){
            printf("%c",used[i]);
        } else {
            printf("%c,",used[i]);
        }
    }
}

void startGame(){
    char guess_letter; //stores letter guess
    char guess_ans; //stores y/n if user wants to guess word 
    int win_condition = 0; //0 if no win, 1 if win
    char used_letters[30] = {"000000000000000000000000000000"}; //will be popluated with the used characters 
    int usedLettersAvailIndex = 0; //keeps track of the index of the most recently added character to 'used'
    char guess_word[30]; 
    int strikes = 0;
    int correct_letters = 0;
    char word_arr[20][30] = {"spike","deficiency","jerry","honk","buff","waterfall", //word_arr[number of words][word length]
                            "horseshoe", "archive", "reservoir", "paradox", "cutting",
                            "tension", "constellation", "ambiguous", "conference",
                             "mercy", "kindness", "modest", "cactus", "yesterday"};
    int random_index = rand() % 20; //random number in range 0 - 19
    char* random_word = word_arr[random_index];
    char blanks[] = {"          "};
    for (int i = 0; i < strlen(random_word); i++){ //populates the blanks array
        blanks[i] = '*';
    }
    
    while (win_condition == 0){
        printf("Strikes: %d\n", strikes);        
        printf("Word to guess: %s\n", blanks);
        printf("Used letters: ");
        showUsedLetters(used_letters, usedLettersAvailIndex);
        printf("\n");
        guess_ans = askIfFullWord();
        if (guess_ans == 'n'){
            guess_letter = askUserChar(used_letters); //used is passed in so characters arent input twice
            if (strchr(random_word, guess_letter) != NULL){ //checks if the letter is in the word
                for (int i = 0; i < strlen(blanks); i++){
                    if (guess_letter == random_word[i]){ //reflects change in the blanks array
                        blanks[i] = guess_letter;
                        correct_letters++;
                    }
                }
            } else {
                strikes++;
            }
            used_letters[usedLettersAvailIndex] = guess_letter; //adds guess to used array
            usedLettersAvailIndex++;
        } else {
            printf("Enter word guess: ");
            scanf(" %s", guess_word);
            if (strcmp(guess_word, random_word) == 0){ //checks if the word is correct
                win_condition = setWin(random_word);
                printf("\n");
            } else {
                strikes++;
            }   
        }
        if (strikes == 10){
            win_condition = 1;
            printf("The correct word was \"%s\"\n\n", random_word);
        }
        if (correct_letters == strlen(random_word)){
            win_condition = setWin(random_word);
        }
        showDrawing(strikes);
    }
}

int main() {
    srand(time(0));
    startGame();
    return 0;
}
