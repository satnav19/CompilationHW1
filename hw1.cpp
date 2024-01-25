#include "tokens.hpp"
#include <stdio.h>
void printer(int token){
  switch (token) {
    case ERR:printf("ERR %s\n",yytext);break;
    case WS: return;
    case VOID: printf("%d VOID %s\n", yylineno, yytext);break;
    case INT: printf("%d INT %s\n", yylineno, yytext);break;
    case BYTE: printf("%d BYTE %s\n", yylineno, yytext);break;
    case B: printf("%d B %s\n", yylineno, yytext);break;
    case BOOL: printf("%d BOOL %s\n", yylineno, yytext);break;
    case AND: printf("%d AND %s\n", yylineno, yytext);break;
    case OR: printf("%d OR %s\n", yylineno, yytext);break;
    case NOT: printf("%d NOT %s\n", yylineno, yytext);break;
    case TRUE: printf("%d TRUE %s\n", yylineno, yytext);break;
    case FALSE: printf("%d FALSE %s\n", yylineno, yytext);break;
    case RETURN: printf("%d RETURN %s\n", yylineno, yytext);break;
    case IF: printf("%d IF %s\n", yylineno, yytext);break;
    case ELSE: printf("%d ELSE %s\n", yylineno, yytext);break;
    case WHILE: printf("%d WHILE %s\n", yylineno, yytext);break;
    case BREAK: printf("%d BREAK %s\n", yylineno, yytext);break;
    case CONTINUE: printf("%d CONTINUE %s\n", yylineno, yytext);break;
    case SC: printf("%d SC %s\n", yylineno, yytext);break;
    case LPAREN: printf("%d LPAREN %s\n", yylineno, yytext);break;
    case RPAREN: printf("%d RPAREN %s\n", yylineno, yytext);break;
    case LBRACE: printf("%d LBRACE %s\n", yylineno, yytext);break;
    case RBRACE: printf("%d RBRACE %s\n", yylineno, yytext);break;
    case ASSIGN: printf("%d ASSIGN %s\n", yylineno, yytext);break;
    case RELOP: printf("%d RELOP %s\n", yylineno, yytext);break;
    case BINOP: printf("%d BINOP %s\n", yylineno, yytext);break;
    case COMMENT: printf("%d COMMENT %s\n", yylineno, yytext);break;
    case ID: printf("%d ID %s\n", yylineno, yytext);break;
    case NUM: printf("%d NUM %s\n", yylineno, yytext);break;
    case STRING: printf("%d STRING %s\n", yylineno, yytext);break;
    default: printf("%d WTF %s\n", yylineno, yytext);break;
  }

}
int main()
{
	int token;
	while (token=yylex()){
  printer(token);
  }	
  return 0;
}

