#include <stdio.h>  
#include <dirent.h>  
#include <stdlib.h>  
#include <iostream>
#include <string.h>
#include <unistd.h>
#include <sstream>
#include<sys/wait.h>
#include<vector>

using namespace std;

int split(string s1,vector<string>&v1)		// 解析輸入的字串s1
{
	string temp="";
	s1=s1+' ';
	for(int i = 0 ; i <s1.size();i++)		// 將輸入的字串過濾掉空白，存入暫存區temp，再將temp存入v1（s2），最後清除temp內容
	{         
		if(s1[i]!=' ')
		{
			temp=temp+s1[i];
		}
		else 
			if(temp.size()!=0)
			{
				v1.push_back(temp);
				temp.erase();
			}
	}
	return 0;
}

int process(vector<string>v2)
{
	char **argv=new char*[v2.size()];
	argv[v2.size()]=0;
	for(int i = 0 ; i<v2.size() ; i++)
	{
		argv[i]=new char [v2[i].size()];
		for(int j = 0 ; j<v2[i].size();j++)		//將指令切割為二維型態，argv[0]放置cd,exit,ls等指令，argv[1]放置路徑,-al等指令
		{
			argv[i][j]=v2[i][j];
		}
	}
	if(v2[0]=="cd")								//如果使用者輸入cd，目前的工作目錄將改為v2[1]的內容
	{
		chdir(v2[1].c_str());
		return 0;
	}
	if(v2[0]=="exit")							//如果使用者輸入exit，印出ByeBye!!並以正常狀態退出程式
	{
		cout<<"ByeBye!!"<<endl;
		exit(0);
	}
	else
	{
		int pid;								//pid是為了讓OS Kernel辨識每個Process
		pid=fork();								//用fork()產生Child Process
		if(pid==0)								//若pid等於0，執行execvp函數
		{										//agrv[0]表示要啟動的程序名稱，agrv表示啟動程序所帶的參數
			execvp(argv[0],argv);
			exit(0);
		}
		else									//若pid不等於0，就等待Process執行完畢
		{     
			int child;
			wait(&child);
		}
		return 0;
		}
}

int main()
{
	char buf[80];
    	string s1;
    	vector<string>s2;

	while(true)
	{
	     getcwd(buf, sizeof(buf));
	     cout<<"1033357_hw2"<<buf<<"> ";
	     getline(cin,s1);	//讀取使用者輸入的命令提示字元，並存入s1

	     if(cin.eof())		//如果讀到結尾（End Of File）
	     {
	       cin.clear();		//清除cin
	       cout<<endl;
	     }
	       split(s1,s2);	//傳送命令到split函式，解析字串
	       
	       process(s2);		//執行命令
	       s1.clear();		//清除字串內容
	       s2.clear();     	//清除vector內容
	}
	return 0;
}