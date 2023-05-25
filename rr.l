%option yylineno
%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "y.tab.h"
int lineno=1;	
%}

INT int
BOOL bool
IF if
ELSE else
WHILE while
DO do
FOR for
REPEAT repeat
UNTIL until
WRITE write
READ read
CONST const
PLUS [+]
MINUS [-]
TIMES [*]
COMPLEMENT [%]
DIVIDES [/]
ODD odd
RELOP [<]|[<][=]|[>]|[>][=]|[=][=]|[!][=]
ASSIGN [=]
OR [|][|]
AND [&][&]
XOR [\^]
NOT [!]
COLON [:]
SPLUS [+][+]
SMINUS [-][-]
SEMI [;]
LP \(
RP \)
LB \{
RB \}
LAN [/][*]
RAN [*][/]
LETTER [a-zA-Z]
DIGIT [0-9]
NUM {DIGIT}+
ID {LETTER}({LETTER}|{DIGIT})*
BLANK [ \n\t]+
ANNO [/][*][^(*/)]*[*][/]
TRUE true
FALSE false
%%
{ANNO} {
	printf("get annotation : %s\n",yytext);
	}
{TRUE} {
	printf("get boolean value : %s\n",yytext);
	return TRUE;
	}
{FALSE} {
	printf("get boolean value : %s\n",yytext);
	return FALSE;
	}
{INT} {
	printf("get type : %s\n",yytext);
	return INT;
	}
{BOOL} {
	printf("get type : %s\n",yytext);
	return BOOL;
	}
{CONST} {
	printf("get type : %s\n",yytext);
	return CONST;
	}
{IF} {
	printf("get keyword : %s\n",yytext);
	return IF;
	}
{ELSE} {
	printf("get keyword : %s\n",yytext);
	return ELSE;
	}
{WHILE} {
	printf("get keyword : %s\n",yytext);
	return WHILE;
	}
{DO} {
	printf("get keyword : %s\n",yytext);
	return DO;
	}
{FOR} {
	printf("get keyword : %s\n",yytext);
	return FOR;
	}
{REPEAT} {
	printf("get keyword : %s\n",yytext);
	return REPEAT;
	}
{UNTIL} {
	printf("get keyword : %s\n",yytext);
	return UNTIL;
	}
{WRITE} {
	printf("get keyword : %s\n",yytext);
	return WRITE;
	}
{READ} {
	printf("get keyword : %s\n",yytext);
	return READ;
	}
{PLUS} {
	printf("get operator : %s\n",yytext);
	return PLUS;
	}
{MINUS} {
	printf("get operator : %s\n",yytext);
	return MINUS;
	}
{TIMES} {
	printf("get operator : %s\n",yytext);
	return TIMES;
	}
{COMPLEMENT} {
	printf("get operator : %s\n",yytext);
	return COMPLEMENT;
	}
{XOR} {
	printf("get operator : %s\n",yytext);
	return XOR;
	}
{DIVIDES} {
	printf("get operator : %s\n",yytext);
	return DIVIDES;
	}
{ODD} {
	printf("get operator : %s\n",yytext);
	return ODD;
	}
{SPLUS} {
	printf("get operator : %s\n",yytext);
	return SPLUS;
	}
{SMINUS} {
	printf("get operator : %s\n",yytext);
	return SMINUS;
	}
{RELOP} {
	printf("get relop : %s\n",yytext);
	yylval.name = strdup(yytext);
	return RELOP;
	}
{ASSIGN} {
	printf("get assign symbol : %s\n",yytext);
	return ASSIGN;
	}
{OR} {
	printf("get symbol or: %s\n",yytext);
	return OR;
	}
{AND} {
	printf("get symbol and: %s\n",yytext);
	return AND;
	}
{NOT} {
	printf("get symbol : %s\n",yytext);
	return NOT;
	}
{SEMI} {
	printf("get symbol : %s\n",yytext);
	return SEMI;
	}
{COLON} {
	printf("get symbol : %s\n",yytext);
	return COLON;
	}
{LP} {
	printf("get bracket : %s\n",yytext);
	return LP;
	}
{RP} {
	printf("get bracket : %s\n",yytext);
	return RP;
	}
{LB} {
	printf("get bracket : %s\n",yytext);
	return LB;
	}
{RB} {
	printf("get bracket : %s\n",yytext);
	return RB;
	}
{LAN} {
	printf("get symbol : %s\n",yytext);
	return LAN;
	}
{RAN} {
	printf("get symbol : %s\n",yytext);
	return RAN;
	}
{NUM} {
	printf("get number : %s\n",yytext);
	double temp;
	sscanf(yytext, "%lf", &temp);
	yylval.var = temp;
	return NUM;
	}
{ID} {
	yylval.name = strdup(yytext);
	printf("get identifier : %s\n",yytext);
	return ID;
	}
{BLANK} {
	
	}
%%
int yywrap()
{
	return 1;
}
