%{
#include<stdio.h>
void showToken(const char*);
%}

%option yylineno
%option noyywrap
badNum [0-][0-9]+ 
illegalFloat [0-9]+"."[0-9]+
digit [0-9]
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
int showToken("INT");
{badNum} showToken("unknown");
{illegalFloat} showToken("unknown");
{relative} showToken("RELOP");
byte showToken("BYTE");
{assign} showToken("ASSIGN");
b showToken("B");
{binaryOp} showToken("BINOP");
bool showToken("BOOL");
and showToken("AND");
or showToken("OR");
not showToken("NOT");
true showToken("TRUE");
false showToken("FALSE");
return showToken("RETURN");
if showToken("IF");
else showToken("ELSE");
while showToken("WHILE");
break showToken("BREAK");
continue showToken("CONTINUE");
void showToken("VOID");
{semiColon} showToken("SC");
{leftP} showToken("LPAREN");
{rightP} showToken("RPAREN");
{leftBrace} showToken("LBRACE");
{rightBrace} showToken("RBRACE");
{digit}+   showToken("NUM");
{id} showToken("ID");
{string} showToken("STRING");
{whitespace} ;
.   showToken("unknown");
%%

void showToken(const char* name){
  printf("%d ", yylineno);
  printf("%s ", name);
  printf("%s \n", yytext);
  //printf("the length is %d \n", yyleng);
}
