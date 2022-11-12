#include<iostream>
#include<cstdio>
#include<windows.h>
#include<conio.h>
using namespace std;
int SIZ = 20;
HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
COORD coord;
HANDLE hCon;
enum Color { DARKBLUE = 1, DARKGREEN, DARKTEAL, DARKRED, DARKPINK, DARKYELLOW, GRAY, DARKGRAY, BLUE, GREEN, TEAL, RED, PINK, YELLOW, WHITE };
//ö��

void SetColor(Color c)
{
    if (hCon == NULL)
        hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hCon, c);//color����
}

SYSTEMTIME sys;
//sys.wYear,sys.wMonth,sys.wDay,sys.wHour,sys.wMinute, sys.wSecond,sys.wMilliseconds,sys.wDayOfWeek
struct PLAYER 
{
    int x, y;//����
    int hp;//����
    int gun;//ǹ
    int direct;//����
} p1, p2;//player1��player2
int map[1005][1005];

int mabs(int x) //��ʱ����صĺ���������ֵ����ֵ��
{
    if (x < 0) 
        return -x; 
    return x;
}

void locate(int x, int y) //��ǰ���� 
{
    coord.X = y - 1;
    coord.Y = x - 1;
    SetConsoleCursorPosition(hout, coord);
}

void print_map() //�߽緽���Ի���ͼ
{
    locate(1, 1);
    SetColor(GRAY);
    for (int i = 1; i <= SIZ; i++) cout << "�� ";//�Ͽ�
    locate(SIZ, 1);
    for (int i = 1; i <= SIZ; i++) cout << "�� ";//�¿�
    for (int i = 2; i < SIZ; i++) {
        locate(i, 1);
        cout << "��";//���
        locate(i, SIZ * 2 - 1);
        cout << "��";//�ҿ�
    }
    locate(SIZ + 1, 1);
    SetColor(WHITE);
}

void create_tree(int x, int y) //��������
{
          map[x][y] 
        = map[x + 1][y] 
        = map[x - 1][y] 
        = map[x][y + 1] 
        = map[x][y - 1] = 2;
}

void use_map(int x) //ѡ���ͼ
{
    if (x == 1)
    {
        SIZ = 20;
        SetColor(DARKGREEN);
              map[16][6]
            = map[15][6] 
            = map[17][6] 
            = map[16][7] 
            = map[16][5] 
            = map[14][13] 
            = map[13][12] 
            = map[13][13] = 2;//��������
        for (int i = 2; i < SIZ; i++) {
            for (int j = 2; j < SIZ; j++) {
                if (map[i][j] == 2) {
                    locate(i, j * 2 - 1);
                    cout << "��";//��ʼ����
                }
            }
        }
        SetColor(GRAY);
        for (int i = 5; i <= 15; i++) {
            map[i][i] = 1;
            locate(i, i * 2 - 1);
            cout << "��";//��ͼ1�ĶԽ���ǽ
        }
        SetColor(WHITE);
    }
    else if (x == 2) //��ͼ2
    {
        SIZ = 30;
        SetColor(GRAY);
        for (int i = 4; i <= 26; i++) {
            if (i == 13 || i == 14 || i == 15) 
                continue;
                  map[i][4] 
                = map[4][i] 
                = map[26][i]
                = map[i][26] = 1;//�ڱ߿��ȱ�ڣ�����֮�Բ��û�
        }
        for (int i = 1; i <= SIZ; i++) {
            for (int j = 1; j <= SIZ; j++) {
                if (map[i][j] == 1) {
                    locate(i, j * 2 - 1);
                    cout << "��";//���ڱ߿�
                }
            }
        }
        SetColor(DARKGREEN);
        for (int i = 10; i <= 20; i++) {
            if (i == 13 || i == 17) continue;
                  map[i][10] 
                = map[10][i] 
                = map[20][i] 
                = map[i][20] = 2;//������������
        }
        create_tree(5, 5);
        create_tree(18, 18);//��������
        for (int i = 1; i <= SIZ; i++) {
            for (int j = 1; j <= SIZ; j++) {
                if (map[i][j] == 2) 
                {
                    locate(i, j * 2 - 1);
                    cout << "��";//��ʼ����
                }
            }
        }
        SetColor(WHITE);
    }
}

void cleanbody(int x, int y);
void putbody(int x, int y, int z);
void player_init() //��ʼ��p1��p2
{
    p1.hp = p2.hp = 300;
    p1.gun = p2.gun = 1;//ǹ
    p1.direct = 4;//����
    p2.direct = 2;
    p1.x = 2;//x����
    p1.y = 2;//y����
    p2.x = SIZ - 1;
    p2.y = SIZ - 1;
    putbody(p1.x, p1.y, 1);//���ò��ܻ�������
    putbody(p2.x, p2.y, 2);
}

void mapinit() //��ʼ����ͼ
{
    for (int i = 1; i <= SIZ; i++) {
              map[i][1] 
            = map[1][i] 
            = map[SIZ][i] 
            = map[i][SIZ] = 1;//�߽��趨
    }
}

void init() 
{
    printf("Use Which Map?\n");
    int x;
    cin >> x;
    system("cls");
    use_map(x); //��3�ֵ�ͼ��1��2������1��2��������������
    mapinit();//��ʼ����ͼ
    print_map();//��ʾ����ͼ
    player_init();//��ʼ��p1��p2
}

void putbody(int x, int y, int z) //�����������
{
    if (z == 1) SetColor(BLUE);//p1��ɫ
    else if (z == 2) SetColor(RED);//p2��ɫ
    locate(x, y * 2 - 1);
    cout << "��";
    SetColor(WHITE);
}

void cleanbody(int x, int y) //�����������������
{
    locate(x, y * 2 - 1);
    cout << " ";
}
/*
LIST
direct:
    w 1
    a 2
    s 3
    d 4
gun:
    usp 1
    mimigun 2
    awp 3
block:
    void 0
    stone 1
    tree 2
    player 3
    clip 4
*/

bool judge(int x, int y) //�ж��Ƿ���磨�߿�
{
    if (map[x][y] == 1) return false;
    if (map[x][y] == 2) return false;
    if (map[x][y] == 3) return false;
    return true;
}

bool judge_gun(int x, int y) //����ǹ�����ж�
{
    if (map[x][y] == 1) return 0;
    if (map[x][y] == 2) return 0;
    if (map[x][y] == 3) {
        if (p1.x == x && p1.y == y) //ǹ������
            p1.hp -= 100;//3������
        else 
            p2.hp -= 100;
        return 0;
    }
    return 1;
}

int cnt;
struct Clip //�ӵ�
{
    int x, y;//�ӵ�����
    int derect;//�ӵ�����
    int force;//����
    int start;
    bool flag;
}clip[1000000];//�������ص���

void create_clip(int y, int x, int a, int b) //�����ӵ�
{
    int X, Y;
    if (y == 1) {
        if (!judge_gun(a - 1, b)) return;//ֻ��ǹ���жϳɹ����ܼ���ִ��
        X = a - 1;  //�ӵ������λ��
        Y = b;      //�ӵ������λ��
    }
    else if (y == 2) {
        if (!judge_gun(a, b - 1)) return;
        X = a;
        Y = b - 1;
    }
    else if (y == 3) {
        if (!judge_gun(a + 1, b)) return;
        X = a + 1;
        Y = b;
    }
    else if (y == 4) {
        if (!judge_gun(a, b + 1)) return;
        X = a;
        Y = b + 1;
    }
    cnt++;
    GetLocalTime(&sys);//��ñ���ʱ��
    clip[cnt].start = sys.wMilliseconds + sys.wSecond * 60 + sys.wHour * 3600;//�ӵ������鿪ʼ��ֵ
    clip[cnt].x = X;//����x
    clip[cnt].y = Y;//����y
    if (x == 1) {//p1
        clip[cnt].derect = p1.direct;//���ǹ��ͬ����
    }
    else if (x == 2) {
        clip[cnt].derect = p2.direct;
    }
}

void shoot(int x) //��ǹ����
{
    if (x == 1) {
        create_clip(p1.direct, 1, p1.x, p1.y);//p1��ǹ
    }
    else if (x == 2) {
        create_clip(p2.direct, 2, p2.x, p2.y);//p2��ǹ
    }
}

void clean_clip(int x, int y) //�ӵ��켣���
{
    locate(x, y * 2 - 1);
    cout << "  ";
    locate(1, 1);
}

void print_clip(int x, int y, int i) //�����ӵ�
{ 
    if (clip[i].flag) {
        clean_clip(x, y);//�����߿������ӵ�
        return;
    }
    locate(x, y * 2 - 1);
    SetColor(YELLOW);
    cout << "*";
    locate(1, 1);
    //  system("pause");
}

void clipmove() //�ӵ��ƶ�����
{
    GetLocalTime(&sys);
    int t = sys.wMilliseconds + sys.wSecond * 60 + sys.wHour * 3600;
    for (int i = 1; i <= cnt; i++) {//�ڷ������ص�����
        if (clip[i].flag) //��ǹ�������ӵ�ִ���ƶ�����
            continue;
        if (mabs(clip[i].start - t) > 50) {//������ʵ����ʡ��
            clip[i].start = t;
            int x = clip[i].x;
            int y = clip[i].y;

            if (clip[i].derect == 1) {//�ӵ�����Ϊ1���ϣ�
                if (!judge_gun(clip[i].x - 1, clip[i].y)) {//�ܳ�����ǹ������
                    clip[i].flag = 1;//��flag����
                    clean_clip(x, y);//���ܺ�����ӵ�
                    continue;
                }
                clean_clip(clip[i].x, clip[i].y);//����ӵ�
                clip[i].x--;//�ӵ������ƶ�
                print_clip(clip[i].x, clip[i].y, i);//�����ӵ������sleep()�𵽶���Ч��
            }
            else if (clip[i].derect == 2) {
                if (!judge_gun(clip[i].x, clip[i].y - 1)) {
                    clip[i].flag = 1;
                    clean_clip(x, y);
                    continue;
                }
                clean_clip(clip[i].x, clip[i].y);
                clip[i].y--;
                print_clip(clip[i].x, clip[i].y, i);
            }
            else if (clip[i].derect == 3) {
                if (!judge_gun(clip[i].x + 1, clip[i].y)) {
                    clip[i].flag = 1;
                    clean_clip(x, y);
                    continue;
                }
                clean_clip(clip[i].x, clip[i].y);
                clip[i].x++;
                print_clip(clip[i].x, clip[i].y, i);
            }
            else if (clip[i].derect == 4) {
                if (!judge_gun(clip[i].x, clip[i].y + 1)) {
                    clip[i].flag = 1;
                    clean_clip(x, y);
                    continue;
                }
                clean_clip(clip[i].x, clip[i].y);
                clip[i].y++;
                print_clip(clip[i].x, clip[i].y, i);
            }
        }
    }
}

void judge_hp() //�ж�ĳ��hpΪ0���ж���Ϸ����
{
    int x = p1.hp;
    int y = p2.hp;
    if (x < 0 && y < 0 && x > y) 
        swap(x, y);//������Сֵ
    if (x <= 0) {//p1����<=0
        locate(1, 1);
        system("cls");
        printf("GAME OVER!\nTHE WINNER IS P2!");//p2ʤ��
        Sleep(5000);
        printf("\n-MADE BY MWVIFJ-");
        exit(0);
    }
    else if (y <= 0) {//p2����<=0
        locate(1, 1);
        system("cls");
        printf("GAME OVER!\nTHE WINNER IS P1!");//p1ʤ��
        Sleep(5000);
        printf("\n-MADE BY MWVIFJ-");
        exit(0);
    }
}

void prog() //�����ƶ�
{  
    char ch;
    while (TRUE) {
        if (_kbhit()) {
            ch = _getch();
            if (ch == 'w' && judge(p1.x - 1, p1.y)) {//δ���ϱ߽�
                p1.direct = 1;  //����
                cleanbody(p1.x, p1.y);//�������
                map[p1.x][p1.y] = 0;//�ƶ�ʱ�������
                putbody(--p1.x, p1.y, 1);//���µ����껭������
                map[p1.x][p1.y] = 3;//�ƶ���������
            }
            else if (ch == '8' && judge(p2.x - 1, p2.y)) {
                p2.direct = 1;
                cleanbody(p2.x, p2.y);
                map[p2.x][p2.y] = 0;
                putbody(--p2.x, p2.y, 2);
                map[p2.x][p2.y] = 3;
            }
            else if (ch == 'a' && judge(p1.x, p1.y - 1)) {
                p1.direct = 2;
                cleanbody(p1.x, p1.y);
                map[p1.x][p1.y] = 0;
                putbody(p1.x, --p1.y, 1);
                map[p1.x][p1.y] = 3;
            }
            else if (ch == '4' && judge(p2.x, p2.y - 1)) {
                p2.direct = 2;
                cleanbody(p2.x, p2.y);
                map[p2.x][p2.y] = 0;
                putbody(p2.x, --p2.y, 2);
                map[p2.x][p2.y] = 3;
            }
            else if (ch == 's' && judge(p1.x + 1, p1.y)) {
                p1.direct = 3;
                cleanbody(p1.x, p1.y);
                map[p1.x][p1.y] = 0;
                putbody(++p1.x, p1.y, 1);
                map[p1.x][p1.y] = 3;
            }
            else if (ch == '5' && judge(p2.x + 1, p2.y)) {
                p2.direct = 3;
                cleanbody(p2.x, p2.y);
                map[p2.x][p2.y] = 0;
                putbody(++p2.x, p2.y, 2);
                map[p2.x][p2.y] = 3;
            }
            else if (ch == 'd' && judge(p1.x, p1.y + 1)) {
                p1.direct = 4;
                cleanbody(p1.x, p1.y);
                map[p1.x][p1.y] = 0;
                putbody(p1.x, ++p1.y, 1);
                map[p1.x][p1.y] = 3;
            }
            else if (ch == '6' && judge(p2.x, p2.y + 1)) {
                p2.direct = 4;
                cleanbody(p2.x, p2.y);
                map[p2.x][p2.y] = 0;
                putbody(p2.x, ++p2.y, 2);
                map[p2.x][p2.y] = 3;
            }
            else if (ch == '0') {//��ǹ
                shoot(2);
            }
            else if (ch == ' ') {
                shoot(1);
            }
            Sleep(20);//CDΪ0.02s
        }
        clipmove();//�ӵ��ƶ��ж�
        judge_hp();
    }
}

void welcome() //������˵����
{
    printf("����������\n���1 wasd�����ƶ����ո񹥻� ֻ�����Ҳ���ӵ�\n���2 ����С����4568�����ƶ���0���� ֻ���������ӵ�\n");
    Sleep(1000);
}

int main() {
    welcome();
    GetLocalTime(&sys);
    init();
    prog();
    return 0;
}