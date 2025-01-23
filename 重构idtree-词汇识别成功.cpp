#include<bits/stdc++.h>
using namespace std;
typedef int id;
map<id,vector<int> > idtree;//����id�����id 
map<vector<int>,id > treeid;
map<id,string> id2char;//���뵥��id 
map<string,id> char2id; 
//map<id,vector<int> > idoper;//ÿ��id��Ӧ�Ĳ������� 
map<pair<id,id>,int> ididtimes;//����idͬʱ���ֵĴ����� 
map<id,int> idtimes;//����id���ֵĴ��� 
vector<int> comidvec;//�ϲ�id�б� 
void printid(int idd){//��� 
	for(int i=0;i<idtree[idd].size();i++){
		cout<<id2char[idtree[idd][i]];
	}
}
void printallcomid(){
	cout<<"�ʻ��\n";
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
//�����Ҫ���������ܶ��ԣ���ô�������һЩ���ߣ�����ɾ������ӡ�������������ϵ
int comid(vector<int> id1,vector<int>id2){//���id��Ȼ��ͨ���ϲ����� 
//	cout<<"\n���ںϲ�---";
//	printid(treeid[id1]);
//	cout<<" ";
//	printid(treeid[id2]);
//	cout<<endl; 
	id1.insert(id1.end(),id2.begin(),id2.end());
	if(treeid.find(id1)!=treeid.end())
	    return -1;
	cout<<"�ϲ��ɹ�������\n";
	comidvec.push_back(C);
	idtree[C]=id1;
	treeid[id1]=C;
	idtimes[C]=1; 
	return C++;
}
void del();
void add();
void src();
string readchar(string str,int i){//���벢���ص����ַ� 
    int len=isCN(str,i);
	return str.substr(i, len);
}
int recvchar(string str){//��¼����id 
	idtree[C].push_back(N);
	treeid[idtree[C]]=C;
	idtimes[C]=1;
	C++;
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
int getgroup(vector<int> idvec,int pos){//�Ӹõ��������id��� 
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
void checkidid(int id1,int id2){//�����Ƿ�ﵽ�ϲ���׼ 
	int checknum=idtimes[id1]+idtimes[id2];
	if(checknum>15){
		if(ididtimes[{id1,id2}]>=checknum/5){
			cout<<"ϲ��ϲ���"; 
			printid(comid(idtree[id1],idtree[id2]));
			cout<<endl;
		}
	}
}
vector<int> idvec2grvec(vector<int> idvec){//����id����ת���id 
	vector<int> vec;
	int idd=-1; 
	for(int i=0;i<idvec.size();i+=idtree[idd].size()){
		idd=getgroup(idvec,i);
//		cout<<idd<<" "; 
		idtimes[idd]++;
		if(i>0){
			ididtimes[{vec.back(),idd}]++;//��¼�ٽ���ϵ 
			checkidid(vec.back(),idd);//�����Ƿ�ﵽ�ϲ���׼ 
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
