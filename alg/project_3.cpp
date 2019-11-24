#include<cstdio>
#include<algorithm>
#include<string>
#include<iostream>
#include<cstring>
#include<cstdlib>
#include<vector>
#include<ctime>

// remember to comment
//#define _DEBUG
//#define _DEBUG_LENGTH_PRINT

using namespace std;

int L, H;
const int maxl = 200 + 10;

string locations[maxl];
string homes[maxl];
int index[maxl];

string start_point;
string temp;

double adj[maxl][maxl];
double mid[maxl][maxl];
vector<int> path[maxl][maxl];

int belong_to[maxl];

vector<int> circle;
vector<int> my_ans;
double res;

int drop_off_location[maxl]; 

void dfs(int t1,int t2,int index_i,int index_j,bool is_first) {
	if(mid[index_i][index_j]==0) {
		if(is_first) {
			path[t1][t2].push_back(index_i);
		}
		path[t1][t2].push_back(index_j);
	}
	else {
		dfs(t1,t2,index_i,mid[index_i][index_j],is_first);	
		dfs(t1,t2,mid[index_i][index_j],index_j,false);	
	}
}

double get_length(vector<int> v) {
	double res=0.0;
	
	for(size_t i=1;i<v.size();i++) {
		res+=adj[v[i-1]][v[i]];
//		if(temp_bool)
//			cout<<"tt "<<res<<endl;
	}
	
	res+=adj[v[v.size()-1]][v[0]];
	return res;
}

void first_generate() {
	circle.clear();
	for(int i=0;i<=H;i++)
		circle.push_back(index[i]);
//	res=get_length(circle);
//	my_ans = circle;
	for(int iter=0;iter<10000;iter++) {
		for(int i=0;i<=H;i++) {
			int j = rand()%(H+1);
			swap(circle[i],circle[j]);	
		}
		double new_res=get_length(circle);
		if(new_res<res || iter==0) {
			res=new_res;
			my_ans.clear();
			for(size_t i=0;i<circle.size();i++) {
				my_ans.push_back(circle[i]);	
			}
		}
	}
}

double e=1e-16, at=0.99999999, T=1.0;
const int max_iter = 200000;

void solve() {
	int iter_times = max_iter;
	while(iter_times--) {
		circle = my_ans;
		int k1=rand()%(H+1);
		int k2=rand()%(H+1);
		if(k1==k2) 
			continue;
		swap(circle[k1],circle[k2]);
		double df = get_length(circle) - res;
		double p = rand()%10000/10000.0;
		if(df<0) {
			my_ans = circle;
			res = get_length(circle);
		}
		else if(exp(-df/T)>p) {
			my_ans = circle;
			res = get_length(circle);
		}
		T*=at;
		if(T<e) 
			break;
	}
}

vector<int> to_full(vector<int> v) {
	int start_index;
	for(size_t i=0;i<v.size();i++) {
		if(v[i]==index[0]) {
			start_index = i;
			break;	
		}
	}
	
	vector<int> ret;
	ret.clear();
	
	for(size_t i=start_index+1;i<v.size();i++) {
		for(size_t j=0;j<path[v[i-1]][v[i]].size();j++) {
			if(j==0) {
				if(ret.empty()) 
					ret.push_back(path[v[i-1]][v[i]][0]);
			}
			else {
				ret.push_back(path[v[i-1]][v[i]][j]);	
			}
		}
	}
	
	for(size_t j=0;j<path[v[v.size()-1]][v[0]].size();j++) {
		if(j==0) {
			if(ret.empty()) 
				ret.push_back(path[v[v.size()-1]][v[0]][0]);
		}
		else {
			ret.push_back(path[v[v.size()-1]][v[0]][j]);	
		}
	}
	
	for(int i=1;i<=start_index;i++) {
		for(size_t j=0;j<path[v[i-1]][v[i]].size();j++) {
			if(j==0) {
				if(ret.empty()) 
					ret.push_back(path[v[i-1]][v[i]][0]);
			}
			else {
				ret.push_back(path[v[i-1]][v[i]][j]);	
			}
		}
	}
	
	return ret;
}

void to_name(vector<int> full_v) {
//	vector<int> full_v = to_full(v);
	cout<<locations[full_v[0]];	
	for(size_t i=1;i<full_v.size();i++) {
		cout<<" "<<locations[full_v[i]];	
	}
	cout<<endl;
}

void show_drop_off(int drop_off[]) {
	bool used[maxl];
	int drop_off_cnt = 0;
	vector<int> TAs[maxl];
	
	memset(used,0,sizeof(used));
	
	for(int i=1;i<=L;i++) 
	if(belong_to[i]>0) {
		if(!used[drop_off[i]])
		{
//			printf("ttt %d\n",drop_off[i]);
			used[drop_off[i]]=true;
			drop_off_cnt ++;
		}	
		TAs[drop_off[i]].push_back(i); 
	}
	
	cout<<drop_off_cnt<<endl;
	for(int i=1;i<=L;i++)
		if(used[i]==true) {
			cout<<locations[i];
			for(size_t j=0;j<TAs[i].size();j++) {
				cout<<" "<<locations[TAs[i][j]];
			}
			cout<<endl;
		}
}

int main() {
	// 初始化 
	freopen("50.in","r",stdin);
	freopen("50.out","w",stdout);
	srand(time(0));
	
	// 读入 
	cin>>L;
	cin>>H;
	for(int i=1;i<=L;i++) {
		cin>>locations[i];
		belong_to[i] = -1;
	}
	
	// 保留home的下标 
	for(int i=1;i<=H;i++) {
		cin>>homes[i];	
		for(int j=1;j<=L;j++) {
			if(homes[i].compare(locations[j])==0) {
				index[i] = j;
				belong_to[j] = i;
				break;
			}
		}
	}
		 
	// 保留初始点下标 
	cin>>start_point;
	for(int j=1;j<=L;j++) {
		if(start_point.compare(locations[j])==0) {
			index[0] = j;
			belong_to[j] = 0;
			break;
		}
	}
	
		
	for(int i=1;i<=L;i++) {
		for(int j=1;j<=L;j++) {
			cin >> temp;	
			if(temp[0]=='x') {
				adj[i][j]=-1;
			}
			else {
				adj[i][j]=atof(temp.c_str());
			}
		}
	}
	
	
	#ifdef _DEBUG
		printf("read adj matrix\n");
		for(int i=1;i<=L;i++)
		{
			for(int j=1;j<=L;j++)
			{
				printf("%f ",adj[i][j]);	
			}
			printf("\n");
		}
		printf("\n");
	#endif

	
	memset(mid,0,sizeof(mid));
	for(int i=1;i<=L;i++)
		adj[i][i]=0;
	


	for(int k=1;k<=L;k++)
	for(int i=1;i<=L;i++)
	for(int j=1;j<=L;j++) {
		if(adj[i][k]!=-1 && adj[k][j]!=-1) {
			if(adj[i][j]==-1 || adj[i][j]>adj[i][k]+adj[k][j])
			{
				adj[i][j]=adj[i][k]+adj[k][j];
				mid[i][j]=k;
			}
		}
	}
	
	#ifdef _DEBUG
		printf("read adj matrix\n");
		for(int i=1;i<=L;i++)
		for(int j=1;j<=L;j++)	{
			cout<<"From:"<<i<<" "<<j<<endl;
			cout<<adj[i][j]<<" ";
			cout<<endl;
		}
	#endif
 
//	int index_i, index_j;
//	for(int i=0;i<=H;i++)
//	for(int j=0;j<=H;j++) {
//		index_i = index[i];
//		index_j = index[j];
//		dfs(index_i,index_j,index_i,index_j,true);
//		//cout<<"From:"<<index_i<<" "<<index_j<<endl;
//		//for(size_t t=0;t<path[index_i][index_j].size();t++)
//		//	cout<<path[index_i][index_j][t]<<" ";
//		//cout<<endl;
//	}

	int index_i, index_j;
	for(int i=0;i<=L;i++)
	for(int j=0;j<=L;j++) {
		index_i = i;
		index_j = j;
		dfs(index_i,index_j,index_i,index_j,true);
//		cout<<"From:"<<index_i<<" "<<index_j<<endl;
//		for(size_t t=0;t<path[index_i][index_j].size();t++)
//			cout<<path[index_i][index_j][t]<<" ";
//		cout<<endl;
	}
	
	
	first_generate();
//	for(size_t i=0;i<my_ans.size();i++)
//		printf("%d ",my_ans[i]);
//	printf("\n");
	
	solve();	
//	for(size_t i=0;i<my_ans.size();i++)
//		printf("%d ",my_ans[i]);
//	printf("\n");
//		
	my_ans=to_full(my_ans);
	
	#ifdef _DEBUG 	
		for(size_t i=0;i<my_ans.size();i++)
			printf("%d ",my_ans[i]);
		printf("\n");
		
		to_name(my_ans);
		
	#endif
	
	#ifdef _DEBUG_LENGTH_PRINT
		cout<<"1:"<<get_length(my_ans)<<endl;
	#endif 
	
	for(int i=1;i<=L;i++) {
		if(belong_to[i]>0)
		drop_off_location[i]=i;
	}
	
	#ifdef _DEBUG 	
		show_drop_off(drop_off_location);
	#endif
	
	bool flag = true;
	vector<int> S;
//	int index_in_path1;
//	int index_in_path2;
	res=get_length(my_ans);
	while(flag) {
		flag=false;
		S.clear();
		for(size_t i=0;i<my_ans.size()-1;i++) {
			if(belong_to[my_ans[i]]!=-1) {
				S.push_back(i);
			}
		}
//		cout<<" "<<endl;
		for(size_t i=2;i<S.size();i++) {
			int best_k=0;
			double best_res = res;
			for(int k=1;k<=L;k++)
//			if(k!=my_ans[S[i-2]] && k!=my_ans[S[i-1]] && k!=my_ans[S[i]]) 
			if(k!=my_ans[S[i-1]])
			{
				if(res-adj[my_ans[S[i-2]]][my_ans[S[i-1]]]-adj[my_ans[S[i-1]]][my_ans[S[i]]] \
				+adj[my_ans[S[i-2]]][k] + adj[k][my_ans[S[i]]] + 1.5*adj[k][my_ans[S[i-1]]]<best_res) {
					best_res = res-adj[my_ans[S[i-2]]][my_ans[S[i-1]]]-adj[my_ans[S[i-1]]][my_ans[S[i]]] \
						+adj[my_ans[S[i-2]]][k] + adj[k][my_ans[S[i]]] + 1.5*adj[k][my_ans[S[i-1]]];
					best_k = k;				
//					cout<<" asdasd"<<my_ans[S[i-2]]<<" "<<my_ans[S[i-1]]<<" "<<my_ans[S[i-2]]<<" "<<i<<endl;
//					printf("ttt %d %d %d\n",my_ans[S[i-1]],k,drop_off_location[my_ans[S[i-1]]]);
//					printf("ttt %d %d %d\n",my_ans[S[i-1]],k,drop_off_location[my_ans[S[i-1]]]);
				} 
			}
			
			if(best_k!=0) {
				drop_off_location[my_ans[S[i-1]]]=best_k;
				my_ans.erase(my_ans.begin()+S[i-2]+1);
				if(my_ans[S[i-2]+1]==my_ans[S[i-2]]) {
					my_ans.erase(my_ans.begin()+S[i-2]+1);	
				}

//				to_name(my_ans);			
//				show_drop_off(drop_off_location);
				res = best_res;
//				cout<<"res:"<<best_res<<endl;
			
				flag = true;
				break;
			}	
		}
	}
	
	to_name(my_ans);
	
	for(int i=1;i<=L;i++) {
		if(belong_to[i]>0) {
			int drop_temp = -1;
			double best_drop = 0.0;
//			drop_off_location[i];
			for(size_t j=0;j<my_ans.size();j++) {
				if(drop_temp==-1 || adj[i][my_ans[j]]<best_drop) {
					drop_temp = my_ans[j];
					best_drop = adj[i][my_ans[j]];
				}
			}
			drop_off_location[i]=drop_temp;
		}
	}
	
	show_drop_off(drop_off_location);
	#ifdef _DEBUG_LENGTH_PRINT 	
		cout<<"2:"<<get_length(my_ans)<<endl;
	#endif
	
	
	return 0;	
}

/*
7
4
Soda Dwinelle Wheeler Campanile Cory RSF Barrows
Wheeler Campanile Cory RSF
Soda
x 1 x 1 x x 1
1 x x 1 x x x
x x x 1 x x x
1 1 1 x 1 1 1
x x x 1 x x x
x x x 1 x x x
1 x x 1 x x x
*/
