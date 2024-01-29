%{
#include<stdio.h>
#include"tokens.hpp"
%}
%x FIRST_STRING
%x IN_STRING
%x BACKSLASH
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
stringDelim \"
stringContents [^\\\"]*
%%
0 return(NUM);
{stringDelim} BEGIN(FIRST_STRING);
<FIRST_STRING>{
  {stringDelim} printf("\n");BEGIN(INITIAL); 
  \\ BEGIN(BACKSLASH);
 {stringContents} return(STRING);
}
<BACKSLASH>{
  \\ printf("\\"); BEGIN(IN_STRING);
  \" printf("\"");BEGIN(IN_STRING);
  t printf("\t");BEGIN(IN_STRING);
  n printf("\n");BEGIN(IN_STRING);
  r printf("\r");BEGIN(IN_STRING);
  . return(ERR);
}
<IN_STRING>{
  {stringDelim} printf("\n");BEGIN(INITIAL);
  \\ BEGIN(BACKSLASH);
  {stringContents} printf("%s",yytext);
}
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
{whitespace} return(WS) ;
.   return(ERR);
%%
