#include<stdio.h>

int arr[30] = { 0 };

void Try();

int main()
{
	int i;
	for (i = 0; i < 30; i++)
	{
		arr[i] = 1;
	}
	Try();
	return 0;
}

void Try()
{
	int k = 0;
	int temp = 0;
	int count = 0;
	while (1)
	{
		k++;
		if (count == 15)
		{
			break;
		}
		if (k == 9)
		{
			if (arr[temp] == 1)
			{
				arr[temp] = 0;
				printf("%dÏÂ´¬\n", temp + 1);
				count++;
				k = 0;
			}
			else {
				k = k - 1;
			}
		}
		temp++;
		if (temp == 30)
		{
			temp = 0;
		}
	}
}