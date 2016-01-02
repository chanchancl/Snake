
#include "stdafx.h"
#include "Tool.h"


// 随机获得一个 [min,max] 的int
int RandomInt(int min, int max)
{
	//测试发现 minstd_rand 比 mt19937快非常多，
	//而且100W概率测试分配比较平均
	//std::mt19937 mt(clock());
	std::minstd_rand mt(clock());
	std::uniform_int_distribution<int> dis(min,max);

	return dis(mt);
	//return 1;
}

// 随机获得一个 [min,float] 的float
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