#include<bits/stdc++.h>
using namespace std;
typedef int id;
map<id,vector<int> > idtree;//����id�����id 
map<vector<int>,id > treeid;
map<id,string> id2char;//���뵥��id 
map<string,id> char2id; 
map<pair<id,id>,int> ididtimes;//����idͬʱ���ֵĴ����� 
map<id,int> idtimes;//����id���ֵĴ��� 
vector<int> comidvec;//�ϲ�id�б� 
struct abc{
	int a;
	int b;
	int c;
	abc():a(-1),b(-1),c(-1){}
	abc(int a_,int b_,int c_):a(a_),b(b_),c(c_) {}
	bool operator==(const abc& other) const {
        return (a == other.a) && (b == other.b) && (c == other.c);
    }
    bool operator>(const abc& other) const {//�ϸ����� 
        return (a > other.a) || (a == other.a && b > other.b) || (a == other.a && b == other.b && c > other.c);
    }
    bool operator<(const abc& other) const {
        return (a < other.a) || (a == other.a && b < other.b) || (a == other.a && b == other.b && c < other.c);
    }
}; //-1����ͨ��� 
map<id,abc> idstruct;//�̾�id���ܹ��ɵĽṹ---��������
//�ȳ���ʹ���¼�ӽڵ� 
map<abc,id> structid;
map<id,int> idpos;//�̾�λ�ã��п��ܾͶ�������
//ͨ��ͳ��Ƶ�ʽ���ɸ�� pos=1Ϊa��2Ϊb��5Ϊc��3Ϊab��6Ϊac��7Ϊbc��8Ϊabc
//���������� 
void printid(int idd){//��� ���ַ� 
	for(int i=0;i<idtree[idd].size();i++){
		cout<<id2char[idtree[idd][i]];
	}
}
void printallcomid(){//����ʻ�� 
	cout<<"�ʻ��\n";
	for(int i=0;i<comidvec.size();i++){
		printid(comidvec[i]);
		cout<<" ";
	}
	cout<<endl;
} 
void gettalkid(int idd){//�ݹ��������� ����̾� 
	if(idstruct[idd].a==idstruct[idd].b&&idstruct[idd].c==idstruct[idd].b){
		printid(idstruct[idd].a);
		cout<<" ";
	}else{
		if(idstruct[idd].a>-1){
			gettalkid(idstruct[idd].a);
		}
		if(idstruct[idd].b>-1){
			gettalkid(idstruct[idd].b);
		}
		if(idstruct[idd].c>-1){
			gettalkid(idstruct[idd].c);
		}
	}
}
void checkraw(vector<int> asvec){//�⹹��� 
    cout<<"�⹹��"; 
//    cout<<"\n������bug\n";
	if(asvec.size()==0){
//		cout<<"����⹹������\n";
		return;
	} 
	for(int i=0;i<asvec.size();i++){
//		cout<<"\nIIII---------"<<i<<"\n"; 
		gettalkid(asvec[i]);
		cout<<" ";
	}
}
int N,C,T,times,op=5;
int isCN(string c,int i) {
    return c[i]<=0x7f&&c[i]>0?1:2;
}
int comid(vector<int> id1,vector<int>id2){//���id��Ȼ��ͨ���ϲ�������˳��ע��̾� 
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
	//ע��̾�
//	idpos[T]=8;
    abc temp(C,C,C);
    idstruct[T]=temp;
    structid[temp]=T;
    T++;
	return C++;
}
string readchar(string str,int i){//���벢���ص����ַ� 
    int len=isCN(str,i);
	return str.substr(i, len);
}
int recvchar(string str){//��¼����id 
	idtree[C].push_back(N);
	treeid[idtree[C]]=C;
	idtimes[C]=1;
	C++;
	//ע��� 
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
void checkidid(int id1,int id2){
//�����Ƿ�ﵽ�ϲ���׼ 
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
vector<int> getstruct(vector<int> strvec,int pos){//��ȡ�ṹ 
//	cout<<"\nȷ�����ɷ���pos="<<pos<<endl;
	if(pos==strvec.size()){
		return strvec;
	}
	int a=strvec[pos],b=strvec[pos+1],c=strvec[pos+2];
	abc temp3(a,b,c),temp2(a,b,-1),temp1(-1,a,b);
	if(structid.find(temp3)!=structid.end()&&pos<strvec.size()-2){
	    cout<<"3��1��";
	    gettalkid(structid[temp3]);
	    cout<<endl;
		strvec.erase(strvec.begin()+pos);
	    strvec.erase(strvec.begin()+pos);
	    strvec[pos]=structid[temp3];
	    if(pos==0) return getstruct(strvec,pos);
	    else return getstruct(strvec,pos-1);
	}else
	if(structid.find(temp2)!=structid.end()&&pos<strvec.size()-1){
//		cout<<"\n����\n"; 
        cout<<"2��1��";
        gettalkid(structid[temp2]);
	    cout<<endl;
		strvec.erase(strvec.begin()+pos);
		strvec[pos]=structid[temp2];
	    if(pos==0) return getstruct(strvec,pos);
	    else return getstruct(strvec,pos-1);
	}else
	if(structid.find(temp1)!=structid.end()&&pos<strvec.size()-1){
//		cout<<"\n����\n"; 
        cout<<"2��1��";
        gettalkid(structid[temp1]);
	    cout<<endl;
		strvec.erase(strvec.begin()+pos);
		strvec[pos]=structid[temp1];
	    if(pos==0) return getstruct(strvec,pos);
	    else return getstruct(strvec,pos-1);
	}else{ 
		return getstruct(strvec,pos+1);
	}
}//����ͬ������ʵ�ʶ��� 
int newidstruct(abc temp){//ֻ���ڴ����ʱʹ�ô�id������Ĭ�Ͼ�id 
    cout<<"newidstruct:"<<T<<endl;
	idstruct[T]=temp;
	structid[temp]=T; 
	return T++;
} 
int checkstr(int idgr){//���ؾ�id 
    printid(idgr);
    cout<<" ";
    abc temp(idgr,idgr,idgr);
	if(structid.find(temp)==structid.end()){
		return newidstruct(temp);
	}
	cout<<"EXITS!!!   "<<temp.a<<" "<<structid[temp]<<" "<< idstruct[structid[temp]].b <<endl; 
	return structid[temp];
}
void construct(vector<int> rawvec){
	for(int i=0;i<rawvec.size();i++){
		abc temp1(-1,rawvec[i-1],rawvec[i]);
		abc temp2(rawvec[i-2],rawvec[i-1],rawvec[i]);
		if(i>0) newidstruct(temp1);
		if(i>1) newidstruct(temp2);
	}
	return;
}
vector<int> grvec2asvec(vector<int> grvec){
	vector<int> strvec;
//	cout<<"ת��\n";
	for(int i=0;i<grvec.size();i++){
		strvec.push_back(checkstr(grvec[i]));//�ڴ�֮ǰ�Ȱ��������idת�̾�id 
	}
	vector<int> asvec=getstruct(strvec,0);
//	cout<<"\n�����ץ������\n";
	checkraw(asvec);
	construct(asvec);
//	cout<<"!\n";
	return asvec;
}
//1�����¶��ϣ��Ӿ��в��Ϻϳ�ֱ������abcģʽ��d�� 
//2����ͷ��β��������ÿ���ʴ��������� 
//3���޸Ĵʻ�ϲ�ģʽ��һ�п����ݺ͸��� 


void aly(string str){
	vector<int> idvec=char2idvec(str);
	vector<int> grvec=idvec2grvec(idvec);
	vector<int> asvec=grvec2asvec(grvec);
}
main(){
	while(1){
        string str;
		cin>>str;
		aly(str);//ѧϰ�ʻ� 
		times++;
		if(times%20==0){
			printallcomid();
		}
	}
} 
