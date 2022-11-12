#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <cmath>
#include <windows.h>
using namespace std;

/*** ��궨λ ***/
HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);  //��ȡ ��׼������
COORD coord;

void locate(int x, int y)
{
    coord.X = y;
    coord.Y = x;
    SetConsoleCursorPosition(hout, coord);  //������λ��
};

/*** ���ع�� ***/
void hide()
{
    return;
}

/*** ��������� ***/
double random(double start, double end)
{
    return start + (end - start) * rand() / (RAND_MAX + 1.0); //����һ���������ڵ���start��С��end��
    //������ĸ߼�д��
}

/*** �����ͼ�ĳ��� ***/
int m, n;

//�ߵ�����
struct node
{
    int x, y;
}snake[1000];

//���ȣ�����ʳ���λ��
int snake_length, dir;
node food;
int direct[4][2] = { {-1,0},{1,0},{0,-1},{0,1} };//ʳ���λ��

/*** ���ǽ ***/
void print_wall()
{
    cout << " ";
    for (int i = 1; i <= n; i++)
        cout << "-";//�����һ�� ��----------��
    cout << endl;
    for (int j = 0; j <= m - 1; j++)
    {//�����һ�С�|�����м�����ո����һ�������|��
        cout << "|";//��ǽ
        for (int i = 1; i <= n; i++) cout << " ";
        cout << "|" << endl;//��ǽ
    }
    cout << " ";
    for (int i = 1; i <= n; i++)
        cout << "-";//������һ�С�----------��
}

/*** �״�����ߣ�����snake[0]����ͷ ***/
void print_snake()
{   //�ߵ����ͣ���@*****��
    locate(snake[0].x, snake[0].y);
    cout << "@";//ͷ��
    for (int i = 1; i <= snake_length - 1; i++)//length-1�Ǽ�ȥͷ���ĳ���
    {
        locate(snake[i].x, snake[i].y);
        cout << "*";//����
    }
}

/*** �ж��Ƿ�ײǽ����ͷ���Ƿ��������������һ����λ����������Ϸʧ�� ***/
bool is_correct()
{
    if (snake[0].x == 0      //��ǽ
        || snake[0].y == 0      //��ǽ
        || snake[0].x == m + 1  //��ǽ
        || snake[0].y == n + 1) //��ǽ
        return false;
    for (int i = 1; i <= snake_length - 1; i++)
    {
        if (snake[0].x == snake[i].x && snake[0].y == snake[i].y) //��ײ
            return false;
    }
    return true;
}

/*** ������ɲ����ʳ��λ�� ***/
bool print_food()
{
    srand((unsigned)time(0));//�������
    bool e;
    while (TRUE)
    {
        e = true;
        int i = (int)random(0, m) + 1;
        int j = (int)random(0, n) + 1;
        food.x = i; food.y = j;//ʳ���λ�����
        for (int k = 0; k <= snake_length - 1; k++)
        {//ʳ�ﲻ�ܳ������ߵ����������λ�ô�
            if (snake[k].x == food.x && snake[k].y == food.y)
            {
                e = false;
                break;
            }
        }
        if (e)
            break;
    }
    locate(food.x, food.y);
    cout << "O";
    return true;
}

/*** �ߵ�ǰ�� ***/
bool go_ahead()
{
    node temp;
    bool e = false;
    temp = snake[snake_length - 1]; //��β
    for (int i = snake_length - 1; i >= 1; i--)
        snake[i] = snake[i - 1]; //����һλ���൱�����в��룩
    snake[0].x += direct[dir][0];
    snake[0].y += direct[dir][1];
    locate(snake[1].x, snake[1].y);//��λ��ͷ���ĺ�һλ
    cout << "*";
    //������ͷ����һλ���������壬����β�����ϣ�ʡȥ�ж�λ�ö���β���������

    /*** �Ե���ʳ�� ***/
    if (snake[0].x == food.x && snake[0].y == food.y)
    {
        snake_length++;//��+1
        e = true;
        snake[snake_length - 1] = temp; //Ҫ��ֵ�µ���β
    }

    /*** �����ʱ��״̬ ***/
    if (!e)
    {
        locate(temp.x, temp.y);//��β����
        cout << " ";//������β֮���һλ�������Ϊ�� ������¼�ߵ�·��
    }
    else
        print_food();
    locate(snake[0].x, snake[0].y);
    cout << "@";//�Ե��Ͱ�ʳ���滻����ͷ

    /*** �����ײ ***/
    if (!is_correct())
    {
        system("cls");
        cout << "You lose!" << endl << "Length: " << snake_length << endl;
        return false;
    }
    return true;
}


/*** ������ ***/
int main()
{
    cout << "------------------S n a c k---------------------" << endl;
    cout << "��ע�ⴰ�ڴ�С,���ⷢ����λ�����齫���ڵ�Ϊ���" << endl;
    cout << "��ѡ���Ѷ�.����1-10������1����,1���,10������" << endl;
    cout << "Ȼ�������Ϸ����,�Է�������Ʒ���ף����Ϸ���!" << endl;
    cout << "-----------------------------------------------" << endl;
    m = 25;
    n = 40;
    if (m < 10 || n < 10 || m>25 || n>40)
    {
        cout << "ERROR" << endl;
        system("pause");
        return 0;
    }
    int hard;
    //�����Ѷ�ϵ����1-10
    cin >> hard;
    if (hard <= 0 || hard > 100)
    {
        cout << "ERROR" << endl;
        system("pause");
        return 0;
    }
    /*** ����ȫ����ʼ���������߳���λ�ã����� ***/
    snake_length = 5;
    clock_t a, b;
    char ch;
    double hard_len;
    for (int i = 0; i <= 4; i++)
    {
        snake[i].x = 1;
        snake[i].y = 5 - i;
    }
    dir = 3;//������direct����Ķ�Ӧ�±꣩

    /*** �����ʼ��ͼ������ʳ�� ***/
    system("cls");
    hide();
    print_wall();
    print_food();
    print_snake();
    locate(m + 2, 0);
    cout << "Now length: ";

    /*** ��ʼ��Ϸ ***/
    while (TRUE)
    {
        /*** �Ѷ��泤�����Ӷ���� ***/
        hard_len = (double)snake_length / (double)(m * n);
        /*** ����ʱ�䣬��λ��ms ***/
        a = clock();
        while (TRUE)
        {
            b = clock();
            if (b - a >= (int)(400 - 30 * hard) * (1 - sqrt(hard_len)))
                //b-a>=(400-30*�Ѷ�)*{1-sqrt[�߳�/(��ͼ��*��ͼ��)]}
                break;
        }
        /*** ���ܼ���������������ң����Դ˸ı䷽�� ***/
        if (_kbhit())
        {
            ch = _getch();
            if (ch == -32)
            {
                ch = _getch();
                switch (ch)
                {
                case 72:
                    if (dir == 2 || dir == 3)//���¿������Ҳ�����
                        dir = 0;//��
                    break;
                case 80:
                    if (dir == 2 || dir == 3)//���¿����ң��󲻿���
                        dir = 1;//��
                    break;
                case 75:
                    if (dir == 0 || dir == 1)//���ҿ����£��ϲ�����
                        dir = 2;//��
                    break;
                case 77:
                    if (dir == 0 || dir == 1)//���ҿ����ϣ��²�����
                        dir = 3;//��
                    break;
                }
            }
        }
        /*** ǰ�� ***/
        if (!go_ahead())
            break;
        /*** ����������ʱ���� ***/
        locate(m + 2, 12);  //��λ����������
        cout << snake_length;
    }
    system("pause");
    return 0;
}
