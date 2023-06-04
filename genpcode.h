#ifndef _GENPCODE_H
#define _GENPCODE_H

#define ID_MAX_LENGTH 64
#define TABLE_SIZE 1024
#define CODE_MAX_SIZE 4096

enum object{constant, variable, procedure};
enum object_t{int_t, bool_t,ptr_t,void_t};
enum oprt{lit, lod, sto, inn, jmp, jpc, opr, red,wri,lod1,gta,cal,sto1};
struct idtable{
	char name[ID_MAX_LENGTH+1];
	enum object kind;
	enum object_t type;
	int value;
	int addr;
	int level;
};
struct idtable table[TABLE_SIZE+1];
struct instruction{
	enum oprt f;
	int l;
	int a;
};
struct instruction code[CODE_MAX_SIZE];
extern int code_cnt,temp_num,level,var_cnt,nowprocedure,table_cnt;
extern char* id;

void enter(enum object k, enum object_t t);
int position(char* tid);
int getv(int t);
int getaddr(int t);
int gettype(int t);
void gen(enum oprt f,int l,int a);
void printpcode();

#endif
