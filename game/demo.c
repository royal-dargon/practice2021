#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Game();
void ShowChess(int p[3][3]);
int Judgement(int p[3][3],int i,int j,int k);

int main()
{
    int i = 0;
    while(1)
    {
        printf("1.开始游戏\n");
        printf("2.结束游戏\n");
        printf("请输入您要进行的操作\n");
        scanf("%d",&i);
        if(i == 1)
        {
            Game();
        }
        else if(i == 2)
        {
            break;
        }
    }
    return 1;
}

void Game()
{
    int arr[3][3] = {0} ;
    int win = 0;
    int i,j;
    int m,n;
    int count = 0;
    ShowChess(arr);
    while(win == 0)
    {
        printf("请输入玩家要输入的坐标(左上角是（0,0）,右下角是（2，2）)：");
        scanf("%d %d",&i,&j);
        while(arr[i][j] == 1 || arr[i][j] == 2)
        {
            printf("该位置已经被下请重新选择!\n");
            scanf("%d %d",&i,&j);
        }
        arr[i][j] = 1;
        count ++;
        ShowChess(arr);
        win = Judgement(arr,i,j,1);
        if(win == 1)
        {
            printf("恭喜你战胜人工智障\n");
            break;
        }
        if(count == 5)
        {
            printf("平局\n");
            break;
        }
        m = rand() % 3;
        n = rand() % 3;
        while(arr[m][n] == 1 || arr[m][n] == 2)
        {
            m = rand() % 3;
            n = rand() % 3;
        }
        //printf("%d %d",m,n);
        arr[m][n] = 2;
        ShowChess(arr); 
        win = Judgement(arr,m,n,2);
        if(win == 2)
        {
            printf("您遗憾的输给人工智障\n");
        }
    }
}

void ShowChess(int p[3][3])
{
    int i ,j;
    printf("+---+---+---+\n");
    for(i = 0;i < 3;i ++)
    {
        for(j = 0;j < 3;j ++)
        {
            printf("| ");
            if(p[i][j] == 0)
            {
                printf("  ");
            }
            else if(p[i][j] == 1)
            {
                printf("* ");
            }
            else
            {
                printf("? ");
            }   
        }
        printf("|\n");
        printf("+---+---+---+\n");
    }
}

int Judgement(int p[3][3],int i,int j,int k)
{
    int m,n;
    int flag1 = 1;
    int flag2 = 1;
    int flag3 = 1;
    int flag4 = 1;
    for(m = 0;m < 3;m ++)
    {
        if(p[i][m] != k)
        {
            flag1 = 0;
        }
    }
  
    if(flag1 == 1)
    {
        return k;
    }
    for(n = 0;n < 3;n ++)
    {
        if(p[n][j] != k)
        {
            flag2 = 0;
        }
    }
    if(flag2 == 1)
    {
        return k;
    }
    n = 0;
    for(m = 0;m < 3;m ++)
    {
        if(p[m][n] != k)
        {
            flag3 = 0;
        }
        n ++;
    }
    if(flag3 == 1)
    {
        return k;
    }
    n = 2;
    for(m = 0;m < 3;m ++)
    {
        if(p[m][n] != k)
        {
            flag4 = 0;
        }
        n --;
    }
    //printf("%d",flag4);
    if(flag4 == 1)
    {
        return k;
    }
    return 0;
}