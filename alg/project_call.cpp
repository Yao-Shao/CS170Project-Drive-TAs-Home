#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<cstdio>
#include<string>
#include<cstdlib>
using namespace std;

int main()
{
	for(int index1=1;index1<=366;index1++) {
		for(int index2=50;index2<=200;index2*=2) {
			char c[8]; 
			sprintf(c, "%d", index1); 

			string s1(c);
			s1 += "_";
			sprintf(c, "%d", index2); 
			string s2(c);
			s1 += s2;
		
			s2 = s1;
			s1+=".in";
			s2+=".out";
			
//			cout<<"s1:"<<s1.c_str()<<endl;
//			cout<<"s2:"<<s2<<endl;
			
			string s;
			s1 = "../inputs/" + s1;
			s2 = "../outputs/" + s2;
			s = "project.exe " + s1 + " " + s2;
			cout<<s.c_str()<<endl;
			system(s.c_str());
		}
	}

	return 0;
}
