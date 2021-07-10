#include <stdio.h>
#include <string.h>

struct Meal {
	int id;
	char name[30];
	float price;
};

struct Meal meal[5] = { 1,"炒干丝",19.9f,2,"松鼠鱼",59.9,3,"大闸蟹",108,4,"糖醋鱼",45,5,"狮子头",38 };

void Show();
int Do();
void showRes(int count);

int mealId[10] = { 0 };

int Way()
{
	Show();
	int count = Do();
	showRes(count);
	return 0;
}

void Show()
{
	int i;
	printf("今日菜品如下：\n");
	printf("\t编号\t菜名\t 价格(单位：元）\n");
	int lenth;
	lenth = sizeof(meal) / sizeof(meal[0]);
	for (i = 0; i < lenth; i++)
	{
		printf("\t%d\t%s\t %.2f\n", meal[i].id, meal[i].name, meal[i].price);
	}
}

int Do()
{
	int a;
	int id;
	int count = 0;
	printf("请输入您的操作编号(1.点餐 2.退出):");
	scanf_s("%d", &a);
	while (a != 2)
	{
		printf("请输入您菜品的编号：");
		scanf_s("%d", &id);
		mealId[count++] = id;
		printf("是否继续点餐(1.点餐 2.退出)");
		scanf_s("%d", &a);
	}
	return count;
}

void showRes(int count)
{
	int i;
	float sum = 0;
	printf("-----------------------------------------\n");
	if (count == 0)
	{
		printf("您还未点餐！\n");
		return;
	}
	printf("您的菜单如下：\n");
	printf("\t编号\t菜名\t 价格(单位：元)\n");
	for (i = 0; i < count; i++)
	{
		printf("\t%d\t%s\t %.2f\n", i + 1, meal[mealId[i] - 1].name, meal[mealId[i] - 1].price);
		sum = sum + meal[mealId[i] - 1].price;
	}
	printf("\t\t\t总计：%.2f\n", sum);
	printf("已经退出点餐系统，欢迎下次点餐！\n");
}