#include "pch.h"
#include "TestSystem.h"
#include "RedBlackClass.h"
#include <random>
#include <iostream>

using namespace std;

TestSystem::TestSystem(RedBlackClass* redBlack)
{
	for (int i = 0; i < 100; ++i)
	{
		mData[i] = i;
	}
	mRedBlack = redBlack;
}

TestSystem::~TestSystem()
{
}

void TestSystem::RandomInsert()
{
	/* 현재 시간값 가져오기 seed값에 이용 */
	std::random_device rd;
	int temp = 0;
	int sourceIndex = 0;
	int destIndex = 0;

	mt19937_64 mtRand(rd()); // 32비트 난수생성기 64비트는 mt19937_64

	uniform_int_distribution<int> indexRange(0, 99);  
	uniform_int_distribution<int> numRange(20, 99);

	for (int i = 0; i < TestSystem::MAX_DATA_NUM; ++i)
	{
		sourceIndex = indexRange(mtRand);
		destIndex = indexRange(mtRand);

		temp = mData[sourceIndex];
		mData[sourceIndex] = mData[destIndex];
		mData[destIndex] = temp;
	}

	for (int i = 0; i < numRange(mtRand); ++i)
	{
		mRedBlack->InsertNode(mData[i]);
	}
}
