#include <stdio.h>

#include <winsock.h>
// ����MySQLͷ�ļ�
#include <mysql.h>

int main()
{
	//mysql��ʼ��
	MYSQL *pconn = mysql_init(0);
	// �������ݿ�(��ʼ����Ϣ�����ӵ�ַ���˺ţ����룬���ݿ�����)
	if (!mysql_real_connect(pconn, "localhost", "root", "1234", "empdp", 0, 0, 0))
	{
		printf("����ʧ�ܣ�����Ϊ:%s", mysql_error(pconn));
		goto exit;
	}
	printf("���ӳɹ�\n");

	// �����ʼ����������
	if (mysql_query(pconn,"set names gbk"))
	{
		printf("�����д���:%s\n", mysql_error(pconn));
	}
	
	//return ��ֵ��0�ǳɹ�
	if (mysql_query(pconn, "insert into userInfo Value(NULL,'lili',21,'Ů')"))
	{
		printf("���ʧ��\n");
	}
	else {
		printf("��ӳɹ�,����Ϊ%s\n",mysql_error(pconn));
		goto exit;
	}
	if (mysql_query(pconn, "select * from userInfo"))
	{
		printf("��ѯʧ��\n");
	}
	MYSQL_RES *res = mysql_store_result(pconn);
	// �����α�ȥ��ȡ���� 
	// ��ȡ����������ѭ������ÿ������
	MYSQL_ROW *row;
	while (row = mysql_fetch_row(res))
	{
		printf("%s\n", row[0]);
	}

	exit:
	system("pause");
	return 0;
}