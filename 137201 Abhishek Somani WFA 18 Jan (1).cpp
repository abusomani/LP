/*
137201
Abhishek Somani
CSE 'B'
*/

//WFA program
//ASSUMPTION OF QUADRANTS

/*
*************************
*			*			*
*			*			*
*	  3		*	  2 	*
*			*			*
*			*			*
*************************
*			*			*
*	  		*	 		*
*	  0		*	  1		*
*			*			*
*			*			*
*************************
*/

#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define MAX 105
vector <ll> V;
int n;
float A[4][MAX][MAX];
double F[MAX];
int Identity[MAX];
int count = 0;

struct state{
	int no;
	int m;
	float S[MAX][MAX];
	state *next;
};

state *state1;

float check(state *t1,state *t2)
{
	state *t3 = new (state);
	int r = t1->m/t2->m; // ratio of size of original and the divided one
	int e = 0;
	float r1 = 0;
	
	for(int i=0; i<r;i++)
	{
		for(int j=0;j<r;j++)
		{
			r1 += t1->S[i][j]; //Sum of elements of original user matrix
		}
	}
	
	float r2 = r1/t2->S[0][0],r3;
	
	for(int i=0;i<t2->m;i++)
	{
		for(int j=0;j<t2->m;j++)
		{
			r1 = 0;
			//Sum of elements of matrix in the specific quadrant 
			for(int k=i*r; k <(i+1)*r;k++)
			{
				for(int l=j*r;l<(j+1)*r;l++)
				{
					r1 += t1->S[k][l];
				}
			}
			
			r3 = r1/t2->S[i][j];
			
			if(r3 != r2)
			{
				e = 1;
				break;
			}
		}
		if(e == 1) break;
	}
	
	if(e == 1) 
	 r2 = -1;
	
	return r2;
	
	
}

state *anotherAdd(state*S,state*t,int &n){
	
	if(S->next == NULL)
	{
		S->next = new (state);
		S->next = t;
		S->next->next = NULL;
		S->next->no = S->no+1;
		n = S->no+1;
	}
	else
		S->next = anotherAdd(S->next,t,n);
	
	return S;
}

int addition(state * temp)
{
	int t;
	state1 = anotherAdd(state1,temp,t);
	temp = state1;
	
	while(temp!=NULL)
	{
		temp = temp->next;
	}
	
	return t;
}

void print(state *S)
{
	if(S == NULL)
		return ;
		
	else
	{
		cout << S->no << endl;
		
		for(int i=0; i<S->m;i++)
		{
			for(int j=0;j<S->m;j++)
			{
				cout <<S->S[i][j]<<" ";
			}
			cout<<endl;
		}
		print(S->next);
	}
}

void createwfa(state *state2)
{
	//For 2-D matrix directly sum the numbers and divide them by 4
	if(state2->m == 2)
	{
		float avg=0;
		cout<<endl<<"Final 2X2 matrix"<<endl;
		for(int i=0;i<2;i++)
		{
			for(int j=0;j<2;j++)
			{
				avg += state2->S[i][j];
				cout<<state2->S[i][j]<<" ";
			}
			cout<<endl;
		}
		avg /=4;
		
		cout<<endl<<"Average:  "<<avg<<endl;
		//Assign them to the respective quadrants as indicated above in starting
		A[0][state2->no][state2->no] =state2->S[1][0]/avg;
		A[1][state2->no][state2->no] =state2->S[1][1]/avg;
		A[2][state2->no][state2->no] =state2->S[0][1]/avg;
		A[3][state2->no][state2->no] =state2->S[0][0]/avg;
		
	}
	//If the size of matrix is greater than 2 then
	else
	{
		//New states will be made as the matrix will be broken
		state * temp,*temp1;
		
			for(int i=0;i<4;i++)
			{
				temp1 = new (state);
				temp1->next=NULL;
				temp1->m = state2->m/2;
				
				//break the matrix half in both axes i.e divide in quadrant and assign it to the new state
				if( i == 0)
				{
					for(int j=0;j<state2->m/2;j++)
					{
						for(int k=0;k<state2->m/2;k++)
						{
							temp1->S[j][k] = state2->S[j+(state2->m/2)][k+(state2->m/2)];
						}
					}
				}
				else if(i==1)
				{	
						for(int j=0;j<state2->m/2;j++)
						{
							for(int k=0;k<state2->m/2;k++)
							{
								temp1->S[j][k] = state2->S[j+(state2->m/2)][k];
							}
						}
					
				}
				else if(i==2)
				{
						for(int j=0;j<state2->m/2;j++)
							{
								for(int k=0;k<state2->m/2;k++)
								{
									temp1->S[j][k] = state2->S[j][k+(state2->m/2)];
								}
							}
				}
				
				else if( i==3)
				{
						for(int j=0;j<state2->m/2;j++)
						{
							for(int k=0;k<state2->m/2;k++)
							{
								temp1->S[j][k] = state2->S[j][k];
							}
						}
				}
			
			//Take a temp state that will be similar to the Original/Parent state
			temp = new (state);
			temp = state1;
			float t;
			
			while(temp!=NULL)
			{
				if(temp->m >= state2->m/2){
					t=check(temp,temp1);
					
					if(t == -1)
					{
						temp = temp->next;
					}
					else
					{
						A[i][state2->no][temp->no]=t;
						break;
					}
				}
			}
			if(temp==NULL)
			{
				int t1 = addition(temp1);
				temp1->no = t1;
				A[i][state2->no][t1]=1;
				createwfa(temp1);
			}
		}
	}
}

int main()
{
	
	cout << "Enter the size of the matrix\n";
	cin>>n;

	//Initializing the global matrix state.
	state1= new(state);
	state1->next=NULL;
	state1->m=n;
	state1->no=0;
	
	//Initialising the final arrays as 0 because there are no links established
	for(int i=0;i<MAX;i++)
	{
		for(int j=0;j<MAX;j++)
		{
			A[0][i][j] = A[1][i][j] = A[2][i][j] = A[3][i][j] =0;
		}
	}
	
	//Take input of user defined pixel matrix
	cout<<"Enter the matrix\n";
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			cin>>state1->S[i][j];
	
			
	createwfa(state1);
	
	int l=0;
	while(state1!=NULL)
	{
		l++;
		state1=state1->next;
	}
	
	cout<<endl;
	
	for(int i=0;i<4;i++)
	{
		cout<<"A"<<i<<endl;
		
		for(int j=0;j<l;j++){
			for(int k=0;k<l;k++)
				cout<<setw(6)<<setprecision(4)<<A[i][j][k]<<"  ";
			cout<<endl;
		}
		cout<<endl;
	}
	
	
	
	return 0;
}
