#include <stdio.h>
#include <string.h>

struct Meal {
	int id;
	char name[30];
	float price;
};

struct Meal meal[5] = { 1,"����˿",19.9f,2,"������",59.9,3,"��բз",108,4,"�Ǵ���",45,5,"ʨ��ͷ",38 };

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
	printf("���ղ�Ʒ���£�\n");
	printf("\t���\t����\t �۸�(��λ��Ԫ��\n");
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
	printf("���������Ĳ������(1.��� 2.�˳�):");
	scanf_s("%d", &a);
	while (a != 2)
	{
		printf("����������Ʒ�ı�ţ�");
		scanf_s("%d", &id);
		mealId[count++] = id;
		printf("�Ƿ�������(1.��� 2.�˳�)");
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
		printf("����δ��ͣ�\n");
		return;
	}
	printf("���Ĳ˵����£�\n");
	printf("\t���\t����\t �۸�(��λ��Ԫ)\n");
	for (i = 0; i < count; i++)
	{
		printf("\t%d\t%s\t %.2f\n", i + 1, meal[mealId[i] - 1].name, meal[mealId[i] - 1].price);
		sum = sum + meal[mealId[i] - 1].price;
	}
	printf("\t\t\t�ܼƣ�%.2f\n", sum);
	printf("�Ѿ��˳����ϵͳ����ӭ�´ε�ͣ�\n");
}