#pragma once
#ifndef __GAME_H__
#define __GAME__H__

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#define row 12
#define col 12
#define COUNT 10//�������׵�����
extern char show_mine[row][col];//չʾ����
extern char real_mine[row][col];//��������

//���еĺ�����Ҫд��ͷ�ļ�����������з��ļ�ʶ��Ҫд�ĺ���
void muen();//�˵�����
void init_mine();//��ʼ�����麯��
void set_mine();//���׺���
int count_mine();//ͳ����Χ�׵ĸ���
void print_player();//��ӡ�������
void print_mine();//��ӡ��������� 
int  sweep_mine();//ɨ�׺���
int safe_mine();//�����һ�α���ը���ĺ���
void open_mine(int x, int y);//������Χ��չ������
int count_show_mine();//�ж��������ʣ��δ֪����ĸ���

#endif  //__GAME_H__
