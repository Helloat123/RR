#include "genpcode.h"
void enter(enum object a,enum object_t b)
{

}
void gen(enum oprt f, int l, int a){
	printf("%8d:%s, %d, %d\n",code_cnt++, oprtname[f], l, a);
}
/*
void printpcode(){
	int i;
	for(i = 0; i < code_cnt; i++) 
		printf("%8d:%s, %d, %d, %d\n",i, oprtname[code[i].f], code[i].l, code[i].a, code[i].type);
}
*/
