#include<bits/stdc++.h>
using namespace std;
typedef int id;
map<id,vector<int> > idtree;//����id�����id 
map<vector<int>,id > treeid;
map<id,string> id2char;//���뵥��id 
map<string,id> char2id; 
map<id,vector<int> > idoper;//ÿ��id��Ӧ�Ĳ������� 
int N,C,times,op=5;
int isCN(string c,int i) {
    return c[i]<=0x7f&&c[i]>0?1:2;
}
void cridtree(int idd,vector<int> idgroup){//������idʱ���¼��id 
//	idtree[idd]=idgroup;
}
void idenid(vector<int> temp){//���������ҳ�id 
	
}
void crid(vector<int> temp){//������id 
	
}
//�����Ҫ���������ܶ��ԣ���ô�������һЩ���ߣ�����ɾ������ӡ�������������ϵ
void del();
void add();
void src();
string readchar(string str,int i){//���벢���ص����ַ� 
    int len=isCN(str,i);
	return str.substr(i, len);
}
int recvchar(string str){//��¼����id 
//	idtree[N]=-1;
	id2char[N]=str;
	char2id[str]=N;
	return N++;
}
int checkchar(string str){//���鵥��id 
	if(char2id.find(str)!=char2id.end()){
		return char2id[str];//������� 
	}else{
		return recvchar(str);
	}
}
vector<int> char2idvec(string str){//����ת����id���� 
	vector<int> vec;
	for(int i=0;i<str.size();i+=readchar(str,i).size()){
		 vec.push_back(checkchar(readchar(str,i)));
	}
	return vec;
}
int getgroup(vector<int> idvec,int pos){//�Ӹõ�����id 
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
vector<int> idvec2grvec(vector<int> idvec){//����id����ת�������� 
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
