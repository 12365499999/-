#include<iostream>
#include<bits/stdc++.h>
#include<windows.h>
#include<algorithm>
using namespace std;
typedef int num,relateclass;
typedef map<num,pair<float,relateclass> > relatelist; //链接字列表，关联度，链接类型：-1前，1后 
typedef vector<pair<num,pair<float,relateclass> > > singlelist;
typedef pair<num,pair<float,relateclass> > psinglelist;
typedef map<num,num> comprehlist;
map<num,comprehlist> compreh;
map<num,relatelist> link; // 建立链接 
map<string,num> voca; //查询新             词 
map<num,string> revoca;
map<num,bool> say;
int N=0,times=0;
bool cmp(const psinglelist a,const psinglelist b){
	return abs(a.second.first)<=abs(b.second.first);
}
int isCN(string c,int i) {
    return c[i]<=0x7f&&c[i]>0?1:2;
}
void relatesort(int numm){
//	for(int )
}
singlelist lenovo(int numm){  //展开联想 排序 
	singlelist result;
	for(relatelist::iterator i=link[numm].begin();i!=link[numm].end();i++){
		if(i->first==numm)
		    continue;
		result.push_back(*i);
	}
	sort(result.begin(),result.end(),cmp);
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
		for(int j=0;j<result.size()&&j<10;j++){
			cout<<"linking"<<j<<":"<<revoca[result[j].first]<<"__times="<<link[slr[i]][result[j].first].first<<" class:"<<link[slr[i]][result[j].first].second<<endl;
		}
//		delete[] result;
	} 
}
void checkword(int slr[],int sum){
	for(int i=0;i<sum;i++){
		singlelist result=lenovo(slr[i]);
		if(link[slr[i]][result[0].first].second==-1){
			cout<<revoca[result[0].first]<<revoca[slr[i]]<<" ";
		}else {
		    cout<<revoca[slr[i]]<<revoca[result[0].first]<<" ";
		}
//		delete[] result;
	} 
}
bool cmp2(int a,int b){
	return link[a][a].first>link[b][b].first;
}
void learn(int numm){
	
}
void checkkey(int slr[],int sum){
	int keylen=sum/5+1;
	int keys[keylen]={0};
	sort(slr,slr+sum,cmp2);
	cout<<endl<<"THE Keys:";
	for(int i=0;i<keylen;i++){
		keys[i]=slr[i];
		cout<<revoca[keys[i]]<<" ";
	}
	cout<<endl;
}
void formerchain(int numm){
	if(say[numm]){
		return;
	}
	say[numm]=1;
	singlelist result=lenovo(numm);
	for(int i=0;i<result.size();i++){
	    if(result[i].second.second==-1){
	        formerchain(result[i].first);
	        break;
	    }
	}
	cout<<revoca[numm];
}
void followchain(int numm){
	if(say[numm]){
		return;
	}
	say[numm]=1;
	cout<<revoca[numm];
	singlelist result=lenovo(numm);
	for(int i=0;i<result.size();i++){
	    if(result[i].second.second==1){
	        followchain(result[i].first);
	        break;
	    }
	}
}
void checkchain(int slr[],int sum){
	for(int i=0;i<sum;i++){
		formerchain(slr[i]);
		say.clear();
		followchain(slr[i]);
		say.clear();
		cout<<endl;
	}
}
void randomlenovo();
main(){
	while(1){
	times++;
	string str;
	cin>>str;//听话 
	int *slr=new int[6000],sum=0;//短时记忆，词汇数 
	for(int i=0;i<str.size();){
		int len=isCN(str,i);
		string singleChar = str.substr(i, len);
		if(voca.find(singleChar)!=voca.end()){
		}
		else {//初始化 
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
			link[slr[i]][slr[j]].first+=-(i-j)*(i-j)*(i-j);//计算关联 
			link[slr[i]][slr[j]].second=link[slr[i]][slr[j]].first<=0?-1:1;
			link[slr[i]][slr[i]].first++;
		}
	}
	cout<<"N==="<<N<<endl<<"T==="<<times<<endl;//总词汇统计 
	//输出
//	checklist(slr,sum);
//	checkword(slr,sum);
//	checkkey(slr,sum); 
	checkchain(slr,sum);
	forget();
	cout<<endl;
	delete[] slr;
} 
} 
