#include <stdio.h>
#include <stdlib.h>



// 墙1，箱子4，人2，目的地3，空白0
int map[10][10] = {
    {1,1,1,1,1,1,1,1,1,1},
    {1,0,0,3,1,1,0,0,0,1},
    {1,0,4,0,0,1,3,0,0,1},
    {1,0,0,1,1,1,1,0,0,1},
    {1,0,0,0,2,0,0,4,0,1},
    {1,1,1,0,0,0,0,0,0,1},
    {1,0,0,0,1,0,0,1,0,1},
    {1,0,4,0,1,4,0,1,0,1},
    {1,3,0,0,1,0,0,1,3,1},
    {1,1,1,1,1,1,1,1,1,1}
};
int x = 4;
int y = 4;

void printMap();
void Move();
int TestRes();
void moveUP();
void moveDown();
void moveLeft();
void moveRight();

int main()
{
    printf("现在即将开始的是推箱子小游戏\n");
    printMap();
    int win = 0;
    printf("now begin to move！\n");
    while(win != 1)
    {
        Move();
        // clear the flash
        system("cls");
        printMap();
        win = TestRes();
    }
    printf("win!!\n");
}

void printMap()
{
    int i,j;
    for(i = 0;i < 10;i ++)
    {
        for(j = 0;j < 10;j ++)
        {
            if(map[i][j] == 0)
            {
                printf("  ");
            }
            else if(map[i][j] == 1)
            {
                printf("■ ");
            }
            else if(map[i][j] == 2)
            {
                printf("♀ ");
            }
            else if(map[i][j] == 3)
            {
                printf("☆ ");
            }
            else
            {
                printf("□ ");
            }
        }
        printf("\n");
    }
}

void Move()
{
    char str;
    str = getchar();
    switch(str)
    {
        case 'w':moveUP(); break;
        case 's':moveDown();break;
        case 'a':moveLeft();break;
        case 'd':moveRight();break;
        default: printf("the action is invalid\n");
    }
}

int TestRes()
{
    int i,j;
    for(i = 0;i < 10;i ++)
    {
        for(j = 0;j < 10;j ++)
        {
            if(map[i][j] == 4)
            {
                return 0;
            }
        }
    }
    return 1;
}

void moveUP()
{
    if(x == 0)
    {
        printf("you can not move\n");
        return;
    }
    if(map[x-1][y] == 1 || map[x-1][y] == 3)
    {
        printf("you can move like this way！\n");
        return;
    }
    else if(map[x-1][y] == 0)
    {
        map[x][y] = 0;
        map[x-1][y] = 2;
        x = x-1;
    }
    else if(map[x-1][y] == 4)
    {
        if(map[x-2][y] == 0)
        {
            map[x-2][y] = 4;
            map[x-1][y] = 2;
            map[x][y] = 0;
            x = x - 1;
        }
        else if(map[x-2][y] == 1 || map[x-2][y] == 4)
        {
            printf("you can not do like this\n");
            return;
        }
        else if(map[x-2][y] == 3)
        {
            map[x-1][y] = 2;
            map[x][y] = 0;
            x = x -1;
        }
    }
}

void moveDown()
{
    if(x == 9)
    {
        printf("you can not do like this\n");
        return;
    }
    if(map[x+1][y] == 1 || map[x+1][y] == 3)
    {
        printf("you can move like this way！\n");
        return;
    }
    else if(map[x+1][y] == 0)
    {
        map[x][y] = 0;
        map[x+1][y] = 2;
        x = x+1;
    }
    else if(map[x+1][y] == 4)
    {
        if(map[x+2][y] == 0)
        {
            map[x+2][y] = 4;
            map[x+1][y] = 2;
            map[x][y] = 0;
            x = x + 1;
        }
        else if(map[x+2][y] == 1 || map[x+2][y] == 4)
        {
            printf("you can not do like this\n");
            return;
        }
        else if(map[x+2][y] == 3)
        {
            map[x+1][y] = 2;
            map[x][y] = 0;
            x = x + 1;
        }
    }
}

void moveLeft()
{
    if(y == 0)
    {
        printf("you can not do like this\n");
        return;
    }
    if(map[x][y-1] == 1 || map[x][y-1] == 3)
    {
        printf("you can move like this way！\n");
        return;
    }
    else if(map[x][y-1] == 0)
    {
        map[x][y] = 0;
        map[x][y-1] = 2;
        y = y-1;
    }
    else if(map[x][y-1] == 4)
    {
        if(map[x][y-2] == 0)
        {
            map[x][y-2] = 4;
            map[x][y-1] = 2;
            map[x][y] = 0;
            y = y - 1;
        }
        else if(map[x][y-2] == 1 || map[x][y-2] == 4)
        {
            printf("you can not do like this\n");
            return;
        }
        else if(map[x][y-2] == 3)
        {
            map[x][y-1] = 2;
            map[x][y] = 0;
            y = y - 1;
        }
    }
}

void moveRight()
{
    if(y == 9)
    {
        printf("you can not do like this\n");
        return;
    }
    if(map[x][y+1] == 1 || map[x][y+1] == 3)
    {
        printf("you can move like this way！\n");
        return;
    }
    else if(map[x][y+1] == 0)
    {
        map[x][y] = 0;
        map[x][y+1] = 2;
        y = y+1;
    }
    else if(map[x][y+1] == 4)
    {
        if(map[x][y+2] == 0)
        {
            map[x][y+2] = 4;
            map[x][y+1] = 2;
            map[x][y] = 0;
            y = y + 1;
        }
        else if(map[x][y+2] == 1 || map[x][y+2] == 4)
        {
            printf("you can not do like this\n");
            return;
        }
        else if(map[x][y+2] == 3)
        {
            map[x][y+1] = 2;
            map[x][y] = 0;
            y = y + 1;
        }
    }
}