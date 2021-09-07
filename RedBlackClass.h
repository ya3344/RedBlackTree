#pragma once
class RedBlackClass
{
public:
	struct NodeInfo
	{
		enum eCOLOR_INDEX
		{
			BLACK = 0,
			RED,
		};
		int data = 0;
		NodeInfo* left = nullptr;
		NodeInfo* right = nullptr;
		NodeInfo* parent = nullptr;
		unsigned char color = BLACK;
	};

public:
	RedBlackClass();
	~RedBlackClass();

public:
	void InsertNode(const int data);
	void DeleteNode(const int data);
	void InorderPrint(NodeInfo* node);
	void AllDeleteNode(NodeInfo* node);
	WORD GetNodeNum() const { return mNodeNum; }

// 레드블랙 트리 관련 함수
public:
	void RedBlackInsert(NodeInfo* pointNode);
	void RightRotation(NodeInfo* pointNode);
	void LeftRotation(NodeInfo* pointNode);

public:
	NodeInfo* GetRootNode() const { return mRootNode; }
	NodeInfo* GetNilNode() const { return mNilNode; }

private:
	NodeInfo* mRootNode = nullptr;
	NodeInfo* mNilNode = nullptr;
	WORD mNodeNum = 0;
};

