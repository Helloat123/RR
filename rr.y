%{
	#include <stdio.h>
	#include <string.h>
	#include "genpcode.h"
	int yylex(void);
	FILE *yyin;
	int yyerror(char*);
	extern int yylineno;
	extern char* yytext;
	#define MAXLOOP 128 
	int jmpadd[MAXLOOP];//栈
	int ja_cnt=0;
	char error_info[1024];
	int var_cnt=0;
%}
%union
{
	int var;
	char* name;
}
%start program
%token <var> NUM
%token <name> ID RELOP
%token INT BOOL CONST IF ELSE WHILE DO FOR REPEAT UNTIL WRITE READ PLUS MINUS TIMES DIVIDES COMPLEMENT ODD XOR SPLUS SMINUS ASSIGN OR AND NOT SEMI LP RP LB RB LETTER DIGIT BLANK ANNO TRUE FALSE
%type <var> aterm aexpr afactor bexpr bterm bfactor rel
%left LOWER_THAN_ELSE
%%
	program:{
		gen(jmp,0,1);
	}block{
		gen(opr,0,0);
	}
	;

	block: LB{
	}decls{
		if (var_cnt) gen(inn,0,var_cnt);
		var_cnt=0;
	}stmts RB
	;

	decls: decls decl|/*%empty*/
	;

	decl: INT ID SEMI{
		id=$2;
		var_cnt++;
		enter(variable,int_t); //into id table
	}| 
	BOOL ID SEMI{
		id=$2;
		var_cnt++;
		enter(variable,bool_t);
	}| 
	CONST INT ID ASSIGN NUM SEMI{
		id=$3;
		temp_num=$5;
		enter(constant,int_t);
	}| 
	CONST BOOL ID ASSIGN TRUE SEMI{
		id=$3;
		temp_num=1;
		enter(constant,bool_t);
	}|
	CONST BOOL ID ASSIGN FALSE SEMI{
		id=$3;
		temp_num=0;
		enter(constant,bool_t);
	}
	;

	stmts: stmts stmt|/*%empty*/
	;

	stmt: ID ASSIGN aexpr SEMI{
		//<aid> = <aexpr>
		int t=position($1);
		if (t>0){
			if (table[t].kind!=variable)
			{
				strcpy (error_info,"");
				sprintf(error_info,"The identifier %s must be a variable!",$1);
				yyerror(error_info);
			}
			else if (table[t].type!=int_t) 
			{
				strcpy (error_info,"");
				sprintf(error_info,"The identifier %s and the expression is not the same type!",$1);
				yyerror(error_info);
			}
			gen(sto,0,getaddr(t));
		}
		else{
			strcpy (error_info,"");
			sprintf(error_info,"The variable %s does not exist!",$1);
			yyerror(error_info);
		}
	}|
	ID ASSIGN bexpr SEMI{
		//<bid> = <bexpr>
		int t=position($1);
		if (t>0){
			if(table[t].kind!=variable)
			{
				strcpy (error_info,"");
				sprintf(error_info,"The identifier %s must be a variable!",$1);
				yyerror(error_info);
			}
			else if (table[t].type!=bool_t) 
			{
				strcpy(error_info,"");
				sprintf(error_info,"The identifier %s and the expression is not the same type!",$1);
				yyerror(error_info);
			}
			gen(sto,0,getaddr(t));
		}
		else{
			strcpy(error_info,"");
			sprintf(error_info,"The variable %s does not exist!",$1);
			yyerror(error_info);
		}
	}|
	IF LP bexpr RP {
		//if (<bexpr>) <stmt> else <stmt>
		jmpadd[ja_cnt++]=code_cnt;
		gen(jpc,0,0);
	}stmt{
		jmpadd[ja_cnt++]=code_cnt;
		gen(jmp,0,0);
	}elses|
	WHILE {
		//while (<bexpr>) <stmt>
		jmpadd[ja_cnt++]=code_cnt;
	}LP bexpr RP {
		jmpadd[ja_cnt++]=code_cnt;
		gen(jpc,0,0);
	}stmt{
		gen(jmp,0,jmpadd[ja_cnt-2]);
		code[jmpadd[ja_cnt-1]].a=code_cnt;
		ja_cnt-=2;
	}SEMI|
	FOR LP stmt{
		//for (<stmt><bexpr>;<stmt>) <stmt>;
		jmpadd[ja_cnt++]=code_cnt;//-4, where bexpr begin
	}bexpr SEMI{
		jmpadd[ja_cnt++]=code_cnt;//-3, jpc where bexpr end, to the end of for
		gen(jpc,0,0);
		jmpadd[ja_cnt++]=code_cnt;//-2, jmp where bexpr end, to the stmt of for
		gen(jmp,0,0);
		jmpadd[ja_cnt++]=code_cnt;//-1, where stmt in for begin
	}stmt{
		gen(jmp,0,jmpadd[ja_cnt-4]);
		code[jmpadd[ja_cnt-2]].a=code_cnt;
	}RP stmt{
		gen(jmp,0,jmpadd[ja_cnt-1]);
		code[jmpadd[ja_cnt-3]].a=code_cnt;
		ja_cnt-=4;
	}|
	DO {
		//do <stmt> while (<bexpr>)
		jmpadd[ja_cnt++]=code_cnt;
	}LB stmts RB WHILE LP bexpr RP {
		gen(opr,0,1);
		gen(jpc,0,jmpadd[--ja_cnt]);
	}SEMI|
	REPEAT {
		//repeat <stmt> until (<bexpr>)
		jmpadd[ja_cnt++]=code_cnt;
	}LB stmts RB UNTIL LP bexpr RP { 	
		gen(jpc,0,jmpadd[--ja_cnt]);
	}SEMI|
	WRITE aexpr SEMI{
		//write <aexpr>
		gen(wri,0,0);
	}|
	READ ID SEMI{
		//read x
		int t=position($2);
		if (t>0) gen(red,gettype(t),getaddr(t));
		else yyerror("The variable does not exists!");
	}|
	ID SPLUS SEMI{
		//x++
		int t=position($1);
		if (t>0) 
		{
			if (table[t].kind==variable) gen(lod,0,getaddr(t));
			else yyerror("It is not a variable");
		}
		else yyerror("The variable does not exists!"); 		
		gen(lit,0,1);
		gen(opr,0,2);
		gen(sto,0,getaddr(t));
	}|
	ID SMINUS SEMI{
		//x--
		int t=position($1);
		if (t>0) 
		{
			if (table[t].kind==variable) gen(lod,0,getaddr(t));
			else yyerror("It is not a variable");
		}
		gen(lit,0,1);
		gen(opr,0,3);
		gen(sto,0,getaddr(t));
	}|
	block/*%empty*/
	;

	elses:/*%empty*/{
		code_cnt--;
		ja_cnt--;
		code[jmpadd[--ja_cnt]].a=code_cnt;
	}
	|ELSE{
		code[jmpadd[ja_cnt-2]].a=code_cnt;
	}stmt{
		code[jmpadd[ja_cnt-1]].a=code_cnt;
		ja_cnt-=2;
	}

		
		
	aexpr: aexpr PLUS aterm{
		gen(opr,0,2);
	}|
	aexpr MINUS aterm{
		gen(opr,0,3);
	}|
	aexpr XOR aterm{
		gen(opr,0,15);
	}|
	aterm|
	ID ASSIGN aexpr{
		yyerror("assign symbol do not have return value in CXR!");
	}
	;

	aterm: aterm TIMES afactor{
		gen(opr,0,4);
	}|
	aterm DIVIDES afactor{
		gen(opr,0,5);
	}|
	aterm COMPLEMENT afactor{
		gen(opr,0,14);
	}|
	afactor
	;

	afactor: ID{
		int t=position($1);
		if (t>0) 
		{
			if (table[t].type==bool_t) yyerror("type error");
			else if (table[t].kind==variable) gen(lod,0,getaddr(t));
			else if (table[t].kind==constant) gen(lit,0,getv(t));
			else yyerror("unknown error in afactor");
		}
		else yyerror("this identifier don't exists."); 		
	}|
	NUM{
		gen(lit,0,$1);
	}|
	LP aexpr RP{
		$$=$2;
	}
	;

	bexpr: bexpr OR bterm{
		gen(opr,0,17);
	}|
	bterm|
	ID ASSIGN bexpr{
		yyerror("assign symbol do not have return value in CXR!");
	}
	;

	bterm: bterm AND bfactor{
		gen(opr,0,16);
	}|
	bfactor
	;

	bfactor: ID{
		int t=position($1);
		if (t>0){
			if (table[t].type!=bool_t) yyerror("this variable is not boolean type.");
			else if (table[t].kind==variable) gen(lod,0,getaddr(t));
			else if (table[t].kind==constant) gen(lit,0,getv(t));
			else yyerror("unknown error in bfactor");
		}
		else yyerror("this variable don't exists"); 	
	}|
	TRUE{
		gen(lit,0,1);
	}|
	FALSE{
		gen(lit,0,0);
	}|
	NOT bfactor{
		gen(opr,0,1);
	}|
	ODD afactor{
		gen(opr,0,6); 	
	}|
	LP bexpr RP{
		$$=$2;
	}|
	rel
	;

	rel: ID RELOP aexpr{
		int t=position($1);
		if (t>0) 
		{
			if (table[t].type!=int_t) yyerror("this variable don't have correct type.");		
			if (table[t].kind==variable) gen(lod,0,getaddr(t));
			else if (table[t].kind==constant) gen(lit,0,getv(t));
			else yyerror("unknown error in rel");
		}
		else yyerror("this variable don't exists."); 	
		if (strcmp($2,"<")==0) gen(opr,0,10);
		else if (strcmp($2,"<=")==0) gen(opr,0,13);
		else if (strcmp($2,">")==0) gen(opr,0,12);
		else if (strcmp($2,">=")==0) gen(opr,0,11);
		else if (strcmp($2,"==")==0) gen(opr,0,8);
		else if (strcmp($2,"!=")==0) gen(opr,0,9);
		else yyerror("wrong relop type\n");	
	 }|
	 NUM RELOP aexpr{
		//num,relop,expr
		gen(lit,0,$1);
		if (strcmp($2,"<")==0) gen(opr,0,10);
		else if (strcmp($2,"<=")==0) gen(opr,0,13);
		else if (strcmp($2,">")==0) gen(opr,0,12);
		else if (strcmp($2,">=")==0) gen(opr,0,11);
		else if (strcmp($2,"==")==0) gen(opr,0,8);
		else if (strcmp($2,"!=")==0) gen(opr,0,9);
		else yyerror("wrong relop type\n");
	 }
	 ;
%%
int iferror=0;
int main(int argc, char *argv[])
{
	for (int i=0;i<argc;i++){
		if (strcmp(argv[i],"-f")==0&&argc>i)
			yyin=fopen(argv[++i],"r");
	}
	#ifdef debug
		printf("**********CX Compiler:************\n");
	#endif
	yyparse();
	if (iferror) return 0;
	#ifdef debug
		printf("************pcode:****************\n");
	#endif
	printpcode();
	return 0;
}
int yyerror(char *msg)
{
	printf("Error encountered: %d:  %s at %s\n", yylineno, msg, yytext);
	iferror=1;
	return 1;
}
