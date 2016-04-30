
%{
/*this is yacc program */
#include<stdio.h>
#include<math.h>
%}
%token number
%%

S:E { printf("The binary equivalent is %d \n\n",$1);}
 ;
E:number{$$=BIN($1);}
 ;
%%
int main()
{
printf("enter a decimal number :");
yyparse();
}
yyerror()
{
printf("error \n");
}
int BIN(int x)
{
     long int decimalNumber=x,remainder,quotient,binary_val;
int binaryNumber[100],i=1,j,digit;
quotient = decimalNumber;


    while(quotient!=0){

         binaryNumber[i++]= quotient % 2;

         quotient = quotient / 2;

    }
    for(j = i -1 ;j> 0;j--)
{
         digit=binaryNumber[j];
        binary_val=binary_val*10+digit;
}
return (binary_val);
}


