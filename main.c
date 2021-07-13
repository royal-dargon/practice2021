#include <stdio.h>
#include <winsock.h>
#include <stdlib.h>
#include <string.h>
#include <mysql.h>

struct UserInfo {
	int id;
	char name[20];
	int role;
};

void registe(MYSQL* p)
{
	char name[20];
	int pwd;
	char temp[50];
	printf("������ע�����\n");
	printf("�������ǳ�:");
	scanf("%s",&name);
	printf("����������:");
	scanf("%d", &pwd);
	sprintf(temp, "insert into user values(NULL,'%s',%d,'0')", name, pwd);
	if (mysql_query(p, "set names gbk"))
	{
		printf("����������:%s\n", mysql_error(p));
		return;
	}
	if (mysql_query(p, temp))
	{
		printf("ע��ʧ��:%s\n", mysql_error(p));
		return;
	}
	printf("ע��ɹ�\n");
	return;
}


void login(MYSQL* pconn,struct UserInfo* temp)
{
	char uname[30];
	int upwd;

	//printf("��ӭ������������ϵͳ\n");
	printf("�������û���½ҳ��\n");

	printf("�������û�����\n");
	scanf("%s", uname);

	printf("���������룺\n");
	scanf("%d", &upwd);

	char sql[100];

	sprintf(sql, "select * from user where uname = '%s' and upwd = %d", uname, upwd);

	if (mysql_query(pconn, sql))
	{
		printf("��½ʧ��, ����Ϊ%u\n", mysql_errno(pconn));
		printf("%s\n", sql);
	}

	MYSQL_RES *res = mysql_store_result(pconn);
	int colume = mysql_num_rows(res);
	if (colume > 0)
	{
		printf("��½�ɹ�\n");
	}
	else
	{
		printf("��½ʧ��\n");
		return;
	}
	MYSQL_ROW row;
	while (row = mysql_fetch_row(res))
	{
		temp->id = atoi(row[0]);
		strcpy(temp->name, row[1]);
		temp->role = atoi(row[3]);
	}
}

void AppointMatch(MYSQL* p,int uid);
void GetAll(MYSQL* p);

void mysql(MYSQL* pconn)
{
	if (!mysql_real_connect(pconn, "localhost", "root", "root", "finalwork", 0, NULL, 0))
	{
		printf("����ʧ��,����Ϊ��%u\n", mysql_errno(pconn));
		mysql_close(pconn);
	}
	else
	{
		printf("���ӳɹ�\n");
	}

	if (mysql_query(pconn, "set names gbk"))
	{
		printf("��������,����Ϊ%u", mysql_errno(pconn));
	}
}

// �û�
//��ȡ�����б�
void GetGames(MYSQL* p);

void SearchGame(MYSQL* p);

//ǰ̨����Ա
//��������
void CreatGame(MYSQL* p);

//ԤԼ����
void AppointGame(MYSQL* p);

//�鿴�����û�ԤԼ����������
void GetAppoint(MYSQL* p);


//��Ա&��ӷ���
//�Ǽ���Ա
void RecordPlayer(MYSQL* p);

//�Ǽ��Ŷ�
void RecordTeam(MYSQL* p);

void ChangeRole(MYSQL* pconn);

int main()
{
	int i;
	struct UserInfo temp = { -1,'0',0 };
	MYSQL *pconn = mysql_init(0);
	mysql(pconn);
	printf("��ӭ������������ϵͳ\n");
	printf("����������Ҫ���еĲ���:(1.login 2.register)\n");
	scanf("%d", &i);
	if (i == 1)
	{
		login(pconn,&temp);
	}
	else
	{
		registe(pconn);
		login(pconn,&temp);
	}

	printf("%d", temp.role);
	if (temp.role == 0)
	{
		while (1) {

			int choose;
			printf("��������Ҫִ�еĲ�����\n");
			printf("1.��ȡ�����б� 2.�������� 3.ԤԼ���� 4.�˳�\n");
			scanf("%d", &choose);

			switch (choose)
			{
			case 1: GetGames(pconn); break;
			case 2: SearchGame(pconn); break;
			case 3: AppointMatch(pconn,temp.id); break;
			case 4: return 0;
			}

		}
	}

	if (temp.role == 1)
	{
		while (1) {

			int choose;
			printf("��������Ҫִ�еĲ�����\n");
			printf("1.ԤԼ���� 2.������� 3.�鿴�û�ԤԼ������ 4.�˳�\n");
			scanf("%d", &choose);


			switch (choose)
			{
			case 1: AppointGame(pconn); break;
			case 2: CreatGame(pconn); break;
			case 3: GetAppoint(pconn); break;
			case 4: return 0;
			}
		}
	}

	if (temp.role == 2)
	{
		while (1) {

			int choose;
			printf("��������Ҫִ�еĲ�����\n");
			printf("1.ԤԼ���� 2.������Ϸ 3.��ȡԤԼ������ 4.�Ǽ���Ա 5.�Ǽ���� 6.Ȩ�޹��� 7.�˳�\n");
			scanf("%d", &choose);

			switch (choose)
			{
			case 1: AppointGame(pconn); break;
			case 2: CreatGame(pconn); break;
			case 3: GetAppoint(pconn); break;
			case 4: RecordPlayer(pconn); break;
			case 5: RecordTeam(pconn); break;
			case 6: ChangeRole(pconn); break;
			case 7: return 0;
			}
		}
	}
	mysql_close(pconn);
}

void AppointGame(MYSQL* p)
{
	char temp[80];
	if (mysql_query(p, "set names gbk"))
	{
		printf("����������:%s\n",mysql_error(p));
		return;
	}
	sprintf(temp, "select * from user_game");
	if (mysql_query(p,temp))
	{
		printf("��ѯʧ��!%s\n", mysql_error(p));
		return;
	}
	MYSQL_RES * res = mysql_store_result(p);
	MYSQL_ROW row;
	printf("���\t�û����\t\t�������\t����ʱ��\n");
	while (row = mysql_fetch_row(res))
	{
		printf("%s\t%s\t\t%s\t%s\n", row[0], row[1], row[2], row[3]);
	}
	return;
}

void CreatGame(MYSQL* p)
{
	char temp[80];
	char temp1[80];
	char temp2[80];
	int id1;
	int id2;
	char name1[15];
	char name2[15];
	char place[40];
	if (mysql_query(p, "set names gbk"))
	{
		printf("����������:%s\n", mysql_error(p));
		return;
	}
	printf("�������һ֧��ӵ�����:");
	scanf("%s", &name1);
	printf("������ڶ�֧��ӵ�����:");
	scanf("%s", &name2);
	printf("����������ص�:");
	scanf("%s", &place);
	sprintf(temp1, "select * from team where tname = '%s'", name1);
	if (mysql_query(p, temp1))
	{
		printf("����ʧ��:%s\n", mysql_error(p));
		return;
	}
	MYSQL_RES * res = mysql_store_result(p);
	MYSQL_ROW row;
	int colume = mysql_num_rows(res);
	if (colume <= 0)
	{
		printf("�����������\n");
	}
	while (row = mysql_fetch_row(res))
	{
		id1 = atoi(row[0]);
	}
	sprintf(temp2, "select * from team where tname = '%s'", name2);
	if (mysql_query(p, temp2))
	{
		printf("����ʧ��:%s\n", mysql_error(p));
		return;
	}
	MYSQL_RES * res1 = mysql_store_result(p);
	MYSQL_ROW row1;
	int colume1 = mysql_num_rows(res1);
	if (colume <= 0)
	{
		printf("�����������\n");
	}
	while (row1 = mysql_fetch_row(res1))
	{
		id2 = atoi(row1[0]);
	}
	sprintf(temp, "insert into game (tidA,tidB,gplace)values(%d,%d,'%s')",id1,id2,place);
	if (mysql_query(p, temp))
	{
		printf("����ʧ��:%s\n", mysql_error(p));
		return;
	}
	printf("�����ɹ�\n");
}

void RecordPlayer(MYSQL* p)
{
	char temp[80];
	char temp1[80];
	char name[20];
	int tid;
	char tname[15];
	char motto[40];
	if (mysql_query(p, "set names gbk"))
	{
		printf("�������:%s\n", mysql_error(p));
		return;
	}
	printf("��������Ա�Ǽǽ���:\n");
	printf("��������Ҫ������Ա������");
	scanf("%s", &name);
	printf("���������Ա������ӵ�����:");
	scanf("%s", &tname);
	printf("���������Ա�ĸ���:");
	scanf("%s", &motto);
	sprintf(temp1, "select * from team where tname = '%s'", tname);
	if (mysql_query(p, temp1))
	{
		printf("����ʧ��:%s\n", mysql_error(p));
		return;
	}
	MYSQL_RES * res = mysql_store_result(p);
	MYSQL_ROW row;
	int colume = mysql_num_rows(res);
	if (colume <= 0)
	{
		printf("�����������\n");
	}
	while (row = mysql_fetch_row(res))
	{
		tid = atoi(row[0]);
	}
	sprintf(temp, "insert into player values (NULL,'%s',%d,'%s')", name, tid, motto);
	if (mysql_query(p, temp))
	{
		printf("����ʧ��!\n");
		return;
	}
	printf("�����ɹ�\n");
	return;
}

void RecordTeam(MYSQL* p)
{
	char temp[80];
	char name[20];
	char city[15];
	printf("�����Ǵ�����ӽ���\n");
	if (mysql_query(p, "set names gbk"))
	{
		printf("�������:%s\n", mysql_error(p));
		return;
	}
	printf("�����������:");
	scanf("%s", &name);
	printf("�����������������:");
	scanf("%s", &city);
	sprintf(temp, "insert into team values(NULL,'%s','%s')",name,city);
	if (mysql_query(p, temp))
	{
		printf("����ʧ��!%s\n", mysql_error(p));
		return;
	}
	printf("�����ɹ�\n");
	return;
}

void AppointMatch(MYSQL* p,int uid)
{
	int id;
	char temp[80];
	printf("������ԤԼ�����Ľ���\n");
	GetGames(p);
	printf("��������ҪԤԼ��������ID��");
	scanf("%d", &id);
	sprintf(temp, "insert into user_game values(NULL,%d,%d,NULL)", uid, id);
	if (mysql_query(p, "set names gbk"))
	{
		printf("�������:%s\n", mysql_error(p));
		return;
	}
	if (mysql_query(p, temp))
	{
		printf("ԤԼʧ��:%s\n", mysql_error(p));
		return;
	}
	printf("ԤԼ�ɹ�\n");
}

void GetGames(MYSQL* p)
{
	char temp1[70];
	//char name1[20];
	//char name2[20];
	int id1, id2;
	printf("�����Ǳ�����Ϣ\n");
	if (mysql_query(p, "set names gbk"))
	{
		printf("�������:%s\n", mysql_error(p));
		return;
	}
	char temp[80];
	sprintf(temp, "select * from game");
	if (mysql_query(p, temp))
	{
		printf("��ѯʧ��!%s\n", mysql_error(p));
		return;
	}
	MYSQL_RES* res = mysql_store_result(p);
	MYSQL_ROW row;
	printf("���\t���A\t\t���B\t\t�ص�\tʱ��\n");
	while (row = mysql_fetch_row(res))
	{
		printf("%s\t", row[0]);
		id1 = atoi(row[1]);
		id2 = atoi(row[2]);
		sprintf(temp1, "select * from team where tid = %d", id1);
		if (mysql_query(p, temp1))
		{
			printf("��ѯʧ��:%s\n", mysql_error(p));
			return;
		}
		MYSQL_RES * res1 = mysql_store_result(p);
		MYSQL_ROW row1;
		int colume = mysql_num_rows(res1);
		if (colume <= 0)
		{
			printf("�����������\n");
		}
		while (row1 = mysql_fetch_row(res1))
		{
			printf("%s\t\t",row1[1]);
		}
		sprintf(temp1, "select * from team where tid = %d", id2);
		if (mysql_query(p, temp1))
		{
			printf("����ʧ��:%s\n", mysql_error(p));
			return;
		}
		MYSQL_RES * res2 = mysql_store_result(p);
		MYSQL_ROW row2;
		int colume1 = mysql_num_rows(res);
		if (colume1 <= 0)
		{
			printf("�����������\n");
		}
		while (row2 = mysql_fetch_row(res2))
		{
			printf("%s\t", row2[1]);
		}
		printf("%s\t%s\n", row[3], row[4]);
	}
}

void SearchGame(MYSQL* p)
{
	char temp[80];
	char temp1[80];
	char temp2[80];
	char name[20];
	int tid;
	printf("��������������\n");
	if (mysql_query(p, "set names gbk"))
	{
		printf("�������:%s\n", mysql_error(p));
		return;
	}
	printf("��������Ҫ������ӵ�����:");
	scanf("%s", &name);
	sprintf(temp, "select * from team where tname = '%s' ", name);
	if (mysql_query(p, temp))
	{
		printf("����ʧ��\n");
	}
	MYSQL_RES* res = mysql_store_result(p);
	MYSQL_ROW row;
	int colume = mysql_num_rows(res);
	if (colume <= 0)
	{
		printf("�������������߲�����\n");
		return;
	}
	while (row = mysql_fetch_row(res))
	{
		tid = atoi(row[0]);
	}
	sprintf(temp, "select * from game where tidA = %d or tidB = %d ", tid,tid);
	if (mysql_query(p, temp))
	{
		printf("����ʧ��\n");
	}
	MYSQL_RES* res1 = mysql_store_result(p);
	MYSQL_ROW row1;
	int colume1 = mysql_num_rows(res1);
	if (colume1 <= 0)
	{
		printf("�����ڱ���\n");
		return;
	}
	int id1, id2;
	printf("���\t���A\t\t���B\t\t�ص�\tʱ��\n");
	while (row1 = mysql_fetch_row(res1))
	{
		printf("%s\t", row1[0]);
		id1 = atoi(row1[1]);
		id2 = atoi(row1[2]);
		sprintf(temp1, "select * from team where tid = %d", id1);
		if (mysql_query(p, temp1))
		{
			printf("��ѯʧ��:%s\n", mysql_error(p));
			return;
		}
		MYSQL_RES * res2 = mysql_store_result(p);
		MYSQL_ROW row2;
		int colume2 = mysql_num_rows(res1);
		if (colume2 <= 0)
		{
			printf("�����������\n");
		}
		while (row2 = mysql_fetch_row(res2))
		{
			printf("%s\t\t", row2[1]);
		}
		sprintf(temp2, "select * from team where tid = %d", id2);
		if (mysql_query(p, temp2))
		{
			printf("����ʧ��:%s\n", mysql_error(p));
			return;
		}
		MYSQL_RES * res3 = mysql_store_result(p);
		MYSQL_ROW row3;
		int colume3 = mysql_num_rows(res);
		if (colume3 <= 0)
		{
			printf("�����������\n");
		}
		while (row3 = mysql_fetch_row(res3))
		{
			printf("%s\t", row3[1]);
		}
		printf("%s\t%s\n", row1[3], row1[4]);
	}
}

void GetAppoint(MYSQL* p)
{
	int i = 0;
	char temp[80];
	printf("�����ǲ�ѯԤ����Ϣ�Ľ���\n");
	if (mysql_query(p, "set names gbk"))
	{
		printf("��������:%s\n", mysql_error(p));
		return;
	}
	printf("��������Ҫ���еĲ���(1.��ѯ���� 2.��ѯָ��):");
	scanf("%d", &i);
	if (i == 1)
	{
		sprintf(temp, "select * from user_game");
		if (mysql_query(p, temp))
		{
			printf("��ѯʧ��:%s\n", mysql_error(p));
			return;
		}
		MYSQL_RES* res = mysql_store_result(p);
		MYSQL_ROW row;
		printf("��ѯ���\n");
		printf("���\t�û��ǳ�\t����A����\t����B����\tʱ��\n");
		while (row = mysql_fetch_row(res))
		{
			printf("%s\t", row[0]);
			int uid = atoi(row[1]);
			int gid = atoi(row[2]);
			char temp1[80];
			char temp2[80];
			sprintf(temp1, "select uname from user where uid = %d", uid);
			if (mysql_query(p, temp1))
			{
				printf("��ѯʧ��!%s\n", mysql_error(p));
				return;
			}
			MYSQL_RES* res1 = mysql_store_result(p);
			MYSQL_ROW row1;
			while (row1 = mysql_fetch_row(res1))
			{
				printf("%s\t\t", row1[0]);
			}
			sprintf(temp2, "select * from game where gid = %d", gid);
			if (mysql_query(p, temp2))
			{
				printf("��ѯʧ��!%s\n", mysql_error(p));
				return;
			}
			MYSQL_RES* res2 = mysql_store_result(p);
			MYSQL_ROW row2;
			while (row2 = mysql_fetch_row(res2))
			{
				int tidA = atoi(row2[1]);
				int tidB = atoi(row2[2]);
				char sqlA[80];
				char sqlB[80];
				sprintf(sqlA, "select * from team where tid = %d", tidA);
				sprintf(sqlB, "select * from team where tid = %d", tidB);
				if (mysql_query(p, sqlA))
				{
					printf("��ѯʧ��\n");
					return;
				}
				MYSQL_RES* res3 = mysql_store_result(p);
				MYSQL_ROW row3;
				while (row3 = mysql_fetch_row(res3))
				{
					printf("%s\t\t", row3[1]);
				}
				if (mysql_query(p, sqlB))
				{
					printf("��ѯʧ��\n");
					return;
				}
				MYSQL_RES* res4 = mysql_store_result(p);
				MYSQL_ROW row4;
				while (row4 = mysql_fetch_row(res4))
				{
					printf("%s\t", row4[1]);
				}
			}
			printf("%s\n", row[3]);
		}
	}
	else {
		GetAll(p);
	}
	return;
}

void GetAll(MYSQL* p)
{
	char name[20];
	printf("����������Ҫ��ѯ���û����ǳ�:");
	scanf("%s", &name);
	char temp[80];
	sprintf(temp, "select * from user where uname = '%s'", name);
	if (mysql_query(p, temp))
	{
		printf("��ѯʧ��!\n");
		return;
	}
	MYSQL_RES* res = mysql_store_result(p);
	MYSQL_ROW row;
	int colume = mysql_num_rows(res);
	if (colume > 0)
	{
		printf("��ѯ�ɹ�\n");
	}
	else
	{
		printf("��ѯʧ�ܣ��û��������ڻ�����ԤԼ\n");
		return;
	}
	while (row = mysql_fetch_row(res))
	{
		int uid = atoi(row[0]);
		char str[80];
		sprintf(str, "select * from user_game where uid = %d", uid);
		if (mysql_query(p, str))
		{
			printf("��ѯʧ��:%s\n", mysql_error(p));
			return;
		}
		MYSQL_RES* re = mysql_store_result(p);
		MYSQL_ROW r;
		printf("��ѯ���\n");
		printf("���\t�û��ǳ�\t����A����\t����B����\tʱ��\n");
		while (r = mysql_fetch_row(re))
		{
			printf("%s\t", r[0]);
			int uid = atoi(r[1]);
			int gid = atoi(r[2]);
			char temp1[80];
			char temp2[80];
			sprintf(temp1, "select uname from user where uid = %d", uid);
			if (mysql_query(p, temp1))
			{
				printf("��ѯʧ��!%s\n", mysql_error(p));
				return;
			}
			MYSQL_RES* res1 = mysql_store_result(p);
			MYSQL_ROW row1;
			while (row1 = mysql_fetch_row(res1))
			{
				printf("%s\t\t", row1[0]);
			}
			sprintf(temp2, "select * from game where gid = %d", gid);
			if (mysql_query(p, temp2))
			{
				printf("��ѯʧ��!%s\n", mysql_error(p));
				return;
			}
			MYSQL_RES* res2 = mysql_store_result(p);
			MYSQL_ROW row2;
			while (row2 = mysql_fetch_row(res2))
			{
				int tidA = atoi(row2[1]);
				int tidB = atoi(row2[2]);
				char sqlA[80];
				char sqlB[80];
				sprintf(sqlA, "select * from team where tid = %d", tidA);
				sprintf(sqlB, "select * from team where tid = %d", tidB);
				if (mysql_query(p, sqlA))
				{
					printf("��ѯʧ��\n");
					return;
				}
				MYSQL_RES* res3 = mysql_store_result(p);
				MYSQL_ROW row3;
				while (row3 = mysql_fetch_row(res3))
				{
					printf("%s\t\t", row3[1]);
				}
				if (mysql_query(p, sqlB))
				{
					printf("��ѯʧ��\n");
					return;
				}
				MYSQL_RES* res4 = mysql_store_result(p);
				MYSQL_ROW row4;
				while (row4 = mysql_fetch_row(res4))
				{
					printf("%s\t", row4[1]);
				}
			}
			printf("%s\n", row[3]);
		}
	}
	return;
}

void ChangeRole(MYSQL* pconn)
{
	char name[100];
	char sql_update_role[100];

	int role2;

	printf("�����������޸ĵ��û���:\n");
	scanf("%s", name);

	printf("�������޸ĺ��Ȩ�ޣ�\n");
	printf("1.��ͨ�û� 2.ǰ̨����Ա 3.��������Ա\n");
	scanf("%d", &role2);

	sprintf(sql_update_role, "update user set role=%d where uname = '%s'", role2-1, name);
	if (mysql_query(pconn, sql_update_role))
	{
		printf("�޸�Ȩ��ʧ��\n");
	}
	else
	{
		printf("�޸�Ȩ�޳ɹ�\n");
	}
}