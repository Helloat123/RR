#ifndef GENPCODE
#define GENPCODE
#include <stdio.h>
#define ID_MAX_LENGTH 64
#define TABLE_SIZE 1024

enum object{constant, variable, prozedure};
enum object_t{int_t, bool_t};
enum oprt{lit, lod, sto, inn, jmp, jpc, opr};
char oprtname[][]={"LIT", "LOD", "STO", "INT", "JMP", "JPC", "OPR"};
struct idtable{
	char name[ID_MAX_LENGTH+1];
	enum object kind;
	enum object_t type;
	int value;
	int addr;
};
struct idtable table[TABLE_SIZE+1];
void enter(enum object,enum object_t);

struct instruction{
	enum oprt f;
	int l;
	int a;
	int v;
	enum object_t type;

};

struct data{
	int value;
	enum object_t type;
};

struct instruction code[CXMAX+1];//程序存储器，存储解释生成的中间代码
int cx;//记录程序条数

int base(int l, int b, struct data s[STACKSIZE+1]){//b和s在interpret中定义的，这里也要传参
	int rt;
	rt = b;
	while(l > 0){
		rt = (int)s[rt].value;
		l = l-1;
	}
	return rt;
}

void pcode_error(char* msg){
	printf("pcode error:%s\n", msg);
	exit(1);
}

void gen(enum oprt f, int l, int a, enum object_t type){
	if(cx > CXMAX) printf("program too long!");
	code[cx].f = f;
	code[cx].l = l;
	code[cx].a = a;
	code[cx].type = type;
	cx++;
}
void genplus(enum oprt f, int l, int a, enum object_t type, int v){//为lit专门使用的命令生成代码
	if(cx > CXMAX)
		printf("program too long!");
	code[cx].f = f;
	code[cx].l = l;
	code[cx].a = a;
	code[cx].v = v;
	code[cx].type = type;
	cx++;
}

void printpcode(){
	int i;
	for(i = 0; i < cx; i++) 
		printf("%8d:%s, %d, %d, %d\n",i, oprtname[code[i].f]], code[i].l, code[i].a, code[i].type);
}
#endif
