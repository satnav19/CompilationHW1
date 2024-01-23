%{
#include<stdio.h>
void showToken(const char*);
%}

%option yylineno
%option noyywrap
digit [0-9]
letter [a-zA-Z]
whitespace [\t\n ]

%%
{digit}+   showToken("NUM");
{letter}+ showToken("WORD");
{whitespace} ;
.   showToken("unknown");
%%

void showToken(const char* name){
  printf("%d ", yylineno);
  printf("%s ", name);
  printf("%s \n", yytext);
  //printf("the length is %d \n", yyleng);
}
