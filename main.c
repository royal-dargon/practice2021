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
	printf("现在是注册界面\n");
	printf("请输入昵称:");
	scanf("%s",&name);
	printf("请输入密码:");
	scanf("%d", &pwd);
	sprintf(temp, "insert into user values(NULL,'%s',%d,'0')", name, pwd);
	if (mysql_query(p, "set names gbk"))
	{
		printf("编码有问题:%s\n", mysql_error(p));
		return;
	}
	if (mysql_query(p, temp))
	{
		printf("注册失败:%s\n", mysql_error(p));
		return;
	}
	printf("注册成功\n");
	return;
}


void login(MYSQL* pconn,struct UserInfo* temp)
{
	char uname[30];
	int upwd;

	//printf("欢迎来到球赛管理系统\n");
	printf("现在是用户登陆页面\n");

	printf("请输入用户名：\n");
	scanf("%s", uname);

	printf("请输入密码：\n");
	scanf("%d", &upwd);

	char sql[100];

	sprintf(sql, "select * from user where uname = '%s' and upwd = %d", uname, upwd);

	if (mysql_query(pconn, sql))
	{
		printf("登陆失败, 错误为%u\n", mysql_errno(pconn));
		printf("%s\n", sql);
	}

	MYSQL_RES *res = mysql_store_result(pconn);
	int colume = mysql_num_rows(res);
	if (colume > 0)
	{
		printf("登陆成功\n");
	}
	else
	{
		printf("登陆失败\n");
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
		printf("连接失败,错误为：%u\n", mysql_errno(pconn));
		mysql_close(pconn);
	}
	else
	{
		printf("连接成功\n");
	}

	if (mysql_query(pconn, "set names gbk"))
	{
		printf("编码有误,错误为%u", mysql_errno(pconn));
	}
}

// 用户
//获取球赛列表
void GetGames(MYSQL* p);

void SearchGame(MYSQL* p);

//前台管理员
//创建球赛
void CreatGame(MYSQL* p);

//预约球赛
void AppointGame(MYSQL* p);

//查看单个用户预约的所有球赛
void GetAppoint(MYSQL* p);


//球员&球队服务
//登记球员
void RecordPlayer(MYSQL* p);

//登记团队
void RecordTeam(MYSQL* p);

void ChangeRole(MYSQL* pconn);

int main()
{
	int i;
	struct UserInfo temp = { -1,'0',0 };
	MYSQL *pconn = mysql_init(0);
	mysql(pconn);
	printf("欢迎来到球赛管理系统\n");
	printf("请输入您想要进行的操作:(1.login 2.register)\n");
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
			printf("请输入你要执行的操作：\n");
			printf("1.获取球赛列表 2.搜索球赛 3.预约球赛 4.退出\n");
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
			printf("请输入你要执行的操作：\n");
			printf("1.预约球赛 2.添加球赛 3.查看用户预约的球赛 4.退出\n");
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
			printf("请输入你要执行的操作：\n");
			printf("1.预约球赛 2.创建游戏 3.获取预约的球赛 4.登记球员 5.登记球队 6.权限管理 7.退出\n");
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
		printf("编码有问题:%s\n",mysql_error(p));
		return;
	}
	sprintf(temp, "select * from user_game");
	if (mysql_query(p,temp))
	{
		printf("查询失败!%s\n", mysql_error(p));
		return;
	}
	MYSQL_RES * res = mysql_store_result(p);
	MYSQL_ROW row;
	printf("编号\t用户序号\t\t比赛序号\t创建时间\n");
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
		printf("编码有问题:%s\n", mysql_error(p));
		return;
	}
	printf("请输入第一支球队的名称:");
	scanf("%s", &name1);
	printf("请输入第二支球队的名称:");
	scanf("%s", &name2);
	printf("请输入比赛地点:");
	scanf("%s", &place);
	sprintf(temp1, "select * from team where tname = '%s'", name1);
	if (mysql_query(p, temp1))
	{
		printf("创建失败:%s\n", mysql_error(p));
		return;
	}
	MYSQL_RES * res = mysql_store_result(p);
	MYSQL_ROW row;
	int colume = mysql_num_rows(res);
	if (colume <= 0)
	{
		printf("队名输入错误\n");
	}
	while (row = mysql_fetch_row(res))
	{
		id1 = atoi(row[0]);
	}
	sprintf(temp2, "select * from team where tname = '%s'", name2);
	if (mysql_query(p, temp2))
	{
		printf("创建失败:%s\n", mysql_error(p));
		return;
	}
	MYSQL_RES * res1 = mysql_store_result(p);
	MYSQL_ROW row1;
	int colume1 = mysql_num_rows(res1);
	if (colume <= 0)
	{
		printf("队名输入错误\n");
	}
	while (row1 = mysql_fetch_row(res1))
	{
		id2 = atoi(row1[0]);
	}
	sprintf(temp, "insert into game (tidA,tidB,gplace)values(%d,%d,'%s')",id1,id2,place);
	if (mysql_query(p, temp))
	{
		printf("创建失败:%s\n", mysql_error(p));
		return;
	}
	printf("创建成功\n");
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
		printf("编码错误:%s\n", mysql_error(p));
		return;
	}
	printf("现在是球员登记界面:\n");
	printf("请输入您要创建球员的姓名");
	scanf("%s", &name);
	printf("请输入该球员所属球队的名称:");
	scanf("%s", &tname);
	printf("请输入该球员的格言:");
	scanf("%s", &motto);
	sprintf(temp1, "select * from team where tname = '%s'", tname);
	if (mysql_query(p, temp1))
	{
		printf("创建失败:%s\n", mysql_error(p));
		return;
	}
	MYSQL_RES * res = mysql_store_result(p);
	MYSQL_ROW row;
	int colume = mysql_num_rows(res);
	if (colume <= 0)
	{
		printf("队名输入错误\n");
	}
	while (row = mysql_fetch_row(res))
	{
		tid = atoi(row[0]);
	}
	sprintf(temp, "insert into player values (NULL,'%s',%d,'%s')", name, tid, motto);
	if (mysql_query(p, temp))
	{
		printf("创建失败!\n");
		return;
	}
	printf("创建成功\n");
	return;
}

void RecordTeam(MYSQL* p)
{
	char temp[80];
	char name[20];
	char city[15];
	printf("现在是创建球队界面\n");
	if (mysql_query(p, "set names gbk"))
	{
		printf("编码错误:%s\n", mysql_error(p));
		return;
	}
	printf("请输入球队名:");
	scanf("%s", &name);
	printf("请输入球队所属城市:");
	scanf("%s", &city);
	sprintf(temp, "insert into team values(NULL,'%s','%s')",name,city);
	if (mysql_query(p, temp))
	{
		printf("创建失败!%s\n", mysql_error(p));
		return;
	}
	printf("创建成功\n");
	return;
}

void AppointMatch(MYSQL* p,int uid)
{
	int id;
	char temp[80];
	printf("现在是预约球赛的界面\n");
	GetGames(p);
	printf("请输入您要预约的球赛的ID：");
	scanf("%d", &id);
	sprintf(temp, "insert into user_game values(NULL,%d,%d,NULL)", uid, id);
	if (mysql_query(p, "set names gbk"))
	{
		printf("编码错误:%s\n", mysql_error(p));
		return;
	}
	if (mysql_query(p, temp))
	{
		printf("预约失败:%s\n", mysql_error(p));
		return;
	}
	printf("预约成功\n");
}

void GetGames(MYSQL* p)
{
	char temp1[70];
	//char name1[20];
	//char name2[20];
	int id1, id2;
	printf("以下是比赛信息\n");
	if (mysql_query(p, "set names gbk"))
	{
		printf("编码错误:%s\n", mysql_error(p));
		return;
	}
	char temp[80];
	sprintf(temp, "select * from game");
	if (mysql_query(p, temp))
	{
		printf("查询失败!%s\n", mysql_error(p));
		return;
	}
	MYSQL_RES* res = mysql_store_result(p);
	MYSQL_ROW row;
	printf("编号\t球队A\t\t球队B\t\t地点\t时间\n");
	while (row = mysql_fetch_row(res))
	{
		printf("%s\t", row[0]);
		id1 = atoi(row[1]);
		id2 = atoi(row[2]);
		sprintf(temp1, "select * from team where tid = %d", id1);
		if (mysql_query(p, temp1))
		{
			printf("查询失败:%s\n", mysql_error(p));
			return;
		}
		MYSQL_RES * res1 = mysql_store_result(p);
		MYSQL_ROW row1;
		int colume = mysql_num_rows(res1);
		if (colume <= 0)
		{
			printf("队名输入错误\n");
		}
		while (row1 = mysql_fetch_row(res1))
		{
			printf("%s\t\t",row1[1]);
		}
		sprintf(temp1, "select * from team where tid = %d", id2);
		if (mysql_query(p, temp1))
		{
			printf("创建失败:%s\n", mysql_error(p));
			return;
		}
		MYSQL_RES * res2 = mysql_store_result(p);
		MYSQL_ROW row2;
		int colume1 = mysql_num_rows(res);
		if (colume1 <= 0)
		{
			printf("队名输入错误\n");
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
	printf("现在是搜索界面\n");
	if (mysql_query(p, "set names gbk"))
	{
		printf("编码错误:%s\n", mysql_error(p));
		return;
	}
	printf("请输入您要搜索球队的名称:");
	scanf("%s", &name);
	sprintf(temp, "select * from team where tname = '%s' ", name);
	if (mysql_query(p, temp))
	{
		printf("搜索失败\n");
	}
	MYSQL_RES* res = mysql_store_result(p);
	MYSQL_ROW row;
	int colume = mysql_num_rows(res);
	if (colume <= 0)
	{
		printf("队名输入错误或者不存在\n");
		return;
	}
	while (row = mysql_fetch_row(res))
	{
		tid = atoi(row[0]);
	}
	sprintf(temp, "select * from game where tidA = %d or tidB = %d ", tid,tid);
	if (mysql_query(p, temp))
	{
		printf("搜索失败\n");
	}
	MYSQL_RES* res1 = mysql_store_result(p);
	MYSQL_ROW row1;
	int colume1 = mysql_num_rows(res1);
	if (colume1 <= 0)
	{
		printf("不存在比赛\n");
		return;
	}
	int id1, id2;
	printf("编号\t球队A\t\t球队B\t\t地点\t时间\n");
	while (row1 = mysql_fetch_row(res1))
	{
		printf("%s\t", row1[0]);
		id1 = atoi(row1[1]);
		id2 = atoi(row1[2]);
		sprintf(temp1, "select * from team where tid = %d", id1);
		if (mysql_query(p, temp1))
		{
			printf("查询失败:%s\n", mysql_error(p));
			return;
		}
		MYSQL_RES * res2 = mysql_store_result(p);
		MYSQL_ROW row2;
		int colume2 = mysql_num_rows(res1);
		if (colume2 <= 0)
		{
			printf("队名输入错误\n");
		}
		while (row2 = mysql_fetch_row(res2))
		{
			printf("%s\t\t", row2[1]);
		}
		sprintf(temp2, "select * from team where tid = %d", id2);
		if (mysql_query(p, temp2))
		{
			printf("创建失败:%s\n", mysql_error(p));
			return;
		}
		MYSQL_RES * res3 = mysql_store_result(p);
		MYSQL_ROW row3;
		int colume3 = mysql_num_rows(res);
		if (colume3 <= 0)
		{
			printf("队名输入错误\n");
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
	printf("现在是查询预定信息的界面\n");
	if (mysql_query(p, "set names gbk"))
	{
		printf("编码问题:%s\n", mysql_error(p));
		return;
	}
	printf("请输入您要进行的操作(1.查询所有 2.查询指定):");
	scanf("%d", &i);
	if (i == 1)
	{
		sprintf(temp, "select * from user_game");
		if (mysql_query(p, temp))
		{
			printf("查询失败:%s\n", mysql_error(p));
			return;
		}
		MYSQL_RES* res = mysql_store_result(p);
		MYSQL_ROW row;
		printf("查询结果\n");
		printf("编号\t用户昵称\t队伍A名称\t队伍B名称\t时间\n");
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
				printf("查询失败!%s\n", mysql_error(p));
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
				printf("查询失败!%s\n", mysql_error(p));
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
					printf("查询失败\n");
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
					printf("查询失败\n");
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
	printf("请输入您需要查询的用户的昵称:");
	scanf("%s", &name);
	char temp[80];
	sprintf(temp, "select * from user where uname = '%s'", name);
	if (mysql_query(p, temp))
	{
		printf("查询失败!\n");
		return;
	}
	MYSQL_RES* res = mysql_store_result(p);
	MYSQL_ROW row;
	int colume = mysql_num_rows(res);
	if (colume > 0)
	{
		printf("查询成功\n");
	}
	else
	{
		printf("查询失败，用户名不存在或者无预约\n");
		return;
	}
	while (row = mysql_fetch_row(res))
	{
		int uid = atoi(row[0]);
		char str[80];
		sprintf(str, "select * from user_game where uid = %d", uid);
		if (mysql_query(p, str))
		{
			printf("查询失败:%s\n", mysql_error(p));
			return;
		}
		MYSQL_RES* re = mysql_store_result(p);
		MYSQL_ROW r;
		printf("查询结果\n");
		printf("编号\t用户昵称\t队伍A名称\t队伍B名称\t时间\n");
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
				printf("查询失败!%s\n", mysql_error(p));
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
				printf("查询失败!%s\n", mysql_error(p));
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
					printf("查询失败\n");
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
					printf("查询失败\n");
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

	printf("请输入你想修改的用户名:\n");
	scanf("%s", name);

	printf("请输入修改后的权限：\n");
	printf("1.普通用户 2.前台管理员 3.超级管理员\n");
	scanf("%d", &role2);

	sprintf(sql_update_role, "update user set role=%d where uname = '%s'", role2-1, name);
	if (mysql_query(pconn, sql_update_role))
	{
		printf("修改权限失败\n");
	}
	else
	{
		printf("修改权限成功\n");
	}
}