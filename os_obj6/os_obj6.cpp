#include"os_obj6.h"

//文件输入函数
void in(int* a, int track_num,int &first_track)
{
	const char* filename = "test.txt";
	ifstream ism;
	ism.open(filename);
	if (!ism.is_open())
	{
		cout << "hhhhhhhhh" << endl;
	}
	ism >> first_track;
	for (int i = 0; i < track_num; i++)
	{
		ism >> a[i];
	}
}

//初始化磁盘数组
void ini_tarray(int* a, t_array &t,int track_num)
{
	int i = 0;
	for (i; i < track_num; i++)
	{
		t.array[i].num = a[i];
		t.array[i].visited = 0;
	}
	t.current = 0;
}

//升序排列磁道数组
void sort_up(t_array &t, int track_num)
{
	for (int i = 0; i < track_num; i++)
	{
		for (int j = track_num - 1; j > i; j--)
		{
			if (t.array[j - 1].num > t.array[j].num)
			{
				int temp = t.array[0].num;
				temp = t.array[j - 1].num;
				t.array[j - 1].num = t.array[j].num;
				t.array[j].num = temp;
			}
		}
	}
}

//先来先处理
void FCFS(t_array t, int first_track,int track_num)
{
	int current_track = first_track;		//初始化当前磁道为第一次道
	int distance[100] = { 0 };		//距离数组，用于输出结果
	for (int i = 0; i < track_num; i++)
	{
		if (current_track >= t.array[t.current].num)	//如果当前磁道比上一个磁道大，大的减小的
		{
			distance[i] = current_track - t.array[t.current].num;	
		}
		else                                            //大的减小的
		{
			distance[i] = t.array[t.current].num - current_track;
		}
		current_track = t.array[t.current].num;		//更新当前磁道
		t.current++;	//找下一个磁道
		
	}
	//计算平均移动距离
	float result = 0;
	for (int i = 0; i < track_num; i++)
	{
		result += distance[i];
	}
	float average = result / track_num;
	//输出
	cout << "----------FCFS----------" << endl;
	cout << "开始磁道为：" << first_track<<endl;
	cout << "下一磁道" << "\t" << "|" << "    " << "移动距离" << endl;
	for (int i = 0; i < track_num; i++)
	{
		cout << "   " << t.array[i].num <<  "\t" << "\t" << "|"  << "\t" << distance[i] << endl;
	}
	cout << "平均：" << average << endl;
		
}

//最短寻道时间优先
void SSTF(t_array t, int first_track, int track_num)
{
	t.array[track_num].num = first_track;		//将开始磁道放到磁道数组中
	track_num++;		//磁道总数+1，以免数组越界
	sort_up(t, track_num);		//将数组升序排列
	while (t.array[t.current].num != first_track)
	{
		t.current++;		//在排序后的数组中找到开始磁道
	}
	t.array[t.current].visited = 1;
	int count = 0;		//用于循环结束
	int distance[100] = { 0 };		//输出距离数组
	int i = 0;
	int next[100] = { 0 };		//下一节点数组，用于输出
	int left = t.current - 1;	//设置开始磁道的左边第一个磁道为left伪指针
	int right = t.current + 1;	//设置开始磁道的右边第一个磁道为right伪指针
	while (count < track_num-2)
	{
		
		if (t.array[left].visited == 0 && t.array[right].visited == 0)		//左右两边都未处理过
		{
			//大的减小的
			if ((t.array[right].num - t.array[t.current].num) < (t.array[t.current].num - t.array[left].num))
			{
				distance[i] = t.array[right].num - t.array[t.current].num;
				next[i] = t.array[right].num;	//更新下一磁道数组
				i++;		//更新两个输出数组的下标
				t.array[right].visited = 1;		//标记访问
				t.current = right;		//更新当前磁道
				right++;		//更新right
			}
			else if ((t.array[right].num - t.array[t.current].num) > (t.array[t.current].num - t.array[left].num))
			{
				distance[i] = t.array[t.current].num - t.array[left].num;		//同上
				next[i] = t.array[left].num;
				i++;
				t.array[left].visited = 1;
				t.current = left;
				if (left != 0)		//若减到0，left不再更新
				{
					left--;
				}
				
			}
		}
		if (left == 0 && t.array[left].visited != 0)	//左边所有磁道都处理完毕，只需处理右边
		{
			distance[i] = t.array[right].num - t.array[t.current].num;
			next[i] = t.array[right].num;
			t.array[right].visited = 1;
			t.current = right;
			right++;
			i++;
		}
		if (right == track_num+1 && t.array[right].visited != 0)	//右边所有磁道都处理完毕，只需处理左边
		{
			distance[i] = t.array[t.current].num - t.array[left].num;
			next[i] = t.array[left].num;
			t.array[left].visited = 1;
			t.current = left;
			left++;
			i++;
		}
		count++;
	}
	//计算距离平均值
	float result = 0;
	for (int i = 0; i < track_num; i++)
	{
		result += distance[i];
	}
	float average = result / (track_num-1);
	//输出
	cout << "----------SSTF----------" << endl;
	cout << "开始磁道为：" << first_track << endl;
	cout << "下一磁道" << "\t" << "|" << "    " << "移动距离" << endl;
	for (int i = 0; i < track_num-1; i++)
	{
		cout << "   " << next[i]<< "\t" << "\t" << "|" << "\t" << distance[i] << endl;
	}
	cout << "平均：" << average << endl;
}

//SCAN和循环SCAN算法
void SCAN_CSCAN(t_array t, int first_track, int track_num, int mode)
{
	t.array[track_num].num = first_track;
	track_num++;
	int distance[100] = { 0 };
	int next[100] = { 0 };
	sort_up(t, track_num);
	while (t.array[t.current].num != first_track)
	{
		t.current++;
	}
	//往磁道减小的方向进行
	if (mode == 1)
	{
		int left = t.current - 1;
		int right = t.current + 1;
		int flag = 0;
		for (int i = 0; i < track_num; i++)
		{
			if (left >= 0)
			{
				next[i] = t.array[left].num;
				distance[i] = t.array[t.current].num - t.array[left].num;
				t.current = left;
				left--;
				
			}
			//若左边处理完且收到falg = 1的信号，开始从右边第一个开始处理右边
			if (left == -1 && flag ==1)
			{
				next[i] = t.array[right].num;
				distance[i] = t.array[right].num - t.array[t.current].num ;
				t.current = right;
				right++;
			}
			//左边处理完，flag = 1.
			if (left == -1)
			{
				flag = 1;
			}
		}
	}
	//往磁道增大的方向进行
	else if (mode == 2)
	{
		int left = t.current - 1;
		int right = t.current + 1;
		int flag = 0;
		for (int i = 0; i < track_num; i++)
		{
			
			if (right < track_num)
			{
				next[i] = t.array[right].num;
				distance[i] = t.array[right].num - t.array[t.current].num;
				t.current = right;
				right++;
			}
			//若右边处理完且收到falg = 1的信号，开始从左边第一个开始处理右边
			if (right == track_num  && flag == 1)
			{
				next[i] = t.array[left].num;
				distance[i] = t.array[t.current].num - t.array[left].num;
				t.current = left;
				left--;
			}
			if (right == track_num   )
			{
				flag = 1;
			}
		}
	}
	else {
		cout << "please input right mode!" << endl;
	}
	//计算平均
	float result = 0;
	for (int i = 0; i < track_num -1; i++)
	{
		result += distance[i];
	}
	float average = result / (track_num - 1);
	//输出
	cout << "----------SCAN_CSCAN----------" << endl;
	cout << "开始磁道为：" << first_track << endl;
	cout << "下一磁道" << "\t" << "|" << "    " << "移动距离" << endl;
	for (int i = 0; i < track_num - 1; i++)
	{
		cout << "   " << next[i] << "\t" << "\t" << "|" << "\t" << distance[i] << endl;
	}
	cout << "平均：" << average << endl;
}

int main()
{
	int first_track = 0;
	int* a = new int[100];
	int track_num = 10;
	t_array t;
	int b = 0;
	int c = 0;
	in(a, track_num, first_track);
	ini_tarray(a, t, track_num);
	//FCFS(t, first_track, track_num);
	//SSTF(t, first_track, track_num);
	//SCAN_CSCAN(t, first_track, track_num,2);
	while (1)
	{
		cout << endl;
		cout << "pls input a number to select a function" << endl;
		cout << "1.FCFS" << endl;
		cout << "2.SSTF" << endl;
		cout << "3.SCAN_CSCAN" << endl;
		cout << "4.quit" << endl;

		cin >> b;
		if (b == 1)
		{
			FCFS(t, first_track, track_num);
		}
		else if (b == 2)
		{
			SSTF(t, first_track, track_num);
		}
		else if (b == 3)
		{
			cout << "please input a number to decide up or down" << endl;
			cout << "1.磁道上升" << endl;
			cout << "2.磁道下降" << endl;
			cin >> c;
			SCAN_CSCAN(t, first_track, track_num, c);
			
		}
		else if (b == 4)
		{
			break;
		}
		else
		{
			cout << "pls intput a ture number" << endl;
		}
	}
	return 0;
}