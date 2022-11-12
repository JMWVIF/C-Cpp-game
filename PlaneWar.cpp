#include<iostream>
#include<windows.h>	//�������̨Ӧ�ó������ڵ�
#include<conio.h>
#include<time.h>
#include<string>
using namespace std;

/*=============== all the structures ===============*/
//   COORD ��Windows API�ж����һ�ֽṹ����ʾһ���ַ��ڿ���̨��Ļ�ϵ����ꡣ
// �䶨��Ϊ��
// typedef struct _COORD {
//             SHORT X;  
//             SHORT Y;


//������˽ṹ ���������Frame����ṹ������ ������typedef������Ľṹ�����
typedef struct Frame
{
	COORD position[2];
	int flag;
}Frame;

//������ɫ 
void setcolor(string str)	//���ﲻ������char str[]����Ϊ�����if��ʽ�ұ���const char*�ͣ��޷���char*��ƥ��
{
	if (str == "lightblue")
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | 1);
	if (str == "lightred")
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
	if (str == "lightpurple")
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE);
	if (str == "lightpink")
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE);
	if (str == "blue")
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE);
	if (str == "red")
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x04);
	if (str == "green")
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
	if (str == "purple")
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE);
	if (str == "pink")
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_BLUE);
	if (str == "gray")
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
	if (str == "white")
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
	else return;
}

/*=============== all the functions ===============*/

void SetPos(COORD a)// set cursor 
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(out, a);
}

void SetPos(int i, int j)// set cursor
{
	COORD pos = { i, j };
	SetPos(pos);
}

void HideCursor()	//���ع��
{
	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };//�ڶ���ֵ0��ʾ���ع��
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

//�ѵ�y�У�[x1, x2]֮����������Ϊ ch
void drawRow(int y, int x1, int x2, char ch)
{
	SetPos(x1, y);
	for (int i = 0; i <= (x2 - x1); i++)
		cout << ch;
}

/*
//��a, b ��������ͬ��ǰ���£�������[a, b] ֮�����ch
void drawRow(COORD a, COORD b, char ch)
{
	if (a.Y == b.Y)
		drawRow(a.Y, a.X, b.X, ch);
	else
	{
		SetPos(0, 25);
		cout << "error code 01���޷�����У���Ϊ���������������x����ͬ";
		system("pause");
	}
}
*/

//�ѵ�x�У�[y1, y2] ֮����������Ϊ ch
void drawCol(int x, int y1, int y2, char ch)
{
	int y = y1;
	while (y != y2 + 1)
	{
		SetPos(x, y);
		cout << ch;
		y++;
	}
}

/*
//��a, b ��������ͬ��ǰ���£�������[a, b] ֮�����ch
void drawCol(COORD a, COORD b, char ch)
{
	if (a.X == b.X)
		drawCol(a.X, a.Y, b.Y, ch);
	else
	{
		SetPos(0, 25);
		cout << "error code 02���޷�����У���Ϊ��������ĺ�����y����ͬ";
		system("pause");
	}
}
*/

//���Ͻ����ꡢ���½����꣬��row����С���col�����
void drawFrame(COORD a, COORD  b, char row, char col)//�����л�
{//4��֮ͬ������
	drawRow(a.Y, a.X + 1, b.X - 1, row);
	drawRow(b.Y, a.X + 1, b.X - 1, row);
	drawCol(a.X, a.Y + 1, b.Y - 1, col);
	drawCol(b.X, a.Y + 1, b.Y - 1, col);
}


void drawFrame(int x1, int y1, int x2, int y2, char row, char col)//�������ǻ�������ı߿�	
{//6��֮ͬ������
	COORD a = { x1, y1 };
	COORD b = { x2, y2 };
	drawFrame(a, b, row, col);
}


void drawFrame(Frame frame, char row, char col)	//��׹�ٺ�ķɻ�
{//3��֮ͬ������ 
	COORD a = frame.position[0];
	COORD b = frame.position[1];
	drawFrame(a, b, row, col);
}

// ������Ϸ����
void drawPlaying()
{									  //�����drawFrame���ǻ�����
	drawFrame(0, 0, 48, 24, '=', '|');//	draw map frame������
	drawFrame(49, 0, 79, 4, '-', '|');//	draw output frame״̬����
	drawFrame(49, 4, 79, 9, '-', '|');//	draw score frame��������
	drawFrame(49, 9, 79, 20, '-', '|');//	draw operate frame��������
	drawFrame(49, 20, 79, 24, '-', '|');//	draw other message frame��ʾ����
	SetPos(52, 6);	//SetPos���ǻ������õ�
	cout << "�÷�";
	SetPos(52, 7);
	cout << "�ƺ�";

	setcolor("green");
	SetPos(52, 10);
	cout << "������ʽ";
	SetPos(52, 12);
	cout << "  a,s,d,w ����ս���ƶ�";
	SetPos(52, 14);
	cout << "  p ��ͣ��Ϸ";
	SetPos(52, 16);
	cout << "  e �˳���Ϸ";
	SetPos(52, 18);
	cout << "  k ����";
	setcolor("white");
}

//��[a, b]֮�����һ���������
int random(int a, int b)
{
	int c = (rand() % (a - b)) + a;
	return c;
}

//��������������ľ��ο����������һ������
COORD random(COORD a, COORD b)
{
	int x = random(a.X, b.X);
	int y = random(a.Y, b.Y);
	COORD c = { x, y };
	return c;
}

// �ú��������жϷɻ���ĳһ�����Ƿ���л��нӴ�
// �����л��нӴ����ж�Ϊ׹��
bool judgeCoordInFrame(Frame frame, COORD spot)
{
	if (spot.X >= frame.position[0].X
		&& spot.X <= frame.position[1].X
		&& spot.Y >= frame.position[0].Y
		&& spot.Y <= frame.position[0].Y)
		return true;
	return false;
}

/*
void printCoord(COORD a)
{
	cout << "( " << a.X << " , " << a.Y << " )";
}

void printFrameCoord(Frame a)
{
	printCoord(a.position[0]);
	cout << " - ";
	printCoord(a.position[1]);
}
*/

//���˵�����
int drawMenu()	//��ʼ���棬����
{
	SetPos(30, 1);
	cout << "P l a n e  W a r";
	drawRow(3, 0, 79, '-');
	drawRow(5, 0, 79, '-');
	SetPos(28, 4);
	cout << "w��s ���ߡ���ѡ��   �س���ʼ ";
	SetPos(15, 11);
	cout << "1.�򵥵ĵ���";
	SetPos(15, 13);
	cout << "2.���ĵ���";
	drawRow(20, 0, 79, '-');
	drawRow(22, 0, 79, '-');
	SetPos(49, 11);
	cout << "�򵥵ĵ��ˣ�";
	SetPos(49, 13);
	cout << "�򵥵ĵ������Ž������ƶ��ٶ�";
	SetPos(24, 21);
	int j = 11;
	SetPos(12, j);
	cout << "->";

	drawFrame(45, 8, 79, 16, '=', '|');

	while (1)
	{
		if (_kbhit())  //_kbbit()�����������Ǽ�����̨���ڵİ����Ƿ񱻰���
		{
			char x = _getch(); //_getch()�����������Ǵӿ���̨�л�ȡ������ַ�
			switch (x)
			{
			case 'w':	//����w��
			case 72:  //����72
			{
				if (j == 13)
				{
					SetPos(12, j);
					cout << "��";
					j = 11;
					SetPos(12, j);
					cout << "->";
					SetPos(51, 13);
					cout << "������������������������";
					SetPos(49, 11);
					cout << "�򵥵ĵ��ˣ�";
					SetPos(49, 13);
					cout << "�򵥵ĵ������Ž������ƶ��ٶ�";
				}
				break;
			}
			case 's':
			case 80:  //����80
			{
				if (j == 11)
				{
					SetPos(12, j);
					cout << "��";
					j = 13;
					SetPos(12, j);
					cout << "->";
					SetPos(51, 13);
					cout << "����������������������������";
					SetPos(49, 11);
					cout << "���ĵ��ˣ�";
					SetPos(49, 13);
					cout << "���ĵ������ŽϿ���ƶ��ٶ�";
				}
				break;
			}
			case 13:	//��ʼ��Ϸ �س�����13
			{
				if (j == 8)	return 1;	//Դ����Ϊ8
				else return 2;
			}
			}
		}
	}
}

/*
DWORD WINAPI MusicFun(LPVOID lpParamte)  //���ǵ���bgm.wav�ļ�
{
	//DWORD OBJ;
	sndPlaySound(TEXT("bgm.wav"), SND_FILENAME|SND_ASYNC);
	return 0;
}
*/


/*================== the Game Class ==================*/

class Game
{
public:
	COORD position[10];
	COORD bullet[10];	//һ�����ͬʱ����10���ӵ�
	Frame enemy[8];		//һ�����ͬʱ����8������
	int score;
	int rank;	//����,�Ѷ�
	int rankf;	//�ȼ���־
	string title;
	int flag_rank;	//�ȼ���־

	Game(); //���캯��

	//��ʼ������	(�趨λ��)
	void initPlane();
	void initBullet();
	void initEnemy();

	//��ʼ��(ʣ��δʹ��֮��)
	//void initThisBullet( COORD );
	//void initThisEnemy( Frame );


	//ִ��ĳһ������
	void planeMove(char);//�ɻ��ƶ�
	void bulletMove();	//�ӵ��ƶ�
	void enemyMove();	//�л��ƶ�

	//�������	������״����ʧ����״
	void drawPlane();
	void drawPlaneToNull();
	void drawBullet();
	void drawBulletToNull();
	void drawEnemy();
	void drawEnemyToNull();


	//�������һ
	void drawThisBulletToNull(COORD);//����ʧЧ�ӵ�
	void drawThisEnemyToNull(Frame);

	void Pause();//�ó�Ա��������ʹ��Ϸ��ͣ
	void Playing();//��Ϸ��ѭ��
	void judgePlane();//�жϷɻ��Ƿ���л��ص�
	void judgeEnemy();//�ж��ӵ��Ƿ���ел�

	void Shoot();//�����ӵ�

	void GameOver();//��Ϸʧ��
	void printScore();//�������
};

Game::Game()	//��ʼ��Ϸ�ĳ�ʼ��
{
	initPlane();
	initBullet();
	initEnemy();
	// ��ʼ���ĸ�int�����ݳ�Ա�����ø�ֵ�ķ�ʽ���г�ʼ��
	// string���͵����ݳ�Աtitleû�н��г�ʼ������Ϊ��
	// string�������һ����׼�������ͣ������ඨ����������Ĭ�Ϲ��캯����
	// ��ЩĬ�Ϲ��캯���Ὣ�����ʼ��Ϊ�����Ĭ��״̬��
	// string��Ĭ�Ϲ��캯����������ַ������൱��"" ��
	score = 0;
	rank = 25;
	rankf = 0;
	flag_rank = 0;
}

// �����������Ĵ�����ʵ����Ϊ�˳�ʼ��ս����ʮ�����ֵ�λ�ã�ս�������������ʾ��   
//                     |       5 
//                     |       9    
//                   *****   12034
//                    ***     678
// ��һ��5��0���������ζ�Ӧ��position[1]position[2]position[0]position[3]position[4]
// �ڶ�������0���������ζ�Ӧ��position[6]position[7]position[8]
// ����0�������|����������������ζ�Ӧ��position[5]position[9]
void Game::initPlane()	//��ʼ���ɻ�
{
	COORD center = { 39, 22 };
	position[0].X = position[5].X = position[7].X = position[9].X = center.X;
	position[1].X = center.X - 2;
	position[2].X = position[6].X = center.X - 1;
	position[3].X = position[8].X = center.X + 1;
	position[4].X = center.X + 2;
	for (int i = 0; i <= 4; i++)
		position[i].Y = center.Y; //����y��һ��
	for (int i = 6; i <= 8; i++)
		position[i].Y = center.Y + 1; //����y+1��һ��
	position[5].Y = center.Y - 1;
	position[9].Y = center.Y - 2;
}

void Game::drawPlane()	//���ɻ�
{
	for (int i = 0; i < 9; i++)
	{
		SetPos(position[i]);
		if (i != 5)
			cout << "@";	//�ɻ�����
		else if (i == 5)
			cout << "|";	//�ɻ�ͷ
	}
}

void Game::drawPlaneToNull()	//�����л���ķɻ�ͼ��
{
	for (int i = 0; i < 9; i++)
	{
		SetPos(position[i]);
		cout << " ";
	}
}

void Game::initBullet()	//��ʼ���ӵ�
{
	for (int i = 0; i < 10; i++)
		bullet[i].Y = 30;	//�ӵ���ʼ��λ��
}

void Game::drawBullet()	//���ӵ�
{
	for (int i = 0; i < 10; i++)
	{
		if (bullet[i].Y != 30)//�ӵ��Ķ���
		{
			SetPos(bullet[i]);
			setcolor("blue");
			cout << "*";	//�ӵ����
			setcolor("white");
		}
	}
}

void Game::drawBulletToNull()	//��������or����ΪNULL  ���ӵ���ʧ
{
	for (int i = 0; i < 10; i++)
		if (bullet[i].Y != 30)
		{
			COORD pos = { bullet[i].X, bullet[i].Y + 1 };
			SetPos(pos);
			cout << " ";
		}
}

/*
void Game::drawBulletToNull_EXTRA()  //�����룺bullet
{
	for (int i = 0; i < 10; i++)
		if (bullet[i].Y != 30)
		{
			COORD pos = { bullet[i].X, bullet[i].Y - 1 };
			SetPos(pos);
			cout << " ";
		}
}
*/

void Game::initEnemy()	//��ʼ���л�
{
	COORD a = { 1, 1 };
	COORD b = { 45, 15 };
	for (int i = 0; i < 8; i++)	//һ������㶨ͬʱ����8������
	{
		enemy[i].position[0] = random(a, b);//����������һ�е�ĳ��λ��
		// random(a, b)�ǵ�����һ�����صĺ���������ʾ������a��b֮��ľ��ο�
		// ���������һ������ֵ������������ֵ��Ϊ�л������Ͻǵ����ꡣ
		// enemy[i].position[0]����һ��Frame�ṹ�����͵ı���������˵л�i�����Ͻǵ����ꡣ
		enemy[i].position[1].X = enemy[i].position[0].X + 3; //�л����ҳ�
		enemy[i].position[1].Y = enemy[i].position[0].Y + 2; //�л�ǰ��
		// enemy[i].position[1]Ҳ����һ��Frame�ṹ�����͵ı���������˵л�i�����½ǵ����ꡣ
	}
}

// ������Ҫ���ݵл������Ͻ���������½����껭���л���
// ��Ȼ���л�������������ʾ��
//   --
//  |  |
//   --
void Game::drawEnemy()	//���л�
{
	for (int i = 0; i < 8; i++)
		drawFrame(enemy[i].position[0], enemy[i].position[1], '-', '|');
	//8���л�����һ�����ͣ������ڴ˻�������
}

void Game::drawEnemyToNull()  //����ĳ�������л���ʧ
{
	for (int i = 0; i < 8; i++)
	{
		drawFrame(enemy[i].position[0], enemy[i].position[1], ' ', ' ');
	}
	//8���л���ĳ��ֱ����ʧ
}


// ������"��ͣ��"����ʾ�Ժ󣬳������հ��µİ�����
// ������'p'���Ժ�˵��Ҫ�˳���ͣ״̬����ʱ��Ҫ���"��ͣ��"����ʾ
// ͨ������հ� "         "�����串�ǣ��ﵽЧ��
void Game::Pause()	//��ͣ
{
	SetPos(61, 2);
	cout << "               ";
	SetPos(61, 2);
	cout << "��ͣ��";
	char c = _getch();
	while (c != 'p')
		c = _getch();
	SetPos(61, 2);
	cout << "         ";
}

void Game::planeMove(char x)	//asdw�ƶ�
{
	if (x == 'a')
		if (position[1].X != 1)//���
			for (int i = 0; i <= 9; i++) //9����Ϊ�ҷ��ɻ���10���ַ�������
				position[i].X -= 2;

	if (x == 's')
		if (position[7].Y != 23)//�½�
			for (int i = 0; i <= 9; i++)
				position[i].Y += 1;

	if (x == 'd')
		if (position[4].X != 47)//�ҽ�
			for (int i = 0; i <= 9; i++)
				position[i].X += 2;

	if (x == 'w')
		if (position[5].Y != 3)//�Ͻ�
			for (int i = 0; i <= 9; i++)
				position[i].Y -= 1;
}

// �˳�Ա����������Ӧһ���ӵ����˶�
// ÿ���ӵ��˶�����Ļ�ӵ������궼����ֱ仯����
// ���ж��ӵ��Ƿ���Ч�����ж����if (bullet[i].Y != 30)����
// ���ӵ���Ч�������ӵ���Y�������1��X���겻�䣬
// ����ӵ��������֮���Ƿ�ﵽ�ϱ߽磬����ﵽ�ϱ߽磬�򽫸��ӵ�����Ļ�ϲ�����
// ͬʱ�������ӵ���ΪʧЧ״̬���� bullet[i].Y = 30��
void Game::bulletMove()	//�ӵ��ƶ�
{
	for (int i = 0; i < 10; i++)	//�ӵ����ͬʱ����10��
	{
		if (bullet[i].Y != 30)	//�����½�
		{
			bullet[i].Y -= 1;	//�����ӵ������ӵ��ƶ���Ч��
			if (bullet[i].Y == 1)	//�����Ͻ�ʱor�����л�ʱ
			{
				COORD pos = { bullet[i].X, bullet[i].Y + 1 };
				//��ȡ����ӵ�����ʧ���ٽ�״̬

				drawThisBulletToNull(pos);	//���ӵ���ʧ
				bullet[i].Y = 30;	//һ���ӵ����磬����һ�����Է�����
			}

		}
	}
}

//�ó�Ա����������Ӧһ�εл����ƶ�
//�����ϱ���ͬʱ���ְ˼ܵл������
//�����ĳ�ܵл��˶����±߽紦�������øõл�������
void Game::enemyMove()	//�л��ƶ�
{
	for (int i = 0; i < 8; i++)	//8���л�
	{
		for (int j = 0; j < 2; j++) //�ƶ�
			enemy[i].position[j].Y++;
		// ���ǽ�ÿ�ܵл������ϽǺ����½������Yֵ����1��
		// ��ʾ�õл���������һ������

		// ���������һ�������ĵл������½������Yֵ�Ƿ�ﵽ24��
		// ����ﵽ������л��Ѿ��˶����±߽��ˣ�
		// ��ʱ��Ҫ������øõл������꣨�µĵл�������
		if (24 == enemy[i].position[1].Y)
		{
			COORD a = { 1, 1 };
			COORD b = { 45, 3 };
			enemy[i].position[0] = random(a, b);
			enemy[i].position[1].X = enemy[i].position[0].X + 3;	//�л���
			enemy[i].position[1].Y = enemy[i].position[0].Y + 2;	//�л���
		}
	}
}

// �ó�Ա���������ж�ս���Ƿ�׹�٣�
// �����ж�ÿ���ϰ�����ս����ÿ�������Ƿ��нӴ���
// ����нӴ������ʾս��׹��
void Game::judgePlane()	 //�жϷɻ��Ƿ����ϰ����ص�
{
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 9; j++)
			// �˴���ʵ��position[j]��ָս����10�����ֵ�COORD���꣬
			// ���еĳ�Ա�������Է������ݳ�Ա������
			// �˴�Ҳ����д��this->position[j]����Ϊ
			// ��Ա��������һ�����ӵ������βΣ���ָ���������һ��ָ�룬
			// ��������β�����Ϊthis������ó�Ա�����Ķ������һ��
			// ��Ա�������ܶ���this�βΣ������ɱ����������ض��塣
			// ��Ա�����ĺ����������ʽʹ��thisָ�룬�����Ǳ�����ô����
			if (judgeCoordInFrame(enemy[i], position[j]))
			{
				SetPos(62, 1);
				cout << "׹��";
				setcolor("red");
				drawFrame(enemy[i], '+', '+');
				setcolor("white");
				// ����ս����ײ���ϰ������״����Ϊ:
				//    ++
				//   +  +
				//    ++
				Sleep(1000);
				GameOver();
				break;
			}
}

void Game::drawThisBulletToNull(COORD c)  //�ӵ���ʧ����״
{
	SetPos(c);
	cout << " ";
}

void Game::drawThisEnemyToNull(Frame f)	//�л���ʧ����״
{
	drawFrame(f, ' ', ' ');
}

// �ó�Ա�������α���ÿһ�ܵл���
// ��ÿһ�ܵл�������ÿһ���ӵ����м�⣨˫�ر�����
// �жϵл��Ƿ����ӵ��нӴ�������нӴ������ʾ���ел���
// ��ʱ���л����ӵ�������Ȼ���ڽ��涥����λ�ô��������һ�ܵл�
void Game::judgeEnemy()		//�ж��ӵ��Ƿ���ел�
{
	for (int i = 0; i < 8; i++)//�����л�
		for (int j = 0; j < 10; j++)//�����ӵ�
			if (judgeCoordInFrame(enemy[i], bullet[j]))
				//�����ǰ�������ӵ������л�������Ļ�����ִ�����д���
			{
				score += 5;//�ӷ�
				drawThisEnemyToNull(enemy[i]);//�л���ʧ
				COORD a = { 1, 1 };
				COORD b = { 45, 3 };
				enemy[i].position[0] = random(a, b);
				enemy[i].position[1].X = enemy[i].position[0].X + 3;//�л���
				enemy[i].position[1].Y = enemy[i].position[0].Y + 2;//�л���
				drawThisBulletToNull(bullet[j]);//�ӵ���ʧ
				bullet[j].Y = 30;//���ӵ�����
			}
}


// �����Ա����������Ӧһ�����������
// Ҳ���ǣ�����Ϸ�е�ʱ����Ұ���"k"������ִ�иú�����
// �����ӵ�����COORD bullet[10]����ģ����ͬһʱ�̣�������ֻ����10���ӵ�ͬʱ���֡�
// ��������ڲ���10���ӵ�������"k"����ս��Ӧ�÷����һ���ӵ���
// ���ǣ����α���10���ӵ�����������һ��ʧЧ���ӵ���
// ���������ӵ������µ����꣨�ɻ����ڿڣ�Ҳ���ǣ�position[5].X��position[5].Y - 1������
// ���伤�Ȼ���˳�forѭ��������ִ����ϡ�
void Game::Shoot()
{
	for (int i = 0; i < 10; i++)
		if (bullet[i].Y == 30)
		{
			bullet[i].X = position[5].X;//�ɻ����ڿھ��������ɵ��ӵ��ĳ�ʼλ��
			bullet[i].Y = position[5].Y - 1;
			break;
		}
}

void Game::printScore()
{
	if (score == 120 && flag_rank == 0)	//������120�����������һ����ٶȼӿ죨����ˢ��ʱ���̣�
	{
		rank -= 5;
		flag_rank = 1;
	}

	else if (score == 240 && flag_rank == 1) //240
	{
		rank -= 5;
		flag_rank = 2;
	}
	else if (score == 360 && flag_rank == 2) //360
	{
		rank -= 5;
		flag_rank = 3;
	}
	int x = rank / 5;
	SetPos(60, 6);
	cout << score;

	if (rank != rankf)
	{
		SetPos(60, 7);
		if (x == 4)	//��ʼΪ4
			title = "��������Ա";
		else if (x == 3) //������x-1
			title = "�м�����Ա";
		else if (x == 2)
			title = "�߼�����Ա";
		else if (x == 1)
			title = "���Ʒ���Ա";
		cout << title;
	}
	rankf = rank;
}


// �����Ա��������Ϸ����ѭ��������
// ������������Ϸ���̡�
void Game::Playing()
{
	//HANDLE MFUN;
	//MFUN = CreateThread(NULL, 0, MusicFun, NULL, 0, NULL); 

	drawEnemy();
	drawPlane();

	int flag_bullet = 0;
	int flag_enemy = 0;

	while (1)
	{
		Sleep(8);
		if (_kbhit())
		{
			char x = _getch();
			if ('a' == x || 's' == x || 'd' == x || 'w' == x)
			{
				drawPlaneToNull();//���÷ɻ���ͼ����ʧ
				planeMove(x);//�ɻ��ƶ�
				drawPlane();//�������е����ݳ�Ա���ɻ��������꣬���µ����괦�����»��Ʒɻ���
				judgePlane();//�жϷɻ��Ƿ���л��ص���׹�٣�
			}

			// ��ĳһѭ�����У������⵽��'p'�����£�
			// �������Ҳ���Ϸ�������"��ͣ��..."��Ȼ������while()ѭ��һֱ�ȴ�'p'���ٴΰ��£�
			// ���'p'��û�а��£���һֱ����while()ѭ���ڣ���˲���ִ�к���ĳ�������ͣ��Ч����
			else if ('p' == x)
				Pause();

			// ����Ǽ�⵽'k'�����£�������Shoot()����
			else if ('k' == x)
				Shoot();

			// ����Ǽ�⵽'e'�����£�������GameOver()������
			// GameOver()����ִ����Ϻ�ִ��break;�������whileѭ����ע�ⲻ��if (_kbhit())����
			// break������ڽ��������while��do while��for��switch��䣬���������ִ��Ȩ���ݸ�������
			// ����ֹ���֮�����䡣
			else if ('e' == x)
			{
				//CloseHandle(MFUN);
				GameOver();
				break;
			}

		}
		/* �����ӵ� */
		// �ж��ӵ�״̬�ĳ���һֱ������
		if (0 == flag_bullet)
		{
			bulletMove();           // ���½�������Ч�ӵ�������
			drawBulletToNull();     // �����ھ�������ӵ�����
			drawBullet();           // ���Ƴ��������ϵ��ӵ�
			judgeEnemy();           // �ж��ϰ����Ƿ��ӵ�����
		}
		flag_bullet++;
		if (5 == flag_bullet)	//�ӵ�CD��5��sleep(8)����������ٰ�һ��
			flag_bullet = 0;

		/* ������� */
		if (0 == flag_enemy)
		{
			drawEnemyToNull();     // �����е��ϰ��ﶼ����
			enemyMove();           // �����ϰ��������
			drawEnemy();           // ���Ƴ������������ϵ��ϰ���
			judgePlane();          // �ж��ϰ����Ƿ���ս���Ӵ�
		}
		flag_enemy++;	//ͨ�����̻���ˢ�µ�ʱ�����Ӷ��ﵽ�Ӿ��ϵļ���Ч��
		if (flag_enemy >= rank)	   //�Ѷ�һ����������
			flag_enemy = 0;		//ʵ���ϣ�����ۼ�Ļ������Կ������𽥼��ٺ�����ԭ���ٶȣ����𽥼��ٵ�ѭ��

		/* ����÷� */
		printScore();
	}
}

void Game::GameOver()//��Ϸ����
{
	system("cls");
	COORD p1 = { 28,9 };	//����ַ�Ҫ���Ĳ���
	COORD p2 = { 53,15 };
	drawFrame(p1, p2, '=', '|');//�ַ����
	SetPos(36, 12);
	setcolor("lightpurple");
	string str = "Game Over";
	for (int i = 0; i < str.size(); i++)
	{
		Sleep(80);//Game Overÿ���һ���ַ���Ҫ��Ϣ0.08��
		cout << str[i];
	}
	setcolor("white");
	Sleep(1000);	//��Ϣ1�����ת��һ������
	system("cls");
	drawFrame(p1, p2, '=', '|');  //����ԭ����Ԥ�趨λ�ã�ֻ��Ҫ���»��Ͼ���
	SetPos(31, 11);
	cout << "����л�: " << score / 5;
	SetPos(31, 12);
	cout << "�á����֣�" << score;
	SetPos(31, 13);
	cout << "��óƺ�: " << title;
	SetPos(30, 16);
	Sleep(1000);
	setcolor("green");
	cout << "���� �ǣ�y��| ��n��";
	setcolor("white");
as:
	char x = _getch();
	if (x == 'n')
		exit(0);//���������˳�
	else if (x == 'y')
	{
		system("cls");
		Game game;
		int a = drawMenu();// ������Ϸ��ʼ�������˵�
		if (a == 2)
			game.rank = 20;	//һ��ʼ��20������/5���ĸ��׶�
		system("cls");
		drawPlaying();// ������Ϸ������
		game.Playing();
	}
	else goto as;//�������������ļ�������Ч�ģ����¸���һ���������
}

/*================== the main function ==================*/
int main()
{
	//��Ϸ׼��
	cout << "\t\t****�ɻ���ս��Ϸ����׼��****\n";
	cout << "\n�Ѽ��� 0%";
	for (int i = 0; i < 9; i++) {
		SetPos((i + 1) * 2 - 1, 1); cout << "�� ";
		SetPos(7 - 1, 3 - 1); cout << i + 1;
		Sleep(30);
	}
	Sleep(30);
	SetPos(19, 1); cout << "�� \n�Ѽ���100%";
	Sleep(50);
	system("cls");
	srand((int)time(0));	//�������
	HideCursor();	//���ع��

	Game game;
	int a = drawMenu();
	if (a == 2)
		game.rank = 20;
	system("cls");
	drawPlaying();
	game.Playing();
}


// ��������kbhit()��VC++6.0��Ϊ_kbhit()��
// ���ܼ�����ֵ����鵱ǰ�Ƿ��м������룬�����򷵻�һ����0ֵ�����򷵻�0
// �÷���int kbhit(void);
// ����ͷ�ļ��� include <conio.h>
// kbhit()��ִ��ʱ,����Ƿ��а�������,�а��·��ط�0ֵ��û�а����򷵻�0���Ƿ�����������
// ��ͬ��getch()����ִ��ʱ, ��ⰴ��ʲô��, ����������ú��������أ�Ҳ�Ͳ�������һ��������������������


// getch()�Ǳ�������õĺ��������������һ�������Ժ�����
// ���û�����ĳ���ַ�ʱ�������Զ���ȡ�����谴�س�
// getch()���Ǳ�׼C�еĺ�����������C�����С�
// ����ͷ�ļ���conio.h��������stdio.h��
// ��ch = getch(); ��ȴ��㰴�������֮�󣬰Ѹü��ַ�����Ӧ��ASCII�븳��ch, ��ִ���������䡣

