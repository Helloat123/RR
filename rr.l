%option yylineno
%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rr.h"
#ifdef debug
	#define dpr printf
#else
	#define dpr(...)
#endif
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
SPLUS [+][+]
SMINUS [-][-]
SEMI [;]
LP \(
RP \)
LM \[
RM \]
LB \{
RB \}
LETTER [a-zA-Z_]
DIGIT [0-9]
NUM {DIGIT}+
ID {LETTER}({LETTER}|{DIGIT})*
BLANK [ \n\t]+
ANNO [/][*][^(*/)]*[*][/]
TRUE true
FALSE false
SWITCH switch
CASE case
BREAK break
CONTINUE continue
EXIT exit
ADDR &
PTR #
VOID void

%%
{ANNO} {
	dpr("get annotation : %s\n",yytext);
	}
{TRUE} {
	dpr("get boolean value : %s\n",yytext);
	yylval.var=1;
	return NUM;
}
{FALSE} {
	dpr("get boolean value : %s\n",yytext);
	yylval.var=0;
	return NUM;
}
{ADDR} {
	dpr("get addr sym\n");
	return ADDR;
}
{PTR} {
	dpr("get pointer sym\n");
	return PTR;
}
{SWITCH} {
	dpr("get switch\n");
	return SWITCH;
}
{CASE} {
	dpr("get case\n");
	return CASE;
}
{VOID} {
	dpr("start of function");
	return VOID;
	   }
{INT} {
	dpr("get type : %s\n",yytext);
	return INT;
}
{BOOL} {
	dpr("get type : %s\n",yytext);
	return INT;
}
{CONST} {
	dpr("get type : %s\n",yytext);
	return CONST;
}
{IF} {
	dpr("get keyword : %s\n",yytext);
	return IF;
	}
{ELSE} {
	dpr("get keyword : %s\n",yytext);
	return ELSE;
	}
{WHILE} {
	dpr("get keyword : %s\n",yytext);
	return WHILE;
	}
{DO} {
	dpr("get keyword : %s\n",yytext);
	return DO;
	}
{FOR} {
	dpr("get keyword : %s\n",yytext);
	return FOR;
	}
{REPEAT} {
	dpr("get keyword : %s\n",yytext);
	return REPEAT;
	}
{UNTIL} {
	dpr("get keyword : %s\n",yytext);
	return UNTIL;
	}
{WRITE} {
	dpr("get keyword : %s\n",yytext);
	return WRITE;
	}
{READ} {
	dpr("get keyword : %s\n",yytext);
	return READ;
	}
{PLUS} {
	dpr("get operator : %s\n",yytext);
	return PLUS;
	}
{MINUS} {
	dpr("get operator : %s\n",yytext);
	return MINUS;
	}
{TIMES} {
	dpr("get operator : %s\n",yytext);
	return TIMES;
	}
{COMPLEMENT} {
	dpr("get operator : %s\n",yytext);
	return COMPLEMENT;
	}
{XOR} {
	dpr("get operator : %s\n",yytext);
	return XOR;
	}
{DIVIDES} {
	dpr("get operator : %s\n",yytext);
	return DIVIDES;
	}
{ODD} {
	dpr("get operator : %s\n",yytext);
	return ODD;
	}
{SPLUS} {
	dpr("get operator : %s\n",yytext);
	return SPLUS;
	}
{SMINUS} {
	dpr("get operator : %s\n",yytext);
	return SMINUS;
	}
{RELOP} {
	dpr("get relop : %s\n",yytext);
	yylval.name = strdup(yytext);
	return RELOP;
	}
{ASSIGN} {
	dpr("get assign symbol : %s\n",yytext);
	return ASSIGN;
	}
{OR} {
	dpr("get symbol or: %s\n",yytext);
	return OR;
	}
{AND} {
	dpr("get symbol and: %s\n",yytext);
	return AND;
	}
{NOT} {
	dpr("get symbol : %s\n",yytext);
	return NOT;
	}
{SEMI} {
	dpr("get symbol : %s\n",yytext);
	return SEMI;
	}
{LP} {
	dpr("get bracket : %s\n",yytext);
	return LP;
	}
{RP} {
	dpr("get bracket : %s\n",yytext);
	return RP;
	}
{LM} {
	dpr("get bracket : %s\n",yytext);
	return LM;
	}
{RM} {
	dpr("get bracket : %s\n",yytext);
	return RM;
	 }
{LB} {
	dpr("get bracket : %s\n",yytext);
	return LB;
	}
{RB} {
	dpr("get bracket : %s\n",yytext);
	return RB;
	}
{NUM} {
	dpr("get number : %s\n",yytext);
	int temp;
	sscanf(yytext,"%d",&temp);
	yylval.var = temp;
	return NUM;
	}
{ID} {
	yylval.name=strdup(yytext);
	dpr("get identifier : %s\n",yytext);
	return ID;
	}
{BLANK} {
	
	}
%%
int yywrap()
{
	return 1;
}
