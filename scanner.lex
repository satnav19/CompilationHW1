%{
#include<stdio.h>
#include"tokens.hpp"
%}

%option yylineno
%option noyywrap
badNum [-][0-9]+ 
comment "//".*
illegalFloat [0-9]+"."[0-9]+
number [1-9][0-9]*
letter [a-zA-Z]
whitespace [\t\n\r ]
semiColon ";"
leftP "("
rightP ")"
leftBrace "{"
rightBrace "}"
assign "="
relative "=="|"!="|"<"|">"|"<="|">="
binaryOp "+"|"-"|"*"|"/"
id [a-zA-Z][a-zA-Z0-9]*
string (\".*\")

%%
0 return(NUM);
int return(INT);
{badNum} return(ERR);
{illegalFloat} return(ERR);
{relative} return(RELOP);
byte return(BYTE);
{assign} return(ASSIGN);
b return(B);
{comment} return(COMMENT);
{binaryOp} return(BINOP);
bool return(BOOL);
and return(AND);
or return(OR);
not return(NOT);
true return(TRUE);
false return(FALSE);
return return(RETURN);
if return(IF);
else return(ELSE);
while return(WHILE);
break return(BREAK);
continue return(CONTINUE);
void return(VOID);
{semiColon} return(SC);
{leftP} return(LPAREN);
{rightP} return(RPAREN);
{leftBrace} return(LBRACE);
{rightBrace} return(RBRACE);
{number}   return(NUM);
{id} return(ID);
{string} return(STRING);
{whitespace} return(WS) ;
.   return(ERR);
%%

