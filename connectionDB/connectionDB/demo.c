#include <stdio.h>

#include <winsock.h>
// 引用MySQL头文件
#include <mysql.h>

int main()
{
	//mysql初始化
	MYSQL *pconn = mysql_init(0);
	// 链接数据库(初始化信息，链接地址，账号，密码，数据库名称)
	if (!mysql_real_connect(pconn, "localhost", "root", "1234", "empdp", 0, 0, 0))
	{
		printf("链接失败，错误为:%s", mysql_error(pconn));
		goto exit;
	}
	printf("链接成功\n");

	// 解决初始化编码问题
	if (mysql_query(pconn,"set names gbk"))
	{
		printf("编码有错误:%s\n", mysql_error(pconn));
	}
	
	//return 的值是0是成功
	if (mysql_query(pconn, "insert into userInfo Value(NULL,'lili',21,'女')"))
	{
		printf("添加失败\n");
	}
	else {
		printf("添加成功,错误为%s\n",mysql_error(pconn));
		goto exit;
	}
	if (mysql_query(pconn, "select * from userInfo"))
	{
		printf("查询失败\n");
	}
	MYSQL_RES *res = mysql_store_result(pconn);
	// 利用游标去读取数据 
	// 读取出来的数据循环读出每条数据
	MYSQL_ROW *row;
	while (row = mysql_fetch_row(res))
	{
		printf("%s\n", row[0]);
	}

	exit:
	system("pause");
	return 0;
}