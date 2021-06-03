#include"os_obj6.h"

//�ļ����뺯��
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

//��ʼ����������
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

//�������дŵ�����
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

//�����ȴ���
void FCFS(t_array t, int first_track,int track_num)
{
	int current_track = first_track;		//��ʼ����ǰ�ŵ�Ϊ��һ�ε�
	int distance[100] = { 0 };		//�������飬����������
	for (int i = 0; i < track_num; i++)
	{
		if (current_track >= t.array[t.current].num)	//�����ǰ�ŵ�����һ���ŵ��󣬴�ļ�С��
		{
			distance[i] = current_track - t.array[t.current].num;	
		}
		else                                            //��ļ�С��
		{
			distance[i] = t.array[t.current].num - current_track;
		}
		current_track = t.array[t.current].num;		//���µ�ǰ�ŵ�
		t.current++;	//����һ���ŵ�
		
	}
	//����ƽ���ƶ�����
	float result = 0;
	for (int i = 0; i < track_num; i++)
	{
		result += distance[i];
	}
	float average = result / track_num;
	//���
	cout << "----------FCFS----------" << endl;
	cout << "��ʼ�ŵ�Ϊ��" << first_track<<endl;
	cout << "��һ�ŵ�" << "\t" << "|" << "    " << "�ƶ�����" << endl;
	for (int i = 0; i < track_num; i++)
	{
		cout << "   " << t.array[i].num <<  "\t" << "\t" << "|"  << "\t" << distance[i] << endl;
	}
	cout << "ƽ����" << average << endl;
		
}

//���Ѱ��ʱ������
void SSTF(t_array t, int first_track, int track_num)
{
	t.array[track_num].num = first_track;		//����ʼ�ŵ��ŵ��ŵ�������
	track_num++;		//�ŵ�����+1����������Խ��
	sort_up(t, track_num);		//��������������
	while (t.array[t.current].num != first_track)
	{
		t.current++;		//���������������ҵ���ʼ�ŵ�
	}
	t.array[t.current].visited = 1;
	int count = 0;		//����ѭ������
	int distance[100] = { 0 };		//�����������
	int i = 0;
	int next[100] = { 0 };		//��һ�ڵ����飬�������
	int left = t.current - 1;	//���ÿ�ʼ�ŵ�����ߵ�һ���ŵ�Ϊleftαָ��
	int right = t.current + 1;	//���ÿ�ʼ�ŵ����ұߵ�һ���ŵ�Ϊrightαָ��
	while (count < track_num-2)
	{
		
		if (t.array[left].visited == 0 && t.array[right].visited == 0)		//�������߶�δ�����
		{
			//��ļ�С��
			if ((t.array[right].num - t.array[t.current].num) < (t.array[t.current].num - t.array[left].num))
			{
				distance[i] = t.array[right].num - t.array[t.current].num;
				next[i] = t.array[right].num;	//������һ�ŵ�����
				i++;		//�����������������±�
				t.array[right].visited = 1;		//��Ƿ���
				t.current = right;		//���µ�ǰ�ŵ�
				right++;		//����right
			}
			else if ((t.array[right].num - t.array[t.current].num) > (t.array[t.current].num - t.array[left].num))
			{
				distance[i] = t.array[t.current].num - t.array[left].num;		//ͬ��
				next[i] = t.array[left].num;
				i++;
				t.array[left].visited = 1;
				t.current = left;
				if (left != 0)		//������0��left���ٸ���
				{
					left--;
				}
				
			}
		}
		if (left == 0 && t.array[left].visited != 0)	//������дŵ���������ϣ�ֻ�账���ұ�
		{
			distance[i] = t.array[right].num - t.array[t.current].num;
			next[i] = t.array[right].num;
			t.array[right].visited = 1;
			t.current = right;
			right++;
			i++;
		}
		if (right == track_num+1 && t.array[right].visited != 0)	//�ұ����дŵ���������ϣ�ֻ�账�����
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
	//�������ƽ��ֵ
	float result = 0;
	for (int i = 0; i < track_num; i++)
	{
		result += distance[i];
	}
	float average = result / (track_num-1);
	//���
	cout << "----------SSTF----------" << endl;
	cout << "��ʼ�ŵ�Ϊ��" << first_track << endl;
	cout << "��һ�ŵ�" << "\t" << "|" << "    " << "�ƶ�����" << endl;
	for (int i = 0; i < track_num-1; i++)
	{
		cout << "   " << next[i]<< "\t" << "\t" << "|" << "\t" << distance[i] << endl;
	}
	cout << "ƽ����" << average << endl;
}

//SCAN��ѭ��SCAN�㷨
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
	//���ŵ���С�ķ������
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
			//����ߴ��������յ�falg = 1���źţ���ʼ���ұߵ�һ����ʼ�����ұ�
			if (left == -1 && flag ==1)
			{
				next[i] = t.array[right].num;
				distance[i] = t.array[right].num - t.array[t.current].num ;
				t.current = right;
				right++;
			}
			//��ߴ����꣬flag = 1.
			if (left == -1)
			{
				flag = 1;
			}
		}
	}
	//���ŵ�����ķ������
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
			//���ұߴ��������յ�falg = 1���źţ���ʼ����ߵ�һ����ʼ�����ұ�
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
	//����ƽ��
	float result = 0;
	for (int i = 0; i < track_num -1; i++)
	{
		result += distance[i];
	}
	float average = result / (track_num - 1);
	//���
	cout << "----------SCAN_CSCAN----------" << endl;
	cout << "��ʼ�ŵ�Ϊ��" << first_track << endl;
	cout << "��һ�ŵ�" << "\t" << "|" << "    " << "�ƶ�����" << endl;
	for (int i = 0; i < track_num - 1; i++)
	{
		cout << "   " << next[i] << "\t" << "\t" << "|" << "\t" << distance[i] << endl;
	}
	cout << "ƽ����" << average << endl;
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
			cout << "1.�ŵ�����" << endl;
			cout << "2.�ŵ��½�" << endl;
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