#include "Tokenizer.h"

// Reads characters from a given file variable and converts them into tokens
_Bool tokenizer(struct lexics *aLex, int *numLex, FILE *inf){
    int i, index = 0, tempIndex = 0;
    char temp[LEXEME_MAX];
    char input[MY_CHAR_MAX];

    // stores a line of the file in input each iteration
    while(fgets(input, MY_CHAR_MAX, inf) != NULL){                 // input holds a whole line
        // reading input for lexemes
        for(i = 0; i < MY_CHAR_MAX; i++){
            // checks for multiple symbols
            if( (input[i] == '!' && input[i+1] == '=') || (input[i] == '=' && input[i+1] == '=') ){
                if(temp[0] != '\0') {                              // checks if temp has a lexeme forming
                    temp[tempIndex] = '\0';                        // null terminating next index so it's known where string stops
                    strcpy(aLex[index].lexeme, temp);              // copies previously forming lexeme into aLex first
                    index++;
                    temp[0] = '\0';                                // resets temp string
                    (*numLex) += 1;                                // incrementing number of lexemes
                    tempIndex = 0;                                 // resets for temp
                }
                temp[tempIndex] = input[i];                        // puts first new symbol into temp string
                temp[tempIndex + 1] = input[i + 1];                // puts second new symbol into temp string
                temp[tempIndex + 2] = '\0';                        // null terminating next index so it's known where string stops
                strcpy(aLex[index].lexeme, temp);                  // copies new lexeme into aLex
                index++;
                temp[0] = '\0';                                    // resets temp string
                (*numLex) += 1;                                    // incrementing number of lexemes
                tempIndex = 0;                                     // resets for temp
                i++;                                               // need to increment i since input[i + 1] was used
            }
            // checks for singular symbols
            else if(input[i] == '(' || input[i] == ')' || input[i] == '{' || input[i] == '}' ||
            input[i] == ',' || input[i] == ';'|| input[i] == '%'|| input[i] == '+' || input[i] == '*'|| input[i] == '='){
                if(temp[0] != '\0') {                              // checks if temp has a lexeme forming
                    temp[tempIndex] = '\0';                        // null terminating index so it's known where string stops
                    strcpy(aLex[index].lexeme, temp);              // copies previously forming lexeme into aLex first
                    index++;
                    temp[0] = '\0';                                // resets temp string
                    (*numLex) += 1;                                // incrementing number of lexemes
                    tempIndex = 0;
                }
                temp[tempIndex] = input[i];                        // puts new symbol into temp string
                temp[tempIndex + 1] = '\0';                        // null terminating next index so it's known where string stops
                strcpy(aLex[index].lexeme, temp);                  // copies new lexeme into aLex
                index++;
                temp[0] = '\0';                                    // resets temp string
                (*numLex) += 1;                                    // incrementing number of lexemes
                tempIndex = 0;                                     // resets for temp
            }
            // checks for whitespace characters
            else if(input[i] == ' ' || input[i] == '\n' || input[i] == '\t' || input[i] == '\v' || input[i] == '\r' || input[i] == '\f'){
                if(temp[0] != '\0') {                              // checks if temp has a lexeme forming
                    temp[tempIndex] = '\0';                        // null terminating next index so it's known where string stops
                    strcpy(aLex[index].lexeme, temp);
                    index++;
                    temp[0] = '\0';                                // resets temp string
                    (*numLex) += 1;                                // incrementing number of lexemes
                    tempIndex = 0;
                }
            }
            // checks for end of line
            else if(input[i] == '\0') {
                i = MY_CHAR_MAX;
            }
            // builds lexeme with alphanumeric characters
            else{
                temp[tempIndex] = input[i];                        // builds substring as it reads through chars and doesn't see delimiter
                tempIndex++;
            }
        }
    }

    // tokenizing the lexemes
    for(i = 0; i < *numLex; i++){
        if(strcmp(aLex[i].lexeme, "(") == 0)
            aLex[i].token = LEFT_PARENTHESIS;
        else if(strcmp(aLex[i].lexeme, ")") == 0)
            aLex[i].token = RIGHT_PARENTHESIS;
        else if(strcmp(aLex[i].lexeme, "{") == 0)
            aLex[i].token = LEFT_BRACKET;
        else if(strcmp(aLex[i].lexeme, "}") == 0)
            aLex[i].token = RIGHT_BRACKET;
        else if(strcmp(aLex[i].lexeme, "while") == 0)
            aLex[i].token = WHILE_KEYWORD;
        else if(strcmp(aLex[i].lexeme, "return") == 0)
            aLex[i].token = RETURN_KEYWORD;
        else if(strcmp(aLex[i].lexeme, "=") == 0)
            aLex[i].token = EQUAL;
        else if(strcmp(aLex[i].lexeme, ",") == 0)
            aLex[i].token = COMMA;
        else if(strcmp(aLex[i].lexeme, ";") == 0)
            aLex[i].token = EOL;
        else if( (strcmp(aLex[i].lexeme, "int") == 0) || (strcmp(aLex[i].lexeme, "void") == 0) )
            aLex[i].token = VARTYPE;
        else if( (strcmp(aLex[i].lexeme, "+") == 0) || (strcmp(aLex[i].lexeme, "*") == 0) || (strcmp(aLex[i].lexeme, "!=") == 0) ||
        (strcmp(aLex[i].lexeme, "==") == 0) || (strcmp(aLex[i].lexeme, "%") == 0) )
            aLex[i].token = BINOP;
        else if( (validIdentifier(aLex[i].lexeme) == TRUE) || (validIdentifier(aLex[i].lexeme) == 1) )
            aLex[i].token = IDENTIFIER;
        else if( (validNumber(aLex[i].lexeme) == TRUE) || (validNumber(aLex[i].lexeme) == 1) )
            aLex[i].token = NUMBER;
    }
    return TRUE;
}

// whitespace
// symbol  (all of them are in provided lexical structure)
// alphanumeric
// tokenizing is just if else statement and reg exs

// null terminate lexemes bc strings only read till it

