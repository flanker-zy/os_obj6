#pragma once
#include<iostream>
#include<fstream>
using namespace std;

//磁道结构体
typedef struct track {
	int num;
	int visited;
}track;

//磁道结构体数组
typedef struct track_array {
	track array[100] = { 0 };
	int current;
}t_array;