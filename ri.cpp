#include <string>
#include <vector>
#include <sstream>
#include <cstring>
#include <iostream>
#include <fstream>
using namespace std;
string s;
unsigned int pc=0;
const int opnum=13;
const string oprtname[opnum]={"LIT","LOD","STO","INT","JMP","JPC","OPR","RED","WRI","LOD1","GTA","CAL","STO1"};
enum oprt{lit, lod, sto, inn, jmp, jpc, opr, red,wri,lod1,gta,cal,sto1};
struct inst//instruction
{
	oprt a;
	int b,c;
};
vector<inst> code;
inst getcontent(const string &s)
{
	//48 : OPR 0 0
	inst res;
	stringstream ss(s);
	int trash;
	char rubbish;
	string oprname;
	ss>>trash>>rubbish>>oprname>>res.b>>res.c;
	for (int i=0;i<opnum;i++) if (oprtname[i]==oprname) {res.a=(oprt)i;break;}
	return res;
}
int st[4096],sp=-1,ss=0;
int top()
{
	return st[sp];
}
void push(const int &x)
{
	st[++sp]=x;
}
void pop()
{
	sp--;
}
int getv(const int &x)
{
	return st[x];
}
int line()
{
	int now=pc;
	pc++;
	inst i=code[now];
	switch (i.a)
	{
		int pos;
		case lit:
			push(i.c);
		break;
		case lod:
			pos=ss;
			for (int x=0;x<i.b;x++) pos=st[pos+1];
			push(getv(pos+i.c));
		break;
		case sto:
			pos=ss;
			for (int x=0;x<i.b;x++) pos=st[pos+1];
			st[pos+i.c]=top();
			pop();
		break;
		case inn:
			sp+=i.c;
		break;
		case jmp:
			pc=i.c;
		break;
		case jpc:
			if (!top()) pc=i.c;
			pop();
		break;
		case opr:
			switch (i.c)
			{
				case 0:
					if (pc==code.size()) 
					{
						cerr<<"main end with OPR 0 0"<<endl;
						return -1;
					}
					else cerr<<"function end with OPR 0 0"<<endl;
					sp=ss-1;
					pc=st[ss+2];
					ss=st[ss];
				break;
				case 1:
					st[sp]=!st[sp];
				break;
				case 2:
					st[sp-1]=st[sp-1]+st[sp];
					sp--;
				break;
				case 3:
					st[sp-1]=st[sp-1]-st[sp];
					sp--;
				break;
				case 4:
					st[sp-1]=st[sp-1]*st[sp];
					sp--;
				break;
				case 5:
					if (st[sp]==0)
					{
						cout<<"divide 0"<<endl;
						return 0;
					}
					st[sp-1]=st[sp-1]/st[sp];
					sp--;
				break;
				case 6:
					st[sp]=st[sp]&1;
				break;
				case 8:
					st[sp-1]=(st[sp-1]==st[sp]);
					sp--;
				break;
				case 9:
					st[sp-1]=(st[sp-1]!=st[sp]);
					sp--;
				break;
				case 10:
					st[sp-1]=(st[sp-1]<st[sp]);
					sp--;
				break;
				case 11:
					st[sp-1]=(st[sp-1]>=st[sp]);
					sp--;
				break;
				case 12:
					st[sp-1]=(st[sp-1]>st[sp]);
					sp--;
				break;
				case 13:
					st[sp-1]=(st[sp-1]<=st[sp]);
					sp--;
				break;
				case 14:
					if (st[sp]==0) 
					{
						cout<<"mod 0"<<endl;
						return -1;
					}
					st[sp-1]=st[sp-1]%st[sp];
					sp--;
				break;
				case 15:
					st[sp-1]=st[sp-1]^st[sp];
					sp--;
				break;
				case 16:
					st[sp-1]=(st[sp-1]&&st[sp]);
					sp--;
				break;
				case 17:
					st[sp-1]=(st[sp-1]||st[sp]);
					sp--;
				break;
				case 18:
					return -1;
				default:
					throw -1;
			}
		break;
		case red:
			cin>>st[i.c];
		break;
		case wri:
			cout<<"write:"<<top()<<endl;
			pop();
		break;
		case lod1:
			st[sp]=st[st[sp]];
		break;
		case gta:
			pos=ss;
			for (int x=0;x<i.b;x++) pos=st[pos+1];
			push(pos+i.c);
		break;
		case cal:
			st[sp+1]=ss;
			//push(ss);
			if (i.b) st[sp+2]=ss;
			else st[sp+2]=st[ss+1];
			ss=sp+1;
			st[sp+3]=pc;
			pc=i.c;
			//push(
		break;
		case sto1:
			st[st[sp-1]]=st[sp];
			sp-=2;
		break;
		default:
			throw -1;
	}
	return 0;
}
ofstream f("ri.log");
void pstack()
{
	cout<<"stack{"<<endl;
	for (int i=sp;i>=0;i--)
	{
		cout<<i<<":"<<st[i]<<endl;
	}
	cout<<"}stack"<<endl;
	cout<<"sp="<<sp<<endl;
	cout<<"pc="<<pc<<endl;
	cout<<"ss="<<ss<<endl;
}
int main(int argc,char **argv)
{
	bool infile=false;
	if (argc>1&&strcmp(argv[1],"-f")==0) freopen(argv[2],"r",stdin),infile=true;
	while (getline(cin,s))
	{
		f<<s<<endl;
		if (s=="run"||s=="r") break;
		inst temp=getcontent(s);
		code.push_back(temp);
		//if (temp.a==opr&&temp.b==0&&temp.c==0) break;
	}
	if (infile)
	{
		freopen("/dev/tty","r",stdin);
		cin.clear();
		cin.sync();
	}
	cerr<<"done"<<endl;
	f<<"got pcode"<<endl;
	while (getline(cin,s))
	{
		f<<"got "<<s<<endl;
		if (s=="next"||s=="n"||s=="")
		{
			if (pc>=code.size()) 
			{
				cout<<"DONE! input quit to quit"<<endl;
				continue;
			}
			cerr<<"executing "<<pc<<':'<<oprtname[code[pc].a]<<' '<<code[pc].b<<' '<<code[pc].c<<endl;
			f<<"executing "<<pc<<':'<<oprtname[code[pc].a]<<' '<<code[pc].b<<' '<<code[pc].c<<endl;
			cout<<"executing "<<pc<<':'<<oprtname[code[pc].a]<<' '<<code[pc].b<<' '<<code[pc].c<<endl;
			if (line()==-1) pc=code.size();
			pstack();
		}
		else if (s=="continue"||s=="c"||s=="con")
		{
			if (pc>=code.size()) 
			{
				cout<<"DONE! input quit to quit"<<endl;
				continue;
			}
			while (pc<code.size()) 
			{
				if (line()==-1) pc=code.size();	
			}
		}
		else if (s=="quit"||s=="q")
		{
			cerr<<"now quit"<<endl;
			f<<"now quit"<<endl;
			return 0;
		}
		else 
		{
			cerr<<"undefined"<<endl;
			f<<"undefine"<<endl;
		}
	}
	f.close();
	return 0;
}
