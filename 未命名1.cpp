#include<iostream>
#include<bits/stdc++.h>
#include<windows.h>
#include <algorithm>
using namespace std;
typedef int num,relateclass;
typedef map<num,pair<float,relateclass> > relatelist; //�������б�����ֵ���������ͣ�-1ǰ��1�� 
typedef vector<pair<num,pair<float,relateclass> > > singlelist;
typedef pair<num,pair<float,relateclass> > psinglelist;
map<num,relatelist> link; // �������� 
map<string,num> voca; //��ѯ��             �� 
map<num,string> revoca;
int N=0,times=0;
bool cmp(const psinglelist a,const psinglelist b){
	cout<<"cmp----"<<revoca[a.first]<<":"<<revoca[b.first]<<endl;
	return abs(a.second.first)<=abs(b.second.first);
}
int isCN(string c,int i) {
    return c[i]<=0x7f&&c[i]>0?1:2;
}
void relatesort(int numm){
//	for(int )
}
singlelist lenovo(int numm){  //չ������ ���� 
//	int result[10]={0};
	singlelist result;
	for(relatelist::iterator i=link[numm].begin();i!=link[numm].end();i++){
		result.push_back(*i);
	}
//	cout<<"LISTnumber::"<<revoca[numm]<<"==="<<link[numm].end()-link[numm].begin()<<endl;
	sort(result.begin(),result.end(),cmp);
//	for(int i=0,j=0;i<5;i++,j++){
//		result[i]=a[j].first;
//	}
	return result;
}
void forget(){
	for(int i=0;i<N;i++){
		for(relatelist::iterator j=link[i].begin();j!=link[i].end();j++){
			j->second.first*=1.003;
		}
	}
}
void checklist(int slr[],int sum){
	for(int i=0;i<sum;i++){
		singlelist result=lenovo(slr[i]);
		cout<<revoca[slr[i]]<<"---FINDING\n";
		for(int j=0;j<10;j++){
			cout<<"linking"<<j<<":"<<revoca[result[j].first]<<"__times="<<link[slr[i]][result[j].first].first<<" class:"<<link[slr[i]][result[j].first].second<<endl;
		}
//		delete[] result;
	} 
}
void checkword(int slr[],int sum){
	for(int i=0;i<sum;i++){
		singlelist result=lenovo(slr[i]);
		if(link[slr[i]][result[1].first].second==-1){
			cout<<revoca[result[1].first]<<revoca[slr[i]]<<" ";
		}else {
		    cout<<revoca[slr[i]]<<revoca[result[1].first]<<" ";
		}
//		delete[] result;
	} 
}
main(){
	while(1){
	times++;
	string str;
	cin>>str;//���� 
	int *slr=new int[6000],sum=0;//��ʱ���䣬�ʻ��� 
	for(int i=0;i<str.size();){
		int len=isCN(str,i);
		string singleChar = str.substr(i, len);
//		cout<<"reading:"<<singleChar;//���� 
		if(voca.find(singleChar)!=voca.end()){
//			cout<<" YES!!!\n";
		}
		else {//��ʼ�� 
//			cout<<" NO....\n";
			voca[singleChar]=N;
			revoca[N]=singleChar;
			relatelist infi;
			infi[N]={};
			link[N]=infi;
			N++;
		}
		slr[sum]=voca[singleChar];
		sum++;
		i+=len;
	}
	for(int i=0;i<sum;i++){
		//link[slr[i]]
		for(int j=0;j<sum;j++){
			link[slr[i]][slr[j]].first+=-(i-j)*(i-j)*(i-j);//������� 
			link[slr[i]][slr[j]].second=link[slr[i]][slr[j]].first<=0?-1:1;
//			cout<<"INFINITING:"<<revoca[slr[i]]<<"&"<<revoca[slr[j]]<<endl;
		}
	}
	cout<<"N==="<<N<<endl<<"T==="<<times<<endl;//�ܴʻ�ͳ�� 
	checklist(slr,sum);
	//���
//	checkword(slr,sum);
	forget();
	cout<<endl;
	delete[] slr;
} 
} 
