#include "Parser.h"

int index = 0;           // index for where we are in aLex  (someLexics)

_Bool parser(struct lexics *someLexics, int numberOfLexics){
    if(function(someLexics, numberOfLexics) == 1)
        return TRUE;
    else return FALSE;
}

int function(struct lexics *someLexics, int numberOfLexics){
    if(header(someLexics, numberOfLexics) == 1 && body(someLexics, numberOfLexics) == 1)
        return 1;
    else return 0;
}

int header(struct lexics *someLexics, int numberOfLexics){
    if(someLexics[index].token == VARTYPE){
        index++;
        if(someLexics[index].token == IDENTIFIER){
            index++;
            if(someLexics[index].token == LEFT_PARENTHESIS){
                index++;
                if(argDecl(someLexics, numberOfLexics) == 1){
                    if(someLexics[index].token == RIGHT_PARENTHESIS){
                        index++;
                        return 1;
                    }
                    else return 0;
                }
                else return 0;
            }
            else return 0;
        }
        else return 0;
    }
    else return 0;
}

int argDecl(struct lexics *someLexics, int numberOfLexics){
    // should take care of arg-decl being optional in header function
    if(someLexics[index].token == RIGHT_PARENTHESIS){
        return 1;
    }
    // handling first two necessary tokens of arg decl
    else if(someLexics[index].token == VARTYPE) {
        index++;
        if(someLexics[index].token == IDENTIFIER){
            index++;
            if(someLexics[index].token == COMMA){
                argDecl(someLexics, numberOfLexics);
            }
            else return 1;  // since it's optional
        }
        else return 0;
    }
    // handling optional COMMA VARTYPE IDENTIFIER repetitions
    else if(someLexics[index].token == COMMA){
        index++;
        if(someLexics[index].token == VARTYPE){
            index++;
            if(someLexics[index].token == IDENTIFIER){
                index++;
                if(someLexics[index].token == COMMA){
                    argDecl(someLexics, numberOfLexics);
                }
                else return 1; // since it's optional
            }
            else return 0;
        }
        else return 0;
    }
    else return 0;
}

int body(struct lexics *someLexics, int numberOfLexics){
    if(someLexics[index].token == LEFT_BRACKET){
        index++;
        // statement-list is optional
        if(statementList(someLexics, numberOfLexics) == 1){
            if(someLexics[index].token == RIGHT_BRACKET) {
                index++;
                return 1;
            }
            else return 0;
        }
        else return 0;
    }
    else return 0;
}

int statementList(struct lexics *someLexics, int numberOfLexics){
    // should take care of statement-list being optional in body function
    if(someLexics[index].token == RIGHT_BRACKET)
        return 1;           // since it's optional
    // handling first necessary statement
    else if(statement(someLexics, numberOfLexics) == 1){
        // should handle repeating statements
        if(someLexics[index].token == WHILE_KEYWORD || someLexics[index].token == RETURN_KEYWORD ||
        someLexics[index].token == IDENTIFIER || someLexics[index].token == LEFT_BRACKET)
            statementList(someLexics, numberOfLexics);
        else return 1;      // since it's optional
    }
    else return 0;
}

int statement(struct lexics *someLexics, int numberOfLexics){
    if(whileLoop(someLexics, numberOfLexics) == 1 || returnFunc(someLexics, numberOfLexics) == 1 ||
    assignment(someLexics, numberOfLexics) == 1 || body(someLexics, numberOfLexics) == 1) {
        return 1;
    }
    else return 0;
}

int whileLoop(struct lexics *someLexics, int numberOfLexics){
    if(someLexics[index].token == WHILE_KEYWORD){
        index++;
        if(someLexics[index].token == LEFT_PARENTHESIS){
            index++;
            if(expression(someLexics, numberOfLexics) == 1){
                if(someLexics[index].token == RIGHT_PARENTHESIS){
                    index++;
                    if(statement(someLexics, numberOfLexics) == 1){
                        return 1;
                    }
                    else return 0;
                }
                else return 0;
            }
            else return 0;
        }
        else return 0;
    }
    else return 0;
}

int returnFunc(struct lexics *someLexics, int numberOfLexics){
    if(someLexics[index].token == RETURN_KEYWORD) {
        index++;
        if(expression(someLexics, numberOfLexics) == 1) {
            if(someLexics[index].token == EOL){
                return 1;
            }
            else return 0;
        }
        else return 0;
    }
    else return 0;
}

int assignment(struct lexics *someLexics, int numberOfLexics){
    if(someLexics[index].token == IDENTIFIER) {
        index++;
        if(someLexics[index].token == EQUAL) {
            index++;
            if(expression(someLexics, numberOfLexics) == 1) {
                if(someLexics[index].token == EOL) {
                    return 1;
                }
                else return 0;
            }
            else return 0;
        }
        else return 0;
    }
    else return 0;
}

int expression(struct lexics *someLexics, int numberOfLexics){
    // handling optional term start
    if(term(someLexics, numberOfLexics) == 1){
        if(someLexics[index].token == BINOP){
            index++;
            if(term(someLexics, numberOfLexics) == 1){
                if(someLexics[index].token == BINOP){
                    expression(someLexics, numberOfLexics);
                }
                else return 1;  // repeating BINOP term isn't necessary
            }
            else return 0;      // term is necessary after BINOP
        }
        else return 1;          // BINOP is optional
    }
    // handling repeating BINOP term sequence
    else if(someLexics[index].token == BINOP){
        if(term(someLexics, numberOfLexics) == 1){
            if(someLexics[index].token == BINOP){
                expression(someLexics, numberOfLexics);
            }
            else return 1;      // repeating BINOP term isn't necessary
        }
        else return 0;          // term is necessary after BINOP
    }
    // handling LEFT_PARENTHESIS expression RIGHT_PARENTHESIS
    else if(someLexics[index].token == LEFT_PARENTHESIS){
        index++;
        if(expression(someLexics, numberOfLexics) == 1){
            if(someLexics[index].token == RIGHT_PARENTHESIS){
                index++;
                return 1;
            }
            else return 0;          // right paren is required after expression
        }
        else return 0;          // expression is required after left paren

    }
    else return 0;
}

int term(struct lexics *someLexics, int numberOfLexics){
    if(someLexics[index].token == IDENTIFIER || someLexics[index].token == NUMBER) {
        index++;
        return 1;
    }
    else return 0;
}

