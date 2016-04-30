
%{
/*this is yacc program */

#include<stdio.h>
#include<math.h>
%}
%token number
%%

S:E { printf("The result is %d \n\n",$1);}
 ;
E:number{$$=DEC($1);}
 ;
%%
int main()
{
printf("enter a binary number :");
yyparse();
}
yyerror()
{
printf("error \n");
}
float DEC(int x)
{
    float ans,bin=x,frac,fun=0.0,a;
int sum=0,dec,i=0,rem,b,j=1;
dec=bin;
frac=bin-dec;
while(dec!=0)
{
rem=dec%10;
dec=dec/10;
sum=sum+(rem*pow(2,(i++)));
}
while(frac!=0.000)
{
a=10*frac;
b=a;
fun=fun+(b*(1/pow(2,(j++))));
frac=a-b;
}
ans=sum+fun;
return (ans);
}

