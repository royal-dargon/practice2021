#include <stdio.h>
#include <winsock.h>
#include <mysql.h>
#include <string.h>

void login(MYSQL* p);
void Regis(MYSQL* p);

int main()
{
	int i;

	MYSQL *con = mysql_init(0);
	if (!mysql_real_connect(con, "localhost", "root", "root", "demo", 0, 0, 0))
	{
		printf("����ʧ�ܣ�����Ϊ%s\n", mysql_error(con));
		goto exit;
	}
	printf("����������Ҫִ�еĲ���:(1.login in 2.register):");
	scanf_s("%d", &i);
	if (i == 1)
	{
		login(con);
	}
	else if (i == 2)
	{
		Regis(con);
	}
	else {
		goto exit;
	}

exit:
	return 0;
}

void login(MYSQL* p)
{
	if (mysql_query(p, "set names gbk"))
	{
		printf("�����д���:%s\n", mysql_error(p));
	}
	char name[40];
	char pwd[40];
	char temp[100];
	printf("�����ǵ������!");
	printf("�������ǳ�:\n");
	scanf("%s", name);
	printf("����������:\n");
	scanf("%s", pwd);
	sprintf(temp, "select * from stuInfo where stu_name = '%s' and user_password = '%s';",name,pwd);
	if (mysql_query(p, temp))
	{
		printf("����ʧ��\n");
		return;
	}
	MYSQL_RES *res = mysql_store_result(p);
	MYSQL_ROW row; 
	while(row = mysql_fetch_row(res))
	{
		printf("%s\t%s\t%s\n", row[2],row[3],row[4]);
		printf("��ѯ�ɹ�\n");
	}
}

void Regis(MYSQL* p)
{
	if (mysql_query(p, "set names gbk"))
	{
		printf("�����д���:%s\n", mysql_error(p));
	}
	char name[40];
	char pwd[40];
	char gender[10];
	char motto[80];
	char temp[200];
	printf("�����ǵ�½ע�ᡣ\n");
	printf("�������ǳ�:\n");
	scanf("%s",name);
	printf("����������:\n");
	scanf("%s", pwd);
	printf("�����������Ա�:\n");
	scanf("%s", gender);
	printf("���������ĸ���:\n");
	scanf("%s", motto);
	sprintf(temp, "insert into stuInfo Value(NULL,'%s','%s','%s','%s');", pwd, name, gender, motto);
	if (mysql_query(p, temp))
	{
		printf("���ʧ��!����ԭ����:%s",mysql_error(p));
		return;
	}
	printf("ע��ɹ�!\n");
}