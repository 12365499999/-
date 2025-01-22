#include<bits/stdc++.h>
using namespace std;
typedef int id;
map<id,vector<int> > idtree;//单字id与多字id 
map<vector<int>,id > treeid;
map<id,string> id2char;//字与单字id 
map<string,id> char2id; 
map<id,vector<int> > idoper;//每个id对应的操作序列 
int N,C,times,op=5;
int isCN(string c,int i) {
    return c[i]<=0x7f&&c[i]>0?1:2;
}
void cridtree(int idd,vector<int> idgroup){//创建新id时需记录子id 
//	idtree[idd]=idgroup;
}
void idenid(vector<int> temp){//在序列中找出id 
	
}
void crid(vector<int> temp){//创建新id 
	
}
//如果需要发挥主观能动性，那么必须给其一些工具，例如删除、添加、搜索、建立关系
void del();
void add();
void src();
string readchar(string str,int i){//读入并返回单个字符 
    int len=isCN(str,i);
	return str.substr(i, len);
}
int recvchar(string str){//收录单字id 
//	idtree[N]=-1;
	id2char[N]=str;
	char2id[str]=N;
	return N++;
}
int checkchar(string str){//检验单字id 
	if(char2id.find(str)!=char2id.end()){
		return char2id[str];//如果存在 
	}else{
		return recvchar(str);
	}
}
vector<int> char2idvec(string str){//输入转单字id序列 
	vector<int> vec;
	for(int i=0;i<str.size();i+=readchar(str,i).size()){
		 vec.push_back(checkchar(readchar(str,i)));
	}
	return vec;
}
int getgroup(vector<int> idvec,int pos){//从该点查找最长id 
	vector<int> vec;
	int idd=-1;
	for(int i=pos;i<idvec.size();i++){
		vec.push_back(idvec[i]);
		idd=treeid[vec];
		if(treeid.find(vec)==treeid.end()){
			return idd;
		}
	}
	return idd;
}
vector<int> idvec2grvec(vector<int> idvec){//单字id序列转建构序列 
	vector<int> vec;
	for(int i=0;i<idvec.size();i++){
		vec.push_back(getgroup(idvec,i));
	}
	return vec;
}
void op1(){
}
void op2(){
}
void op3(){
}
void op4(){
}
void op5(){
}
void op6(){
}
void opergr(int operid){
	for(int i=0;i<idoper[operid].size();i++){
		if(idoper[operid][i]==1){
			op1();
		}else if(idoper[operid][i]==2){
			op2();
		}else if(idoper[operid][i]==3){
			op3();
		}else if(idoper[operid][i]==4){
			op4();
		}else if(idoper[operid][i]==5){
			op5();
		}else if(idoper[operid][i]==6){
			op6();
		}
	}
}
void opergrvec(vector<int> grvec){
	for(int i=0;i<grvec.size();i++){
		opergr(grvec[i]);
	}
} 
void aly(string str){
	vector<int> idvec=char2idvec(str);
	vector<int> grvec=idvec2grvec(idvec);
	opergrvec(grvec);
}
main(){
	while(1){
        string str;
		cin>>str;
		aly(str);
	}
} 
