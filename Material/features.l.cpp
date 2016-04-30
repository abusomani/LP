
inc [+]+
eql [0]*
dec [-]+


%{
        #include <stdio.h>
        #include <malloc.h>
        #include <fcntl.h>
        #define SIZE 100
        int r,c;
        int mat[100][100];
        int d[100][100];
        char D[100][100];
        int max = 0;
%}

%%
{inc}{eql}{dec} {
        printf("feature text is %s\n",yytext);
        if(max < yyleng)
                max = yyleng;
}


%%

void d_create(){
        int i,j;
        for(i=0;i<r;i++){
                for(j=0;j<c-1;j++){
                        d[i][j] = mat[i][j+1] - mat[i][j];
                }
        }
}


void D_create(){
        int i,j;
        for(i=0;i<r;i++){
                for(j=0;j<c-1;j++){
                        if(d[i][j] > 0)
                                D[i][j] = '+';
                        else if(d[i][j] == 0)
                                D[i][j] = '0';
                        else
                                D[i][j] = '-';
                }
        }
}


void print(){
        int i,j;
        printf("Matrix is :\n");
        for(i=0;i<r;i++){
                for(j=0;j<c;j++)
                        printf("%d ",mat[i][j]);
                printf("\n");
        }

        printf("dM matrix is :\n");
        for(i=0;i<r;i++){
                for(j=0;j<c-1;j++)
                        printf("%d ",d[i][j]);
                printf("\n");
        }

        FILE* fd  = fopen("dm.txt","w");
        printf("dM` matrix is :\n");
        for(i=0;i<r;i++){
                for(j=0;j<c-1;j++){
                        printf("%c ",D[i][j]);
                        fprintf(fd,&D[i][j]);
                }
                printf("\n");
                fprintf(fd,"\n");
        }
}



int main(){
        //yyin = fopen("matrix.txt","r");
        printf("row col : ");
        scanf("%d %d",&r,&c);

        //printf("%d %d \n",r,c);

        int i,j;
        printf("Enter %d numbers\n",r*c);
        for(i=0;i<r;i++)
                for(j=0;j<c;j++)
                        scanf("%d",&mat[i][j]);

        d_create();
        D_create();
        print();
        yyin = fopen("dm.txt","r");
        yylex();
        //yylex1();
        printf("maximum feature is %d\n",max);
}


