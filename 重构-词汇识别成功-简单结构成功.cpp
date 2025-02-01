#include<bits/stdc++.h>
using namespace std;
typedef int id;
map<id,vector<int> > idtree;//单字id与多字id 
map<vector<int>,id > treeid;
map<id,string> id2char;//字与单字id 
map<string,id> char2id; 
map<pair<id,id>,int> ididtimes;//相邻id同时出现的次数； 
map<id,int> idtimes;//单个id出现的次数 
vector<int> comidvec;//合并id列表 
struct abc{
	int a;
	int b;
	int c;
	abc():a(-1),b(-1),c(-1){}
	abc(int a_,int b_,int c_):a(a_),b(b_),c(c_) {}
	bool operator==(const abc& other) const {
        return (a == other.a) && (b == other.b) && (c == other.c);
    }
    bool operator>(const abc& other) const {//严格弱序 
        return (a > other.a) || (a == other.a && b > other.b) || (a == other.a && b == other.b && c > other.c);
    }
    bool operator<(const abc& other) const {
        return (a < other.a) || (a == other.a && b < other.b) || (a == other.a && b == other.b && c < other.c);
    }
}; //-1代表通配符 
map<id,abc> idstruct;//短句id所能构成的结构---由下至上
//先尝试使其记录子节点 
map<abc,id> structid;
map<id,int> idpos;//短句位置，有可能就都记下来
//通过统计频率进行筛除 pos=1为a，2为b，5为c，3为ab，6为ac，7为bc，8为abc
//建三叉树吗？ 
void printid(int idd){//输出 单字符 
	for(int i=0;i<idtree[idd].size();i++){
		cout<<id2char[idtree[idd][i]];
	}
}
void printallcomid(){//输出词汇表 
	cout<<"词汇表：\n";
	for(int i=0;i<comidvec.size();i++){
		printid(comidvec[i]);
		cout<<" ";
	}
	cout<<endl;
} 
void gettalkid(int idd){//递归搜索子树 输出短句 
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
void checkraw(vector<int> asvec){//解构输出 
    cout<<"解构："; 
//    cout<<"\n找嫌疑bug\n";
	if(asvec.size()==0){
//		cout<<"无需解构！！！\n";
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
int comid(vector<int> id1,vector<int>id2){//组合id必然是通过合并而来，顺便注册短句 
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
	//注册短句
//	idpos[T]=8;
    abc temp(C,C,C);
    idstruct[T]=temp;
    structid[temp]=T;
    T++;
	return C++;
}
string readchar(string str,int i){//读入并返回单个字符 
    int len=isCN(str,i);
	return str.substr(i, len);
}
int recvchar(string str){//收录单字id 
	idtree[C].push_back(N);
	treeid[idtree[C]]=C;
	idtimes[C]=1;
	C++;
	//注册词 
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
void checkidid(int id1,int id2){
//检验是否达到合并标准 
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
vector<int> getstruct(vector<int> strvec,int pos){//获取结构 
//	cout<<"\n确定嫌疑犯：pos="<<pos<<endl;
	if(pos==strvec.size()){
		return strvec;
	}
	int a=strvec[pos],b=strvec[pos+1],c=strvec[pos+2];
	abc temp3(a,b,c),temp2(a,b,-1),temp1(-1,a,b);
	if(structid.find(temp3)!=structid.end()&&pos<strvec.size()-2){
	    cout<<"3合1：";
	    gettalkid(structid[temp3]);
	    cout<<endl;
		strvec.erase(strvec.begin()+pos);
	    strvec.erase(strvec.begin()+pos);
	    strvec[pos]=structid[temp3];
	    if(pos==0) return getstruct(strvec,pos);
	    else return getstruct(strvec,pos-1);
	}else
	if(structid.find(temp2)!=structid.end()&&pos<strvec.size()-1){
//		cout<<"\n快了\n"; 
        cout<<"2合1：";
        gettalkid(structid[temp2]);
	    cout<<endl;
		strvec.erase(strvec.begin()+pos);
		strvec[pos]=structid[temp2];
	    if(pos==0) return getstruct(strvec,pos);
	    else return getstruct(strvec,pos-1);
	}else
	if(structid.find(temp1)!=structid.end()&&pos<strvec.size()-1){
//		cout<<"\n快了\n"; 
        cout<<"2合1：";
        gettalkid(structid[temp1]);
	    cout<<endl;
		strvec.erase(strvec.begin()+pos);
		strvec[pos]=structid[temp1];
	    if(pos==0) return getstruct(strvec,pos);
	    else return getstruct(strvec,pos-1);
	}else{ 
		return getstruct(strvec,pos+1);
	}
}//优先同档次中实际对象 
int newidstruct(abc temp){//只有在传入词时使用词id，否则默认句id 
    cout<<"newidstruct:"<<T<<endl;
	idstruct[T]=temp;
	structid[temp]=T; 
	return T++;
} 
int checkstr(int idgr){//传回句id 
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
//	cout<<"转句\n";
	for(int i=0;i<grvec.size();i++){
		strvec.push_back(checkstr(grvec[i]));//在此之前先把所有组合id转短句id 
	}
	vector<int> asvec=getstruct(strvec,0);
//	cout<<"\n好像快抓到你了\n";
	checkraw(asvec);
	construct(asvec);
//	cout<<"!\n";
	return asvec;
}
//1、有下而上，从句中不断合成直到符合abc模式（d） 
//2、从头至尾，遍历的每个词从最深搜索 
//3、修改词汇合并模式，一切靠数据和概率 


void aly(string str){
	vector<int> idvec=char2idvec(str);
	vector<int> grvec=idvec2grvec(idvec);
	vector<int> asvec=grvec2asvec(grvec);
}
main(){
	while(1){
        string str;
		cin>>str;
		aly(str);//学习词汇 
		times++;
		if(times%20==0){
			printallcomid();
		}
	}
} 
