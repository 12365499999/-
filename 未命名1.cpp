#include<iostream>
#include<bits/stdc++.h>
#include<windows.h>
#include<algorithm>
using namespace std;
typedef int num,direct,wordclass,id,pos;
typedef map<num,pair<float,direct> > relatelist; //链接字列表，关联度，链接类型：-1前，1后 
typedef vector<pair<num,pair<float,direct> > > singlelist;
typedef pair<num,pair<float,direct> > psinglelist;
typedef map<num,num> comprehlist; 
typedef map<id,vector<num> > group;
//typedef map<num,vector<int> > wordlen;
map<num,comprehlist> compreh;
map<num,relatelist> link; // 建立链接 
map<string,num> voca; //查询新词 
map<num,string> revoca;
map<num,bool> say;
map<num,bool> see;
map<vector<int>,id> shandle;//句子找id 
map<id,vector<int> > rehandle;//id找短句
map<id,int> idlen;//句子长度 
map<num,vector<num> > wordnext;// 下一个字列表 
int N=0,times=0,C=0;
void printhandle(int);
int newbreakchain(vector<int>);
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
void formerchain(int numm,int head){
	if(say[numm]){
		return;
	}
	say[numm]=1;
	singlelist result=lenovo(numm);
	for(int i=0;i<result.size();i++){
	    if(result[i].second.second==-1){
	        formerchain(result[i].first,head);
	        break;
	    }
	}
	if(numm!=head)
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
		formerchain(slr[i],slr[i]);
		say.clear();
		followchain(slr[i]);
		say.clear();
		cout<<endl;
	}
}
int checkchainhandle(int numm,vector<int> handlechain,int slr[],int poss){
	handlechain.push_back(numm);
	int idd=-1;
	if(shandle.find(handlechain)!=shandle.end()){
		idd=shandle[handlechain];
	}
	for(int i=0;i<wordnext[numm].size();i++){
		if(wordnext[numm][i]==slr[poss+1]){
			int iddd=checkchainhandle(slr[poss+1],handlechain,slr,poss+1);
            if(idlen[iddd]>idlen[idd]){
            	idd=iddd;
			}
		}
	}
	if(idd==-1){//截断学习 
	    idd=newbreakchain(handlechain);
	}
	if(idlen[idd]<1){//筛选短句长度 
		return -1;
	}
	else return idd;
}
int newbreakchain(vector<int> handlechain){
    for(int i=0;i<handlechain.size()-1;i++){
    	if(find(wordnext[handlechain[i]].begin(),wordnext[handlechain[i]].end(),handlechain[i+1])==wordnext[handlechain[i]].end())
	    wordnext[handlechain[i]].push_back(handlechain[i+1]);
	}
	shandle[handlechain]=C;
	rehandle[C]=handlechain;
	idlen[C]=handlechain.size();
	C++;
	return C-1;
}
int newhandlechain(int slr[],int i,int j){
	vector<int> handlechain;
	for(int k=i;k<=j;k++){
		handlechain.push_back(slr[k]);
	}
	return newbreakchain(handlechain);
}
void printhandle(int idd){
	vector<int> printhandles;
	printhandles=rehandle[idd];
	for(int i=0;i<printhandles.size();i++){
		cout<<revoca[printhandles[i]];
	}
	cout<<" ";
}
void totallearn(int idslr[],int idsum,int idlong){//升筛 
	idlong++;
//	cout<<idsum<<" "<<idlong<<endl;
	for(int i=0;i<idsum;i++){
		if(idlen[idslr[i]]>=idlong){
//			cout<<"越筛handle:"<<idslr[i]<<" "<<endl;
		    continue;
		}
	    vector<int> temp;
		for(int j=i;j<=idsum;j++){
			if(temp.size()>=idlong){
				if(shandle.find(temp)!=shandle.end())
				    break;
		        newbreakchain(temp);
			    i=j-1;
				break;
			}
			temp.insert(temp.end(),rehandle[idslr[j]].begin(),rehandle[idslr[j]].end());
			if(j==idsum&&j-i>1){
				newbreakchain(temp);
//	            cout<<"升筛完成"<<endl; 
			}
		}
	}
}
void randomlenovo();
main(){
	idlen[-1]=-1;
	while(1){
	times++;
	string str;
	cin>>str;//听话 
	int *slr=new int[6000],sum=0;//短时记忆，词汇数 
	int *idslr=new int[6000],idsum=0,idlong=999999;
	vector<int> slrhandle;
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
		slrhandle.push_back(voca[singleChar]);
		sum++;
		i+=len;
	}
	for(int i=0;i<sum;i++){
		//link[slr[i]]
		for(int j=0;j<sum;j++){
			link[slr[i]][slr[j]].first+=-(i-j)*(i-j)*(i-j);//计算关联 
			link[slr[i]][slr[j]].second=link[slr[i]][slr[j]].first<=0?-1:1;
			link[slr[i]][slr[i]].first++;
//			shortwordlearn[slr[i]][slr[i]].push_back(i-j);
//		    linchain[slr[i]][slr[j]]=true;//标记直链 
		}
	}
	//句柄识别
//	cout<<"ID:\n";
	for(int i=0;i<sum;){
	    vector<int> handleee;
        int idd=checkchainhandle(slr[i],handleee,slr,i);
//        cout<<idd<<"  "<<idlen[idd]<<endl;
//        if(idd==-1){
//        	int j;
//        	for(j=i+1;j<sum;j++){
//        		if(checkchainhandle(slr[j],handleee,slr,j)!=-1){
//        			break;
//				}
//			}
//			j--;
////			cout<<i<<"----"<<j<<endl;
//	        idslr[idsum]=newhandlechain(slr,i,j);
//	       	idlong=min(idlong,idlen[idslr[idsum]]);
//	        idsum++;
//			i=j+1;
//        	continue;
//		}
       	idlong=min(idlong,idlen[idd]);
       	idslr[idsum]=idd;
       	idsum++;
		i+=idlen[idd];
		printhandle(idd);
	}
	//句柄整合升级 
	totallearn(idslr,idsum,idlong);
	//输出
	cout<<endl<<"N==="<<N<<endl<<"T==="<<times<<endl<<"C==="<<C<<endl;//总词汇统计 
//	checklist(slr,sum);
//	checkword(slr,sum);
//	checkkey(slr,sum); 
//	checkchain(slr,sum);
	forget();
	cout<<endl;
	delete[] slr;
	delete[] idslr;
} 
} 
