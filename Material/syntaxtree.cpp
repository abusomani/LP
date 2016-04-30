#include<stdio.h>
#include<stdlib.h>
#include<cstring>
#include<string.h>
#define Blank ' '
#define Tab '\t'
#define MAX 100
 
long int pop ();
char expression[MAX], syntaxtree[MAX];
long int stack[MAX];
int top;

void push(long int symbol)
{
if(top > MAX)
{
printf("Stack overflow\n");
exit(1);
}
else
{
top=top+1;
stack[top] = symbol;
}
}
 
long int pop()
{
if (top == -1 )
{
printf("Stack underflow \n");
exit(2);
}
else
return (stack[top--]);
}
 
int white_space(char symbol)
{
if( symbol == Blank || symbol == Tab || symbol == '\0')
return 1;
else
return 0;
}
int prec(char symbol )
{
switch(symbol)
{
case '(':
return 0;
case '+':
case '-':
return 1;
case '*':
case '/':
case '%':
return 2;
case '^':
return 3;
}
} 
void expression_to_syntaxtree()
{
int i,p=0,type,precedence,len;
char next ;
stack[top]='#';
len=strlen(expression);
expression[len]='#';
for(i=0; expression[i]!='#';i++)
{
if( !white_space(expression[i]))
{
switch(expression[i])
{
case '(':
push(expression[i]);
break;
 
case ')':
while((next = pop()) != '(')
syntaxtree[p++] = next;
break;
case '+':
case '-':
case '*':
case '/':
case '%':
case '^':
precedence = prec(expression[i]);
while(stack[top]!='#' && precedence<= prec(stack[top]))
syntaxtree[p++] = pop();
push(expression[i]);
break;
default: /*if an operand comes */
syntaxtree[p++] = expression[i];
}/*End of switch */
}/*End of if */
}/*End of for */
while(stack[top]!='#')
syntaxtree[p++] = pop();
syntaxtree[p] = '\0' ;  /*End syntaxtree with'\0' to make it a string*/
}
 

 



int main()
{
long int value;
char choice='y';
//clrscr();
while(choice == 'y')
{
top = 0;
printf("Enter Expression : ");
fflush(stdin);
gets(expression);
expression_to_syntaxtree();
printf("Expression Tree Format : %s\n",syntaxtree);
printf("Want to continue(y/n) : ");
scanf("%c",&choice);
}
}
