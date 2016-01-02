
#include "stdafx.h"
#include "Tool.h"


// ������һ�� [min,max] ��int
int RandomInt(int min, int max)
{
	//���Է��� minstd_rand �� mt19937��ǳ��࣬
	//����100W���ʲ��Է���Ƚ�ƽ��
	//std::mt19937 mt(clock());
	std::minstd_rand mt(clock());
	std::uniform_int_distribution<int> dis(min,max);

	return dis(mt);
	//return 1;
}

// ������һ�� [min,float] ��float
float RandomReal(float min, float max)
{
	std::minstd_rand mt(clock());
	std::uniform_real_distribution<float> dis(min,max);

	return dis(mt);
}

bool operator==(COORD op1, COORD op2)
{
	return (op1.X == op2.X && op1.Y == op2.Y);
}

/*
//Test Code
int i[100] = { 0 };
for (int index = 0; index < 1000000; index++)
	i[RandomInt(0, 99)]++;

int max, min;
max = min = i[0];
for (int index = 0; index < 100; index++)
{
	cout << "Number " << index << " have " << i[index] << "times!!" << endl;
	if (i[index] > max)
		max = i[index];
	if (i[index] < min)
		min = i[index];
}
cout << "Max times are " << max << endl
<< "Min Times are " << min << endl;
*/