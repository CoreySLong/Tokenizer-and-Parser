#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <string.h>
#include "Givens.h"
#include "Analyzer.h"

_Bool parser(struct lexics *someLexics, int numberOfLexics);
int function(struct lexics *someLexics, int numberOfLexics);
int header(struct lexics *someLexics, int numberOfLexics);
int argDecl(struct lexics *someLexics, int numberOfLexics);
int body(struct lexics *someLexics, int numberOfLexics);
int statementList(struct lexics *someLexics, int numberOfLexics);
int statement(struct lexics *someLexics, int numberOfLexics);
int whileLoop(struct lexics *someLexics, int numberOfLexics);
int returnFunc(struct lexics *someLexics, int numberOfLexics);
int assignment(struct lexics *someLexics, int numberOfLexics);
int expression(struct lexics *someLexics, int numberOfLexics);
int term(struct lexics *someLexics, int numberOfLexics);

#endif