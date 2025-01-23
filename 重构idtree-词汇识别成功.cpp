#include<bits/stdc++.h>
using namespace std;
typedef int id;
map<id,vector<int> > idtree;//单字id与多字id 
map<vector<int>,id > treeid;
map<id,string> id2char;//字与单字id 
map<string,id> char2id; 
//map<id,vector<int> > idoper;//每个id对应的操作序列 
map<pair<id,id>,int> ididtimes;//相邻id同时出现的次数； 
map<id,int> idtimes;//单个id出现的次数 
vector<int> comidvec;//合并id列表 
void printid(int idd){//输出 
	for(int i=0;i<idtree[idd].size();i++){
		cout<<id2char[idtree[idd][i]];
	}
}
void printallcomid(){
	cout<<"词汇表：\n";
	for(int i=0;i<comidvec.size();i++){
		printid(comidvec[i]);
		cout<<" ";
	}
	cout<<endl;
} 
int N,C,times,op=5;
int isCN(string c,int i) {
    return c[i]<=0x7f&&c[i]>0?1:2;
}
//如果需要发挥主观能动性，那么必须给其一些工具，例如删除、添加、搜索、建立关系
int comid(vector<int> id1,vector<int>id2){//组合id必然是通过合并而来 
//	cout<<"\n正在合并---";
//	printid(treeid[id1]);
//	cout<<" ";
//	printid(treeid[id2]);
//	cout<<endl; 
	id1.insert(id1.end(),id2.begin(),id2.end());
	if(treeid.find(id1)!=treeid.end())
	    return -1;
	cout<<"合并成功！！！\n";
	comidvec.push_back(C);
	idtree[C]=id1;
	treeid[id1]=C;
	idtimes[C]=1; 
	return C++;
}
void del();
void add();
void src();
string readchar(string str,int i){//读入并返回单个字符 
    int len=isCN(str,i);
	return str.substr(i, len);
}
int recvchar(string str){//收录单字id 
	idtree[C].push_back(N);
	treeid[idtree[C]]=C;
	idtimes[C]=1;
	C++;
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
int getgroup(vector<int> idvec,int pos){//从该点查找最优id组合 
	vector<int> vec;
	int idd=-1;
//	cout<<"\ngetgroup:";
//	for(int i=0;i<vec.size();i++){
//		cout<<vec[i]<<" ";
//	}cout<<endl;
	for(int i=pos;i<idvec.size();i++){
//		cout<<idvec[i]<<" ";
		vec.push_back(idvec[i]);
		if(treeid.find(vec)==treeid.end()){
//			cout<<endl;
			return idd;
		}
		idd=treeid[vec];
	}
//	cout<<endl;
	return idd;
}
void checkidid(int id1,int id2){//检验是否达到合并标准 
	int checknum=idtimes[id1]+idtimes[id2];
	if(checknum>15){
		if(ididtimes[{id1,id2}]>=checknum/5){
			cout<<"喜提合并："; 
			printid(comid(idtree[id1],idtree[id2]));
			cout<<endl;
		}
	}
}
vector<int> idvec2grvec(vector<int> idvec){//单字id序列转组合id 
	vector<int> vec;
	int idd=-1; 
	for(int i=0;i<idvec.size();i+=idtree[idd].size()){
		idd=getgroup(idvec,i);
//		cout<<idd<<" "; 
		idtimes[idd]++;
		if(i>0){
			ididtimes[{vec.back(),idd}]++;//记录临近关系 
			checkidid(vec.back(),idd);//检验是否达到合并标准 
		}
		vec.push_back(idd);
	}
	return vec;
}
void aly(string str){
	vector<int> idvec=char2idvec(str);
	vector<int> grvec=idvec2grvec(idvec);
}
main(){
	while(1){
        string str;
		cin>>str;
		aly(str);
		times++;
		if(times%20==0){
			printallcomid();
		}
	}
} 
