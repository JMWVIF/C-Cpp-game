#define _CRT_SECURE_NO_WARNINGS 1
//#include"MineClearance.c"		//Դ�ļ��ķ��ļ�����Ҫ���У���Ŀ���Զ���⵽��ֻ��Ҫͷ�ļ�����
#include"MineClearance.h"
double start, finish;

int main()
{
	srand((unsigned int)time(NULL));//���������������
	int input = 0;
	muen();//�˵�
	do
	{
		scanf_s("%d", &input);
		switch (input)
		{
		case 2:game_GOD();//�����ϵ��ӽǺ�����
			break;
		case 1:game();
			break;
		case 0:exit(1);//�˳���Ϸ
			break;
		default:
			printf("���������������\n");
			break;
		}
		printf("\n�Ƿ�������\n");
		muen();
	} while (1);//ѭ������Ϸ
	system("pause");
	return 0;
}