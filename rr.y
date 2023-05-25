%{
	#include <stdio.h>
	#include <string.h>
	#include "genpcode.h"
	int yylex(void);
	FILE *yyin;
	int yyerror(char*);
	extern int yylineno;
	extern char* yytext;
	#define MAXLOOP 16
	int cx1[MAXLOOP];//if的嵌套栈
	int cx1count = 0;
	int cx2[MAXLOOP];//while的嵌套栈
	int cx2count = 0;
	int cx3[MAXLOOP];//回标for语句中jpc用.每三条语句为一组，组内第一个记录for中第二个表达式之前的位置，第二个记录第二个表达式之后的位置，第三个记录stmt结束位置
	int cx3count = 0;
	int cx4[MAXLOOP];//do while的嵌套栈
	int cx4count = 0;
	int cx5[MAXLOOP];//repeat until的嵌套栈
	int cx5count = 0;
%}
%start program
%token <var> NUM
%token <name> ID RELOP
%token INT BOOL CONST IF ELSE WHILE DO FOR REPEAT UNTIL WRITE READ PLUS MINUS TIMES DIVIDES COMPLEMENT ODD XOR SPLUS SMINUS ASSIGN OR AND NOT SEMI COLON LP RP LB RB LAN RAN LETTER DIGIT BLANK ANNO TRUE FALSE
%type <var> aterm aexpr afactor bexpr bterm bfactor rel
%%
	program: block{
		int temp;
	}
	;

	block: LB decls stmts RB
	;

	decls: decls decl|
	;

	decl: INT ID SEMI{
		id = $2;
		printf("aid\n");
		gen(inn,0,1,int_t);
		enter(variable,int_t); //into id table
	}| 
	BOOL ID SEMI{
		id = $2;
		printf("bid\n");
		gen(inn,0,1,bool_t);
		enter(variable,bool_t);
	}| 
	CONST INT ID{
		id = $3;
		gen(inn,0,1,int_t);
		enter(constant,int_t);
	} ASSIGN aexpr SEMI{
		int t = position($3);
		if (t > 0) gen(sto,0,getaddr(t),gettype(t));
		else yyerror("this variable don't exists.");
	}| 
	CONST BOOL ID {
		id = $3;
		gen(inn,0,1,bool_t);
		enter(constant,bool_t);
	}ASSIGN bexpr SEMI{
		int t = position($3);
		if (t > 0) gen(sto,0,getaddr(t),bool_t);
		else yyerror("this variable don't exists.");
	}| 
	;

	stmts: stmts stmt|
	;

	stmt: ID ASSIGN aexpr SEMI{
		//<aid> = <aexpr>
		int t = position($1);
		if(t > 0){
			if(table[t].kind != variable)
				yyerror("this identifier should be a variable!");
			else if(table[t].type == 1){
				if(!(judgeeq(1,$3)||judgeeq(0,$3))) {
					yyerror("this bool variable cannot be assigned by number excepts 1 and 0");
				}
				else gen(sto,0,getaddr(t),bool_t);
			}
			else gen(sto,0,getaddr(t),gettype(t));
		}
		else yyerror("this variable don't exists.");
	}|
	ID ASSIGN bexpr SEMI{
		//<bid> = <bexpr>
		int t = position($1);
		if(t > 0){
			if(table[t].kind != variable) yyerror("this identifier should be a variable!");
			else if(table[t].type != 1) yyerror("this variable is not boolean type.");
			else gen(sto,0,getaddr(t),bool_t);
		}
		else yyerror("this variable don't exists.");	
	}|
	IF LP bexpr RP {
		//if (<bexpr>) <stmt>
		printf("process if\n");
		cx1[cx1count] = cx;
		cx1count+=1;
		gen(jpc,0,0,int_t);
	}stmt {
		cx1[cx1count] = cx;
		cx1count+=1;
		gen(jmp,0,0,int_t);
	}elses SEMI|
	WHILE {
		//while (<bexpr>) <stmt>
		printf("process while\n");
		cx2[cx2count] = cx;
		cx2count+=1;
	}LP bexpr RP {
		cx2[cx2count] = cx;
		cx2count+=1;
		gen(jpc,0,0,int_t);
	}stmt{
		int temp;
		gen(jmp,0,cx2[cx2count-2],int_t);
		code[cx2[cx2count-1]].a = cx;
		cx2count -= 2;
	}SEMI|
	FOR LP ID ASSIGN aexpr SEMI{
		//need to rewrite
		//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		//for (<stmt>;<bexpr>;<stmt>) <stmt>;
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
		cx3[cx3count] = cx;
		cx3count+=1;
	}rel SEMI {
		gen(jpc,0,0,int_t);//不满足跳到stmt后结束循环
		gen(jmp,0,0,int_t);//否则执行stmt
		cx3[cx3count] = cx;//注意gen和cx[cxcount]语句的先后，此时存储的是jmp后的那一条语句的位置。
		cx3count+=1; 
	}selfop {
		gen(jmp,0,cx3[cx3count-2],int_t);//跳到第二个表达式前
		cx3[cx3count] = cx;
		cx3count+=1;
		code[cx3[cx3count-2]-1].a = cx;
	}RP stmt{
		int temp;
		//跳到第二个表达式后
		gen(jmp,0,cx3[cx3count-2],int_t);
		code[cx3[cx3count-2]-2].a = cx;
		cx3count -= 3;
	}|
	DO {
		//do <stmt> while (<bexpr>)
		cx61[cx61count] = cx;
		cx61count += 1;
		cx4[cx4count] = cx;
		cx4count += 1;
	}stmt
	WHILE LP bexpr RP { 	
		gen(jpc2,0,code[cx4[cx4count-1]].a,int_t);
		cx4count -= 1;
		int temp;
	}SEMI|
	REPEAT {
		//repeat <stmt> until (<bexpr>)
		cx61[cx61count] = cx;//?
		cx61count += 1;//???????????????????????????????
		cx5[cx5count] = cx;
		cx5count += 1;
	}stmt
	UNTIL LP bexpr RP { 	
		gen(jpc,0,code[cx5[cx5count-1]].a,int_t);
		cx5count -= 1;
		int temp;
	}SEMI|
	WRITE aexpr SEMI{
		//write <aexpr>
	}|
	READ ID SEMI{
		//read x
		int t = position($2);
		if(t > 0) gen(red, 0, getaddr(t), gettype(t));
		else yyerror("this variable don't exists.");
	}|
	ID SPLUS SEMI{
		//x++
		int t = position($1);
		if(t > 0){
			gen(lod,0,getaddr(t),gettype(t));
		}
		else{
			yyerror("this variable don't exists."); 		
		}
		genplus(lit,0,1,int_t,1);
		gen(opr,0,2,int_t);
		gen(sto,0,getaddr(t),bool_t);
	}|
	ID SMINUS SEMI{
		//x--
		int t = position($1);
		if(t > 0){
			gen(lod,0,getaddr(t),gettype(t));
		}
		else{
			yyerror("this variable don't exists."); 		
		}
		genplus(lit,0,1,int_t,1);
		gen(opr,0,3,int_t);
		gen(sto,0,getaddr(t),bool_t);
	}
	block|
	;
	
	elses:ELSE{
		//else <stmt>
		printf("else statement\n");
		code[cx1[cx1count-2]].a = cx;
	} stmt{
		code[cx1[cx1count-1]].a = cx;
		cx1count -= 2;
	}|{
		//no else
		cx1count-=1;
		code[cx1[cx1count]].a = cx;
		cx1count-=1;
		code[cx1[cx1count]].a = cx;
		//printf("code:%d,%d\n",code[cx1[cx1count]].f,cx);
	}
	;

	aexpr: aterm PLUS aterm{
		gen(opr,0,2,int_t);
	}|
	aexpr MINUS aterm{
		gen(opr,0,3,int_t);
	}|
	aexpr XOR aterm{
		gen(opr,0,17,int_t);
	}|
	aterm|
	ID ASSIGN aexpr{
		yyerror("assign symbol do not have return value in CXR!");
	}
	;

	aterm: afactor TIMES afactor{
		gen(opr,0,4,int_t);
	}|
	afactor DIVIDES afactor{
		gen(opr,0,5,int_t);
	}|
	afactor COMPLEMENT afactor{
		gen(opr,0,16,int_t);
	}|
	afactor|
	aterm PLUS aterm{
		yyerror("CXR do not support A+B+C but A+(B+C). Add parentheses!"); 		
	}|
	aterm MINUS aterm{
		yyerror("CXR do not support A+B+C but A+(B+C). Add parentheses!"); 		
	}
	;

	afactor: ID{
		int t = position($1);
		if(t > 0){
			gen(lod,0,getaddr(t),gettype(t));
		}
		else{
			yyerror("this variable don't exists."); 		
		}
	}|
	NUM{
		genplus(lit,0,$1,int_t,$1);
	}|
	LP aexpr RP
	;

	bexpr: bexpr OR bterm{
		gen(opr,0,15,bool_t);
	}|
	bterm|
	ID ASSIGN bexpr{
		yyerror("assign symbol do not have return value in CXR!");
	}
	;

	bterm: bterm AND bfactor{
		gen(opr,0,14,bool_t);
	}|
	bfactor
	;

	bfactor: ID{
		int t = position($1);
		if(t > 0){
			if(table[t].type != 1)
				yyerror("this variable is not boolean type.");
			else{
				gen(lod,0,getaddr(t),gettype(t));
			}
		}
		else{
			yyerror("this variable don't exists"); 	
		}
	}|
	TRUE{
		genplus(lit,0,1,bool_t,1);
	}|
	FALSE{
		genplus(lit,0,0,bool_t,1);
	}|
	NOT bfactor{
		gen(opr,0,1,bool_t);
	}|
	ODD afactor{
		gen(opr,0,6,bool_t); 	
	}|
	LP bexpr RP|
	rel
	;

	rel: ID RELOP aexpr{
		int t = position($1);
		double temp = 0;
		if (t > 0){
			if(table[t].type != 0) yyerror("this variable don't have correct type.");		
		}
		else yyerror("this variable don't exists."); 	
		if (strcmp($2, "<") == 0){
			gen(lod,0,getaddr(t),gettype(t));
			gen(opr,0,10,bool_t);
		}
		else if (strcmp($2, "<=") == 0){
			gen(lod,0,getaddr(t),gettype(t));
			gen(opr,0,13,bool_t);
		}
		else if (strcmp($2, ">") == 0){
			gen(lod,0,getaddr(t),gettype(t));
			gen(opr,0,12,bool_t);
		}
		else if (strcmp($2, ">=") == 0){
			gen(lod,0,getaddr(t),gettype(t));
			gen(opr,0,11,bool_t);
		}
		else if (strcmp($2, "==") == 0){
			gen(lod,0,getaddr(t),gettype(t));
			gen(opr,0,8,bool_t);
		}
		else if (strcmp($2, "!=") == 0){
			gen(lod,0,getaddr(t),gettype(t));
			gen(opr,0,9,bool_t);
		}
		else
			yyerror("wrong relop type\n");	
	 }|
	 NUM RELOP aexpr{
		printf("num,relop,expr\n");
		if(strcmp($2, "<") == 0){
			genplus(lit,0,$1,int_t,$1);
			gen(opr,0,10,bool_t);
		}
		else if(strcmp($2, "<=") == 0){
			genplus(lit,0,$1,int_t,$1);
			gen(opr,0,13,bool_t);
		}
		else if(strcmp($2, ">") == 0){
			genplus(lit,0,$1,int_t,$1);
			gen(opr,0,12,bool_t);
		}
		else if(strcmp($2, ">=") == 0){
			genplus(lit,0,$1,int_t,$1);
			gen(opr,0,11,bool_t);
		}
		else if(strcmp($2, "==") == 0){
			genplus(lit,0,$1,int_t,$1);
			gen(opr,0,8,bool_t);
		}
		else if(strcmp($2, "!=") == 0){
			genplus(lit,0,$1,int_t,$1);
			gen(opr,0,9,bool_t);
		}
		else
			yyerror("wrong relop type\n");
	 }
	 ;

%%
int main(int argc, char *argv[])
{
	int i;
	for(i = 0; i < argc ; i++){
		if (strcmp(argv[i],"-f") == 0 && argc > i)
			yyin = fopen(argv[++i] ,"r");
	}
	printf("**********CX Compiler:************\n");
	yyparse();
	printf("************pcode:****************\n");
	printpcode();
	return 0;
}
int yyerror(char *msg)
{
	printf("Error encountered: %d:  %s at %s\n", yylineno, msg, yytext);
	return 1;
}
