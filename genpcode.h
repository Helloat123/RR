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
int table_cnt=0;
struct instruction{
	enum oprt f;
	int l;//l for call development. also value of const
	int a;
};
struct data{
	int value;
	enum object_t type;
};
int code_cnt=0;
char* id;
void enter(enum object k, enum object_t t){
	table_cnt++;
	strcpy(table[table_cnt].name,id);
	table[table_cnt].kind=k;
	table[table_cnt].type=t;
	table[table_cnt].addr=table_cnt+2;
	table[table_cnt].value=0;//默认值是0
}
int position(char* tid){
	strcpy(table[0].name,tid);//如果return的是0说明没找到
	for(int i=table_cnt; i>=0;i--){
		if (strcmp(table[i].name, tid)==0)
			return i;
	}
	return -1;
}
void assignv(int t, double val){
	table[t].value = val;
}
double getv(int t){
	if(t > 0)
		return table[t].value;
	return -999999; 
}
int getaddr(int t){
	if(t > 0)
		return table[t].addr;
	return -999999; 
}
int gettype(int t){
	if(t > 0)
		return table[t].type;
	return -1; 
}
int judgeeq(int i, double d){
	return ((d - i <= EPSINON && i <= d) || (0 <= i-d && i- d <= EPSINON) || (0 <= d  && d <= EPSINON) || (0 >= d && i >= -EPSINON));
}
void gen(enum oprt f, int l, int a);
#endif
