#pragma once
#include<iostream>
#include<fstream>
using namespace std;

//�ŵ��ṹ��
typedef struct track {
	int num;
	int visited;
}track;

//�ŵ��ṹ������
typedef struct track_array {
	track array[100] = { 0 };
	int current;
}t_array;