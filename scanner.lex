%{
#include"tokens.hpp"
%}
%option yylineno
%option noyywrap
binop (\+|-|\*|\/)
comment \/\/[^\r\n]* 
digit ([0-9])
num (0|[1-9]{digit}*)	
positiveNum [1-9]digit*
letter ([a-zA-Z])
whitespace ([\t\n\r ])
escape (\\[ntr\"\\0])
ASCII [!#-\[\]-~\x09\x20]
hexASCII (\\x[0-7][0-9a-fA-F])
string ({ASCII}|{escape}|{hexASCII})
badEscape (\\[^ntr\"\\0])
badChar ([\x00-\x09\x0b\x0c\x0e-\x1f]|\x7f)
badString ({string}|{badEscape}|{badChar})
unclosed \"[^\"]* 
relop (==|!=|<|>|<=|>=)
id {letter}+({letter}|{digit})*
%%
{whitespace}				    ;
void  return VOID;
int  return INT;
byte return BYTE;
b return B;
bool return BOOL;
and return AND;
or  return OR;
not return NOT;
true return TRUE;
false return FALSE;
return return RETURN;
if return IF;
else return ELSE;
while return WHILE;
break return BREAK;
continue return CONTINUE;
; return SC;
\( return LPAREN;
\) return RPAREN;
"{" return LBRACE;
"}" return RBRACE;
= return ASSIGN;
{relop} return RELOP;
{binop} return BINOP;
{comment} return COMMENT;
{num} return NUM;
{id}  return ID;
(\"{string}*\") return STRING;
(\"{badString}*\") return BAD_STRING;
{unclosed} return UNCLOSED;
. return ERR;
%%
