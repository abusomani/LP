
#include<iostream>
using namespace std;
int main()
{
int iden=0,keyw=0,punct=0,opr=0,cons=0,chk=0,size,identt=0;
string keyword[]={"int","float","char","double","bool","string"};
string identifier[]={"a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z"};
string punctuation[]={",",";","(",")","{","}"};
string ident[]={"[","]"};
string operators[]={"+","-","*","/","%","!","=","&",">","<","?"};
string constant[]={"1","2","3","4","5","6","7","8","9","10"},strin[100];
int no;

cout<<"Enter a string (at the end use |)\n";
int p=0;
for(p=0;p<100;p++)
{
cin>>strin[p];
if(strin[p]=="|")
break;
}


for(int i=0;i<=p;i++)
{
for(int j=0;j<26;j++)
{
if(strin[i]==identifier[j])
iden++;
}
}
for(int i=0;i<p;i++)
{
for(int j=0;j<6;j++)
{
if(strin[i]==keyword[j])
keyw++;
}
}

for(int i=0;i<p;i++)
{
for(int j=0;j<6;j++)
{
if(strin[i]==punctuation[j])
punct++;
}
}
for(int i=0;i<p;i++)
{
for(int j=0;j<2;j++)
{
if(strin[i]==ident[j])
identt++;
}
}

for(int i=0;i<p;i++)
{
for(int j=0;j<11;j++)
{
if(strin[i]==operators[j])
opr++;
}
}

for(int i=0;i<p;i++)
{
for(int j=0;j<10;j++)
{
if(strin[i]==constant[j])
cons++;
}
}
for(int i=0;i<p;i++)
{
	if(strin[i]=="\"")
	chk++;
}
punct=punct+chk-identt;
iden=iden+(chk/2);
cons=cons-(identt/2);
cout<<"No. of identifier  "<<iden<<endl;
cout<<"No. of keyword  "<<keyw<<endl;
cout<<"No. of punctuation  "<<punct<<endl;
cout<<"No. of operators  "<<opr<<endl;
cout<<"No. of constants  "<<cons<<endl;
return 0;
}

// Each time you give input then give space like below...
// string a [ 2 ] = { " abc " , " def " } ; int b = 10 ; |

