#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <windows.h>

void welcome();
void create(int matrix[50][50],int n);
void display(int matrix[50][50],int n);
void play(int matrix[50][50],int n);
void findingWhite(int matrix[50][50],int usermatrix[50][50],int n,int x,int y);
void Message(int usermatrix[50][50],int n,int result);
int moves=-1,bomb,kodi;

void main()
{
    int n,matrix[50][50]={0};
    welcome(); 
    scanf("%d",&n);
    n=(n==1)?8:(n==2)?16:24;
    create(matrix,n);
    play(matrix,n);
    
}

void welcome()
{
    char name[]="MINE SWEEPER";
    int i;
    system("CLS");
    printf("\n\n\n\n%*s",75,"");
    printf("%c ",2);
    for(i=0;name[i]!='\0';i++)
    {
        printf("%c",name[i]);
        sleep(1);
    }
    printf(" %c",2);
    system("CLS");
    printf("\n\n\n\n%*s",75,"");
    printf("%c %s %c",2,name,2);
    printf("\n\n\n%*s",70,"");
    printf("LOADING");
    for(i=0;i<6;i++)
    {
        printf(".");
        sleep(1);
    }
    system("CLS");
    printf("\n\n\n\n%*s",75,"");
    printf("%c %s %c",2,name,2);
    printf("\n\n\n\n%*s",70,"");
    printf(" choose game level ");
    printf("\n\n%*s",70,"");
    printf(" 1.EASY");
    printf("\n%*s",70,"");
    printf(" 2.MEDIUM");
    printf("\n%*s",70,"");
    printf(" 3.HARD\n");
}

void create(int matrix[50][50],int n)
{
    int i,j,index_i,index_j;
    bomb=(n==8)?10:(n==16)?40:100;
    kodi=bomb;
    srand(time(0));
    for(i=0;i<bomb;i++)
    {
        index_i=rand()%n,index_j=rand()%n;
        if(matrix[index_i][index_j]!=-2)
        {
            matrix[index_i][index_j]=-2;
        }
        else
        {
            if(matrix[index_i][index_j+1]!=-2)
                matrix[index_i][++index_j]=-2;
            else if(matrix[index_i][index_j-1]!=-2)
                matrix[index_i][--index_j]=-2;
            else if(matrix[index_i+1][index_j]!=-2)
                matrix[++index_i][index_j]=-2;
            else if(matrix[index_i-1][index_j]!=-2)
                matrix[--index_i][index_j]=-2;
            else if(matrix[index_i+1][index_j+1]!=-2)
                matrix[++index_i][++index_j]=-2;
            else if(matrix[index_i-1][index_j-1]!=-2)
                matrix[--index_i][--index_j]=-2;
            else if(matrix[index_i+1][index_j-1]!=-2)
                matrix[++index_i][--index_j]=-2;
            else if(matrix[index_i-1][index_j+1]!=-2)
                matrix[--index_i][++index_j]=-2;
            else
            {
                index_j+=2;
                matrix[index_i][index_j+2]=-1;
            }
                
        }
        if(matrix[index_i+1][index_j]!=-2)
            matrix[index_i+1][index_j]++;

        if(matrix[index_i][index_j+1]!=-2)
            matrix[index_i][index_j+1]++;

        if(matrix[index_i-1][index_j]!=-2)
            matrix[index_i-1][index_j]++;

        if(matrix[index_i][index_j-1]!=-2)
            matrix[index_i][index_j-1]++;

        if(matrix[index_i+1][index_j+1]!=-2)    
            matrix[index_i+1][index_j+1]++;

        if(matrix[index_i-1][index_j-1]!=-2)
            matrix[index_i-1][index_j-1]++;

        if(matrix[index_i+1][index_j-1]!=-2)    
            matrix[index_i+1][index_j-1]++;

        if(matrix[index_i-1][index_j+1]!=-2)
            matrix[index_i-1][index_j+1]++;
    }
}

void display(int matrix[50][50],int n)
{
    int i,j,lenght;
    lenght=(n==8)?65:(n==16)?50:35;
    system("CLS");
    printf("\n\n\n\n%*s",75,"");
    printf("%c MINE SWEEPER %c\n",2,2);
    printf("%*s------------------\n\n",74,"");
    printf("\n%*s",lenght+n*2,"");
    printf("Flag_Remaining : %d\n",kodi);
    printf("\n%*s",lenght+1,"");
    for(i=0;i<n;i++)
        printf(" %d  ",i);
    printf("\n\n%*s",lenght,"");
    for(i=0;i<n;i++)
        printf("****");
    printf("*\n");
    for(i=0;i<n;i++)
    {
        printf("%*d ",lenght-2,i);
        printf("%*s",1,"");
        for(j=0;j<n;j++)
        {
            printf("| ");
            if(matrix[i][j]==0)
                printf("  ");
            else if(matrix[i][j]==-1)
                printf("%c ",177);
            else if(matrix[i][j]==-2)
                printf("%c ",149);
            else if(matrix[i][j]==-3)
                printf("|%c",16);
            else
                printf("%d ",matrix[i][j]);
        }
        printf("|\n");
        printf("%*s",lenght,"");
        for(j=0;j<n;j++)
            printf("****");
        printf("*\n");
    }
    
}

void play(int matrix[50][50],int n)
{
    int usermatrix[50][50],i,j,x,y,flag;
    memset(usermatrix,-1,sizeof(int)*50*50);
    while(1)
    {
    
        display(usermatrix,n);
        printf("enter the co-ordinates : \n");
        scanf("%d %d",&x,&y);
        printf("\nwant to flag/removeFlag (yes-1 & no-0)\n");
        scanf("%d",&flag);
        if(flag && (usermatrix[x][y]==-1||usermatrix[x][y]==-3))
        {
            if(usermatrix[x][y]==-1)
                usermatrix[x][y]=-3,kodi--;
            else
                usermatrix[x][y]=-1,kodi++;
            //usermatrix[x][y]=(usermatrix[x][y]==-1)?-3:-1;
        }
        else if(!flag)
        {
            if(x>=0&&x<n&&y>=0&&y<n&&usermatrix[x][y]!=-3)
                findingWhite(matrix,usermatrix,n,x,y);
        }
        if(moves==n*n)
           break;
        else if(moves==n*n-bomb-1)
        {
            Message(usermatrix,n,1);
            break;
        } 
        sleep(1);
    }
}

void findingWhite(int matrix[50][50],int usermatrix[50][50],int n,int x,int y)
{
    if(matrix[x][y]==0 && usermatrix[x][y]==-1)
    {
        usermatrix[x][y]=matrix[x][y];
        moves++;
        if(x+1<n)
            findingWhite(matrix,usermatrix,n,x+1,y);
        
        if(x-1>=0)
            findingWhite(matrix,usermatrix,n,x-1,y);
        
        if(y+1<n)
            findingWhite(matrix,usermatrix,n,x,y+1);

        if(y-1>=0)
            findingWhite(matrix,usermatrix,n,x,y-1);

        if(x-1>=0 && y-1>=0)
            findingWhite(matrix,usermatrix,n,x-1,y-1);
        
        if(x+1<n && y+1<n)
            findingWhite(matrix,usermatrix,n,x+1,y+1);

        if(x-1>=0 && y+1<n)
            findingWhite(matrix,usermatrix,n,x-1,y+1);

        if(x+1<n && y-1>=0)
            findingWhite(matrix,usermatrix,n,x+1,y-1);
    }
    else if(matrix[x][y]!=-2 && usermatrix[x][y]==-1)
    {
        usermatrix[x][y]=matrix[x][y];
        moves++;
    }
    else if(matrix[x][y]==-2)
    {
        printf("\n\n%*s",70,"");
        printf("Stepped On BomB \n");
        sleep(2);
        moves=n*n;
        Message(matrix,n,0);
    }    
}

void Message(int usermatrix[50][50],int n,int result)
{
    display(usermatrix,n);
    printf("\n\n\n%*s",65,"");
    char message1[]="Congrats You Won The Game",message2[]="Better Luck Next Time Buddy";
    int i;
    for(i=0;message1[i]!='\0'&&result;i++)
    {
        printf("%c",message1[i]);
        if(message1[i]==' ')
            sleep(1);
    }
    for(i=0;message2[i]!='\0'&&!result;i++)
    {
        printf("%c",message2[i]);
        if(message2[i]==' ')
            sleep(1);
    }
    printf(" %c-%c",3,3);
}