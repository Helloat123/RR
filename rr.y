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
	IF LP bexpr RP {
		//if (<bexpr>) <stmt>
		jmpadd[ja_cnt++]=code_cnt;
		gen(jpc,0,0);
	}stmt {
		jmpadd[ja_cnt++]=code_cnt;
		gen(jmp,0,0);
	}elses SEMI|
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
		//need to rewrite
		//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		//for (<stmt>;<bexpr>;<stmt>) <stmt>;
		/*
		int t = position($3);
		if(t > 0){
			if(table[t].kind != variable)
				yyerror("this identifier should be a variable!");
			else if(table[t].type == 1){
				if(!(judgeeq(1,$5)||judgeeq(0,$5))) {
					yyerror("this bool variable cannot be assigned by number excepts 1 and 0");
				}
				else gen(sto,0,getaddr(t),bool_t);
			}
			else gen(sto,0,getaddr(t),gettype(t));
		}
		else yyerror("this variable don't exists.");
		jmpadd[ja_cnt] = cx;
		ja_cnt+=1;
		*/
	}bexpr SEMI{
		/*
		gen(jpc,0,0,int_t);//不满足跳到stmt后结束循环
		gen(jmp,0,0,int_t);//否则执行stmt
		jmpadd[ja_cnt] = cx;//注意gen和cx[cxcount]语句的先后，此时存储的是jmp后的那一条语句的位置。
		ja_cnt+=1; 
	}selfop {
		gen(jmp,0,jmpadd[ja_cnt-2],int_t);//跳到第二个表达式前
		jmpadd[ja_cnt] = cx;
		ja_cnt+=1;
		code[jmpadd[ja_cnt-2]-1].a = cx;
		*/
	}stmt{

	}RP stmt{
		/*
		int temp;
		//跳到第二个表达式后
		gen(jmp,0,jmpadd[ja_cnt-2],int_t);
		code[jmpadd[ja_cnt-2]-2].a = cx;
		ja_cnt -= 3;
		*/
	}|
	DO {
		//do <stmt> while (<bexpr>)
		jmpadd[ja_cnt++]=code_cnt;
	}LB stmts RB WHILE LP bexpr RP {
		gen(jpc,0,jmpadd[--ja_cnt]);
	}SEMI|
	REPEAT {
		//repeat <stmt> until (<bexpr>)
		jmpadd[ja_cnt++]=code_cnt;
	}LB stmts RB UNTIL LP bexpr RP { 	
		gen(opr,0,1);
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
	
	elses:ELSE{
		//else <stmt>
		code[jmpadd[ja_cnt-2]].a=code_cnt;
	}stmt{
		code[jmpadd[ja_cnt-1]].a=code_cnt;
		ja_cnt-=2;
	}|
	/*%empty*/{
		//no else
		ja_cnt-=1;
		code[jmpadd[ja_cnt]].a=code_cnt;
		ja_cnt-=1;
		code[jmpadd[ja_cnt]].a=code_cnt;
	}
	;

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
