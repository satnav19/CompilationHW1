#include "tokens.hpp"
#include <iostream>
using namespace std;
const int maxLength = 1030;
bool notInRange(char current, char lower, char upper) {
	return ((current < lower) || (upper < current));
}

bool printable(char c)
{
	return notInRange(c, char(0x0), char(0x1f)) && int(c) != 0x7f;
}


bool validEsc(char next)
{
	return (next == 'n' 
      || next == 'r' 
      || next == '0' ||
      next == 't' ||
      next == '\\' ||
      next == '\"' ||
      next == 'x');
}
int toInt(char c)
{
	int result = 0;
	if (c >= '0' && c <= '9') {
		result =  (int)(c - '0');
	}
	else if (c >= 'a' && c <= 'f') {
		result = (int)(c - 'a' + 10);
	}
	else if (c >= 'A' && c <= 'F') {
		result =  (int)(c - 'A' + 10);
	}
	return result;
}

void addEscSeq(char* text, int* index, int position)
{
	(*index)++;
	char next_char = yytext[*index];
	switch (next_char)
	{	
		case '\\':
			text[position] = '\\';
			break;
			
		case '"':
			text[position] = '\"';
			break;
			
		case 'n':
			text[position] = '\n';
			break;
			
		case 'r':
			text[position] = '\r';
			break;
			
		case 't':
			text[position] = '\t';
			break;
			
		case '0':
			text[position] = '\0'; 
			break;
			
		case 'x':
			(*index)++;
			int hexadecimal = toInt(yytext[*index]) * 16;
			(*index)++;
			hexadecimal += toInt(yytext[*index]);
			text[position] = (char)hexadecimal;
			break;
	}
}
void printer(const char* token_name, const char* token_value)
{
	cout << yylineno << " " << token_name << " " << token_value << endl;
}


void renderText()
{
	char textArr[maxLength] = {0};
	int current_write_index = 0;

	for(int i = 1; i < yyleng - 1; i++)
	{
		if (yytext[i] == '\\') {
			addEscSeq(textArr, &i, current_write_index);
		}
		else {
			textArr[current_write_index] = yytext[i];
		}
		current_write_index++;
	}

	cout << yylineno << " " << "STRING" << " " << textArr << endl;
}

void stringPolice()
{
	for (int index = 0; index < yyleng ; index++)
	{
		if (!printable(yytext[index])) {
			cout << "Error " << yytext[index] << endl;
			return;
		}

		if (yytext[index] != '\\') {
			continue;
		}

		if (index + 1 == yyleng) {
			cout << "Error unclosed string" << endl;
			return;
		}
		
		char escaped = yytext[index + 1];
		if (!validEsc(escaped)) {
			cout << "Error undefined escape sequence " << escaped << endl;
			return;
		}
		
		if (escaped == 'x')
		{ 
			if (!(index + 2 < yyleng - 1)) {
				cout << "Error undefined escape sequence x" << endl;
				return;
			}

			if (!(index + 3 < yyleng - 1)) {
				cout << "Error undefined escape sequence x" << yytext[index + 2] << endl;
				return;
			}

			if ((notInRange(yytext[index + 2], '0', '7')) ||
				(notInRange(yytext[index + 3], '0', '9') &&
			     notInRange(yytext[index + 3], 'a', 'f') &&
				 notInRange(yytext[index + 3], 'A', 'F'))){
				cout << "Error undefined escape sequence x" <<
        yytext[index + 2] << yytext[index + 3] << endl;
				return;
			}
			index += 2;			
		}
	}
}

void errorHandler(tokentype err)
{
	int index = 0;
	switch (err)
	{
	case UNCLOSED:
		cout << "Error unclosed string" << endl;
		exit(0);
	case ERR:
		
		while (yytext[index])
		{
			if (!printable(yytext[index])) {
				cout << "Error " << yytext[index] << endl;
				exit(0);
			}
			index++;
		}

		cout << "Error " << yytext << endl;
		exit(0);
	case BAD_STRING:
		stringPolice();
		exit(0);
	
  default:
    cout << "BAD " << yytext << endl;
    exit(0);
  }
  }

int main()
{
	int token;
	while ((token = yylex())) 
	{
	  switch (token)
	  {
	  	case VOID:
			printer("VOID", yytext);
			break;
		case INT:
			printer("INT", yytext);
			break;
		case BYTE:
			printer("BYTE", yytext);
			break;
		case B:
			printer("B", yytext);
			break;
		case BOOL:
			printer("BOOL", yytext);
			break;
		case AND:
			printer("AND", yytext);
			break;
		case OR:
			printer("OR", yytext);
			break;
		case NOT:
			printer("NOT", yytext);
			break;
		case TRUE:
			printer("TRUE", yytext);
			break;
		case FALSE:
			printer("FALSE", yytext);
			break;
		case RETURN:
			printer("RETURN", yytext);
			break;
		case IF:
			printer("IF", yytext);
			break;
		case ELSE:
			printer("ELSE", yytext);
			break;
		case WHILE:
			printer("WHILE", yytext);
			break;
		case BREAK:
			printer("BREAK", yytext);
			break;	
		case CONTINUE:
			printer("CONTINUE", yytext);
			break;
		case SC:
			printer("SC", yytext);
			break;
		case LPAREN:
			printer("LPAREN", yytext);
			break;
		case RPAREN:
			printer("RPAREN", yytext);
			break;
		case LBRACE:
			printer("LBRACE", yytext);
			break;
		case RBRACE:
			printer("RBRACE", yytext);
			break;
		case ASSIGN:
			printer("ASSIGN", yytext);
			break;
		case RELOP:
			printer("RELOP", yytext);
			break;
		case BINOP:
			printer("BINOP", yytext);
			break;
		case COMMENT:
			printer("COMMENT", "//");
			break;
		case ID:
			printer("ID", yytext);
			break;
		case NUM:
			printer("NUM", yytext);
			break;
		case STRING:
			renderText();
			break;
		case BAD_STRING:
			errorHandler(BAD_STRING);
			exit(0);
		case UNCLOSED:
			errorHandler(UNCLOSED);
			exit(0);
		case ERR:
			errorHandler(ERR);
			exit(0);
	  }
	}
	return 0;
}
