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
	int nowprocedure=0;
	int tablestart=0;
	int var_cnt=0;
	int level=0;
	int vv=0;
%}
%union
{
	int var;
	char* name;
}
%start program
%token <var> NUM
%token <name> ID RELOP
%token INT CONST IF ELSE WHILE DO FOR REPEAT UNTIL WRITE READ PLUS MINUS TIMES DIVIDES COMPLEMENT ODD XOR SPLUS SMINUS ASSIGN OR AND NOT SEMI LP RP LB RB LETTER DIGIT BLANK ANNO SWITCH CASE BREAK CONTINUE EXIT ADDR PTR VOID LM RM
%%
	program:defs
	{
		id="__main__";
		enter(procedure,void_t);
		gen(jmp,0,0);
		vv=var_cnt;
	}functions{
		int t=position("__main__");
		code[table[t].addr].a=code_cnt;
		var_cnt=vv;
	}block{
		gen(opr,0,0);
	}
	;
	
	functions:functions function|;

	function:VOID ID LP RP{
		id=$2;
		level++;
		enter(procedure,void_t);
		table[nowprocedure].addr=code_cnt;
		gen(inn,0,3);//DL SL RA
		tablestart=table_cnt;
		var_cnt=3;
	}block{
		level--;
		table_cnt=tablestart;
		var_cnt=0;
		gen(opr,0,0);
	}
	;

	defs: defs def|;

	def:
	INT ID LM NUM RM SEMI{
		id=$2;
		var_cnt++;
		enter(variable,ptr_t);
		int t=position($2);
		gen(gta,level-table[t].level,getaddr(t)+1);
		gen(inn,0,$4);
		var_cnt+=$4;
	}|
	INT ID LM ID RM SEMI{
		id=$2;
		var_cnt++;
		enter(variable,ptr_t);
		int t=position($2);
		gen(gta,level-table[t].level,getaddr(t)+1);
		t=position($4);
		if (t<0) yyerror("no such constant");
		else if (table[t].kind!=constant) yyerror("it is not a constant");
		gen(inn,0,getv(t));
		var_cnt+=getv(t);
	}|
	INT ID SEMI{
		id=$2;
		var_cnt++;
		enter(variable,int_t); //into id table
		gen(inn,0,1);
	}| 
	INT ID ASSIGN bexpr SEMI{
		id=$2;
		var_cnt++;
		enter(variable,int_t);
	}|
	INT PTR ID SEMI{
		id=$3;
		var_cnt++;
		enter(variable,ptr_t);
		gen(inn,0,1);
	}|
	CONST INT ID ASSIGN NUM SEMI{
		id=$3;
		temp_num=$5;
		enter(constant,int_t);
	}|
	error SEMI
	;

	block: LB stmts RB
	;

	stmts: stmts stmt|/*%empty*/
	;

	stmt: 
	ID LP RP SEMI{
		int t=position($1);
		if (t>0)
		{
			if (table[t].kind!=procedure) yyerror("this is not a procedure");
			gen(cal,level^1,table[t].addr);
		}
		else yyerror("no such procedure");
	}|
	INT ID LM NUM RM SEMI{
		id=$2;
		var_cnt++;
		enter(variable,ptr_t);
		int t=position($2);
		gen(gta,level-table[t].level,getaddr(t)+1);
		gen(inn,0,$4);
		var_cnt+=$4;
	}|
	INT ID LM ID RM SEMI{
		id=$2;
		var_cnt++;
		enter(variable,ptr_t);
		int t=position($2);
		gen(gta,level-table[t].level,getaddr(t)+1);
		t=position($4);
		if (t<0) yyerror("no such constant");
		else if (table[t].kind!=constant) yyerror("it is not a constant");
		gen(inn,0,getv(t));
		var_cnt+=getv(t);
	}|
	INT ID SEMI{
		id=$2;
		var_cnt++;
		enter(variable,int_t); //into id table
		gen(inn,0,1);
	}| 
	INT ID ASSIGN bexpr SEMI{
		id=$2;
		var_cnt++;
		enter(variable,int_t);
	}|
	INT PTR ID SEMI{
		id=$3;
		var_cnt++;
		enter(variable,ptr_t);
		gen(inn,0,1);
	}|
	CONST INT ID ASSIGN NUM SEMI{
		id=$3;
		temp_num=$5;
		enter(constant,int_t);
	}|
	ID ASSIGN bexpr SEMI{
		//<id> = <expr>
		int t=position($1);
		if (t>0){
			if (table[t].kind!=variable)
			{
				strcpy (error_info,"");
				sprintf(error_info,"The identifier %s must be a variable!",$1);
				yyerror(error_info);
			}
			gen(sto,level-table[t].level,getaddr(t));
		}
		else{
			strcpy(error_info,"");
			sprintf(error_info,"The variable %s does not exist!",$1);
			yyerror(error_info);
		}
	}|
	PTR ID{
		int t=position($2);
		if (t>0)
		{
			gen(lod,level-table[t].level,getaddr(t));
		}
		else
		{
			strcpy(error_info,"");
			sprintf(error_info,"The variable %s does not exist!",$2);
			yyerror(error_info);
		}
	}ASSIGN bexpr{
		gen(sto1,0,0);
	}|
	ID LM bexpr RM ASSIGN{
		int t=position($1);
		if (t>0){
			gen(lod,level-table[t].level,getaddr(t));
			gen(opr,0,2);
		}
		else{
			strcpy(error_info,"");
			sprintf(error_info,"The variable %s does not exist!",$1);
			yyerror(error_info);
		}
	}bexpr SEMI{
		gen(sto1,0,0);
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
	}|
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
	WRITE bexpr SEMI{
		//write <expr>
		gen(wri,0,0);
	}|
	READ ID SEMI{
		//read x
		int t=position($2);
		if (t>0) gen(red,level-table[t].level,getaddr(t));
		else yyerror("The variable does not exists!");
	}|
	READ ID LM bexpr RM SEMI{
		int t=position($2);
		if (t>0)
		{
			gen(lod,level-table[t].level,getaddr(t));
			gen(opr,0,2);
			gen(red1,0,0);
		}
		else yyerror("The array does not exists!");
	}|
	ID SPLUS SEMI{
		//x++
		int t=position($1);
		if (t>0) 
		{
			if (table[t].kind==variable) gen(lod,level-table[t].level,getaddr(t));
			else yyerror("It is not a variable");
		}
		else yyerror("The variable does not exists!"); 		
		gen(lit,0,1);
		gen(opr,0,2);
		gen(sto,level-table[t].level,getaddr(t));
	}|
	ID SMINUS SEMI{
		//x--
		int t=position($1);
		if (t>0) 
		{
			if (table[t].kind==variable) gen(lod,level-table[t].level,getaddr(t));
			else yyerror("It is not a variable");
		}
		gen(lit,0,1);
		gen(opr,0,3);
		gen(sto,level-table[t].level,getaddr(t));
	}|
	EXIT{
		//exit
		gen(opr,0,18);
	}|
	block|SEMI|error SEMI
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

		
		
	expr: expr PLUS term{
		gen(opr,0,2);
	}|
	expr MINUS term{
		gen(opr,0,3);
	}|
	expr XOR term{
		gen(opr,0,15);
	}|
	term|
	ID ASSIGN expr{
		yyerror("assign symbol do not have return value in CXR!");
	}
	;

	term: term TIMES factor{
		gen(opr,0,4);
	}|
	term DIVIDES factor{
		gen(opr,0,5);
	}|
	term COMPLEMENT factor{
		gen(opr,0,14);
	}|
	factor
	;

	factor: ID{
		int t=position($1);
		if (t>0) 
		{
			//if (table[t].type==bool_t) yyerror("type error");
			//else 
			if (table[t].kind==variable) gen(lod,level-table[t].level,getaddr(t));
			else if (table[t].kind==constant) gen(lit,table[t].level,getv(t));
			else yyerror("unknown error in afactor");
		}
		else yyerror("this identifier don't exists."); 		
	}|
	NUM{
		gen(lit,0,$1);
	}|
	LP bexpr RP{
		//$$=$2;
	}|
	PTR ID{
		int t=position($2);
		gen(lod,level-table[t].level,getaddr(t));
		gen(lod1,0,0);
	}|
	ADDR ID{
		int t=position($2);
		gen(gta,level-table[t].level,getaddr(t));
	}|
	ID LM bexpr RM{
		int t=position($1);
		gen(lod,level-table[t].level,getaddr(t));
		gen(opr,0,2);
		gen(lod1,0,0);
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

	bfactor: 
	NOT bfactor{
		gen(opr,0,1);
	}|
	ODD factor{
		gen(opr,0,6); 	
	}|
	rel
	;

	rel: expr RELOP expr{
		if (strcmp($2,"<")==0) gen(opr,0,10);
		else if (strcmp($2,"<=")==0) gen(opr,0,13);
		else if (strcmp($2,">")==0) gen(opr,0,12);
		else if (strcmp($2,">=")==0) gen(opr,0,11);
		else if (strcmp($2,"==")==0) gen(opr,0,8);
		else if (strcmp($2,"!=")==0) gen(opr,0,9);
		else yyerror("wrong relop type\n");	
	}|
	expr
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
