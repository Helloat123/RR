#include "genpcode.h"
#include <stdio.h>
#include <string.h>
const char oprtname[15][5]={"LIT", "LOD", "STO", "INT", "JMP", "JPC", "OPR","RED","WRI","LOD1","GTA"};
char *id;
int table_cnt=0,code_cnt=0,temp_num=0;
void enter(enum object k, enum object_t t){
	table_cnt++;
	strcpy(table[table_cnt].name,id);
	table[table_cnt].kind=k;
	table[table_cnt].type=t;
	table[table_cnt].addr=table_cnt-1;
	table[table_cnt].value=temp_num;
	temp_num=0;
}
int position(char* tid){
	strcpy(table[0].name,tid);//如果return的是0说明没找到
	for(int i=table_cnt; i>=0;i--){
		if (strcmp(table[i].name, tid)==0)
			return i;
	}
	return -1;
}
int getv(int t){
	if (t>0) return table[t].value;
	return -1; 
}
int getaddr(int t){
	if (t>0) return table[t].addr;
	return -1; 
}
int gettype(int t){
	if (t>0) return table[t].type;
	return -1;
}
void gen(enum oprt f, int l, int a){
	code[code_cnt].f=f;
	code[code_cnt].l=l;
	code[code_cnt++].a=a;
	//printf("%8d:%s, %d, %d\n",code_cnt++, oprtname[f], l, a);
}
void printpcode(){
	for (int i=0;i<code_cnt;i++) printf("%5d : %s %d %d\n",i,oprtname[code[i].f],code[i].l,code[i].a);
}

