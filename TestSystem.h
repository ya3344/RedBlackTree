#pragma once
class TestSystem
{
public:
	explicit TestSystem(class RedBlackClass* redBlack);
	~TestSystem();

public:
	enum eDataIndex
	{
		MAX_DATA_NUM = 100,
	};

public:
	void RandomInsert();
public:
	class RedBlackClass* mRedBlack = nullptr;
	int mData[MAX_DATA_NUM];
};

