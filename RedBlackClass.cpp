#include "pch.h"
#include "RedBlackClass.h"



RedBlackClass::RedBlackClass()
{
	// nilnode ����
	mNilNode = new NodeInfo;
	mNilNode->data = -1;
	if (mNilNode == nullptr)
	{
		CONSOLE_ERROR_LOG("mNilNode alloc lack!");
		return;
	}
}

RedBlackClass::~RedBlackClass()
{
	AllDeleteNode(mRootNode);
	SafeDelete(mNilNode);
}

void RedBlackClass::InsertNode(const int data)
{
	NodeInfo* tempNode = nullptr;
	NodeInfo* insertNode = nullptr;
	WORD depth = 0;

	// ��尡 ����ִ� ��� ��Ʈ��忡 ����
	if (mRootNode == nullptr || mNodeNum == 0)
	{
		mRootNode = new NodeInfo;
		if (mRootNode == nullptr)
		{
			CONSOLE_ERROR_LOG("RootNode alloc lack!");
			return;
		}
		mRootNode->data = data;
		mRootNode->left = mNilNode;
		mRootNode->right = mNilNode;
		mRootNode->color = NodeInfo::BLACK;
		++mNodeNum;
		return;
	}

	tempNode = mRootNode;

	while (true)
	{
		if (tempNode == nullptr)
		{
			CONSOLE_ERROR_LOG("tempNode alloc lack!");
			return;
		}

		if (data == tempNode->data)
		{
			MESSAGE_BOX(L"Ovelap Node Insert No!");
			return;
		}
		if (data < tempNode->data)
		{
			if (tempNode->left == mNilNode)
			{
				tempNode->left = new NodeInfo;
				if (tempNode->left == nullptr)
				{
					CONSOLE_ERROR_LOG("tempNode->left alloc lack!");
					return;
				}
				insertNode = tempNode->left;
				break;
			}
			tempNode = tempNode->left;
		}
		else if (data > tempNode->data)
		{
			// visualization
			if (tempNode->right == mNilNode)
			{
				tempNode->right = new NodeInfo;
				if (tempNode->right == nullptr)
				{
					CONSOLE_ERROR_LOG("tempNode->right alloc lack!");
					return;
				}
				insertNode = tempNode->right;
				break;
			}
			tempNode = tempNode->right;
		}
	}

	if (nullptr == insertNode)
	{
		CONSOLE_ERROR_LOG("insertNode Error!");
		return;
	}
	// data push
	insertNode->data = data;
	// �θ��� ���
	insertNode->parent = tempNode;
	// nilNode ���
	insertNode->left = mNilNode;
	insertNode->right = mNilNode;
	// �����Ʈ�� ��Ģ�� ���� �űԳ��� ������ ����
	insertNode->color = NodeInfo::RED;
	// ��� ���� ����
	++mNodeNum;
	//�θ� �������� ��� �뷱��
	if (insertNode->parent->color == NodeInfo::RED)
	{
		RedBlackInsert(insertNode);
	}
}

void RedBlackClass::DeleteNode(const int data)
{
	NodeInfo* tempNode = nullptr;
	NodeInfo* findDeleteNode = nullptr;
	bool isDeleteNode = false;

	findDeleteNode = mRootNode;
	if (findDeleteNode == nullptr)
	{
		MESSAGE_BOX(L"empty!");
		return;
	}

	// ������ ��� ��ġ
	while (findDeleteNode)
	{
		if (data == findDeleteNode->data)
		{
			isDeleteNode = true;
			break;
		}

		if (data > findDeleteNode->data)
		{
			findDeleteNode = findDeleteNode->right;
		}
		else if (data < findDeleteNode->data)
		{
			findDeleteNode = findDeleteNode->left;
		}

		if (findDeleteNode == mNilNode)
		{
			isDeleteNode = false;
			break;
		}
	}

	if (isDeleteNode == false)
	{
		CONSOLE_LOG("�����Ϸ��� ��带 ã�� �� �����ϴ�.!");
		return;
	}

	// �ڽĳ�尡 ���� ���
	if (findDeleteNode->left == mNilNode && findDeleteNode->right == mNilNode)
	{
		if (findDeleteNode == mRootNode) // ������尡 ��Ʈ����̰� �ڽĳ�嵵 ���� ���
		{
			mRootNode = nullptr;
			SafeDelete(findDeleteNode);
			SafeDelete(mNilNode);
			--mNodeNum;
			return;
		}

		if (findDeleteNode->parent == nullptr)
		{
			CONSOLE_ERROR_LOG("DeleteNode parent nullptr!");
			return;
		}

		if (findDeleteNode->parent->left == findDeleteNode) // ������尡 
		{
			findDeleteNode->parent->left = mNilNode;
			SafeDelete(findDeleteNode);
			--mNodeNum;
			return;
		}
		else if (findDeleteNode->parent->right == findDeleteNode)
		{
			findDeleteNode->parent->right = mNilNode;
			SafeDelete(findDeleteNode);
			--mNodeNum;
			return;
		}
		else
		{
			CONSOLE_ERROR_LOG("deleteNode find error!");
			return;
		}
	}
	//�ڽĳ�尡 ���ʿ��� �ִ� ���
	else if (findDeleteNode->left == mNilNode || findDeleteNode->right == mNilNode)
	{
		// �ڽĳ�尡 ���ʿ��� �ִ� ���
		if (findDeleteNode->left != mNilNode)
		{
			if (findDeleteNode->parent == nullptr) // ��Ʈ����� ���
			{
				mRootNode = findDeleteNode->left;
				mRootNode->parent = nullptr;
				SafeDelete(findDeleteNode);
				--mNodeNum;
				return;
			}

			// �θ����� �ڽĿ��� ��尡 ��������� ���
			if (findDeleteNode->parent->left == findDeleteNode)
			{
				findDeleteNode->parent->left = findDeleteNode->left;
				findDeleteNode->left->parent = findDeleteNode->parent;
				SafeDelete(findDeleteNode);
				--mNodeNum;
				return;
			}
			// �θ����� �ڽĿ����� ��尡 ��������� ���
			else if (findDeleteNode->parent->right == findDeleteNode)
			{
				findDeleteNode->parent->right = findDeleteNode->left;
				findDeleteNode->left->parent = findDeleteNode->parent;
				SafeDelete(findDeleteNode);
				--mNodeNum;
				return;
			}
		}
		// �ڽĳ�尡 �����ʿ��� �ִ� ���
		else if (findDeleteNode->right != mNilNode)
		{
			if (findDeleteNode->parent == nullptr) // ��Ʈ����� ���
			{
				mRootNode = findDeleteNode->right;
				mRootNode->parent = nullptr;
				SafeDelete(findDeleteNode);
				--mNodeNum;
				return;
			}

			// �θ����� �ڽĿ��� ��尡 ��������� ���
			if (findDeleteNode->parent->left == findDeleteNode)
			{
				findDeleteNode->parent->left = findDeleteNode->right;
				findDeleteNode->right->parent = findDeleteNode->parent;
				SafeDelete(findDeleteNode);
				--mNodeNum;
				return;
			}
			// �θ����� �ڽĿ����� ��尡 ��������� ���
			else if (findDeleteNode->parent->right = findDeleteNode)
			{
				findDeleteNode->parent->right = findDeleteNode->right;
				findDeleteNode->right->parent = findDeleteNode->parent;
				SafeDelete(findDeleteNode);
				--mNodeNum;
				return;
			}
		}
	}
	// ���� �ڽĳ�尡 ��� �ִ� ���
	else if (findDeleteNode->left != mNilNode && findDeleteNode->right != mNilNode)
	{
		// ������ �ڽĳ���� ���� ���� ������ ������带 ��ü ����(��ü�ϴ� ��� ���� �����Ͽ� ����)
		tempNode = findDeleteNode->right;
		while (true)
		{
			// ���� ��尡 ������ �극��ũ ��ü�� ��� �˻���.
			if (tempNode->left == mNilNode)
				break;

			tempNode = tempNode->left;
		}

		// ������忡 ��ü�� ����� �� �����Ͽ� ��带 �����Ѱ�ó�� ǥ��
		findDeleteNode->data = tempNode->data;
		// ������忡 ��ü�� ����� ���� ���ԵǾ��� ������ ��ü���� ���� ����.
		if (tempNode->parent->left == tempNode)
		{
			tempNode->parent->left = tempNode->right;
			if (tempNode->right != mNilNode)
				tempNode->right->parent = tempNode->parent;

			SafeDelete(tempNode);
			--mNodeNum;
			return;
		}
		else if (tempNode->parent->right == tempNode)
		{
			tempNode->parent->right = tempNode->right;
			if (tempNode->right != mNilNode)
				tempNode->right->parent = tempNode->parent;

			SafeDelete(tempNode);
			--mNodeNum;
			return;
		}
	}
}

void RedBlackClass::InorderPrint(NodeInfo* node)
{
	NodeInfo* tempNode = nullptr;

	tempNode = node;

	if (tempNode == mNilNode)
		return;

	InorderPrint(node->left);
	wprintf(L" %d", node->data);
	InorderPrint(node->right);
}

void RedBlackClass::AllDeleteNode(NodeInfo* node)
{
	NodeInfo* deleteNode = nullptr;

	deleteNode = node;

	if (deleteNode == mNilNode)
		return;

	AllDeleteNode(deleteNode->left);
	AllDeleteNode(deleteNode->right);
	wprintf(L"deleteNode: %d", deleteNode->data);
	SafeDelete(deleteNode);
	--mNodeNum;
}

void RedBlackClass::RedBlackInsert(NodeInfo* pointNode)
{
	NodeInfo* parentNode = nullptr;
	NodeInfo* grandParentNode = nullptr;
	NodeInfo* uncleNode = nullptr;
	bool isLeft = false;

	if (nullptr == pointNode)
	{
		CONSOLE_ERROR_LOG("insertNode error!");
		return;
	}

	// �θ� �ֱ� ������ �ش� �Լ��� ���Ա� ������ ����ó�� �н�.
	while (pointNode != mRootNode && pointNode->parent->color != NodeInfo::BLACK)
	{
		parentNode = pointNode->parent;
		// �θ� ������ ���� �Ҿƹ��� ��尡 �ֱ� ������ �����ϱ� ������ ����ó�� �н�
		grandParentNode = parentNode->parent;
		// ���� ��� �˻�
		if (parentNode == grandParentNode->left)
		{
			uncleNode = grandParentNode->right;
			isLeft = true;
		}
		else if(parentNode == grandParentNode->right)
		{
			uncleNode = grandParentNode->left;
			isLeft = false;
		}
		else
		{
			CONSOLE_ERROR_LOG("unclNode not found!");
			return;
		}

		// �Ҿƹ��� ��� �������� �θ��尡 ���ʿ� �ִ��� �����ʿ� �ִ��� üũ
		if (true == isLeft)
		{
			// �θ��嵵 ���� ���̷��嵵 ����
			if (parentNode->color == NodeInfo::RED && uncleNode->color == NodeInfo::RED)
			{
				parentNode->color = NodeInfo::BLACK;
				uncleNode->color = NodeInfo::BLACK;
				grandParentNode->color = NodeInfo::RED;
				pointNode = grandParentNode;
			}
			else if (parentNode->color == NodeInfo::RED && uncleNode->color == NodeInfo::BLACK
				&& parentNode->right == pointNode)
			{
				LeftRotation(parentNode);
				pointNode = parentNode;
			}
			else if (parentNode->color == NodeInfo::RED && uncleNode->color == NodeInfo::BLACK
				&& parentNode->left == pointNode)
			{
				parentNode->color = NodeInfo::BLACK;
				grandParentNode->color = NodeInfo::RED;
				RightRotation(grandParentNode);
				pointNode = grandParentNode;
			}
		}
		else
		{
			// �θ��嵵 ���� ���̷��嵵 ����
			if (parentNode->color == NodeInfo::RED && uncleNode->color == NodeInfo::RED)
			{
				parentNode->color = NodeInfo::BLACK;
				uncleNode->color = NodeInfo::BLACK;
				grandParentNode->color = NodeInfo::RED;
				pointNode = grandParentNode;
			}
			else if (parentNode->color == NodeInfo::RED && uncleNode->color == NodeInfo::BLACK
				&& parentNode->left == pointNode)
			{
				RightRotation(parentNode);
				pointNode = parentNode;
			}
			else if (parentNode->color == NodeInfo::RED && uncleNode->color == NodeInfo::BLACK
				&& parentNode->right == pointNode)
			{
				parentNode->color = NodeInfo::BLACK;
				grandParentNode->color = NodeInfo::RED;
				LeftRotation(grandParentNode);
				pointNode = grandParentNode;
			}
		}
	}

	mRootNode->color = NodeInfo::BLACK;
}

void RedBlackClass::RightRotation(NodeInfo* pointNode)
{
	if (nullptr == pointNode)
	{
		CONSOLE_ERROR_LOG("parent nullptr!\n");
		return;
	}
	if (nullptr == mRootNode)
	{
		CONSOLE_ERROR_LOG("rootNode nullptr!\n");
		return;
	}
	NodeInfo* leftChild = pointNode->left;
	if (nullptr == leftChild)
	{
		CONSOLE_ERROR_LOG("leftChild nullptr!\n");
		return;
	}
	// ���� �ڽ� ����� ������ �ڽ� ��带 �θ� ����� ���� �ڽ����� �̵�
	pointNode->left = leftChild->right;

	if (leftChild->right != mNilNode)
	{
		leftChild->right->parent = pointNode;
	}
	leftChild->parent = pointNode->parent;

	// �θ� nullptr�̸� �� ���� root
	// �� ��쿡�� ���� �ڽ��� root ���� ����� ȸ��
	if (pointNode->parent == nullptr)
		mRootNode = leftChild;
	else
	{
		// ���� �ڽ� ��带 �θ� ��尡 �ִ� ���� ��ġ
		if (pointNode == pointNode->parent->left)
			pointNode->parent->left = leftChild;
		else
			pointNode->parent->right = leftChild;
	}

	leftChild->right = pointNode;
	pointNode->parent = leftChild;
}

void RedBlackClass::LeftRotation(NodeInfo* pointNode)
{
	if (nullptr == pointNode)
	{
		CONSOLE_ERROR_LOG("parent nullptr!\n");
		return;
	}
	if (nullptr == mRootNode)
	{
		CONSOLE_ERROR_LOG("rootNode nullptr!\n");
		return;
	}
	NodeInfo* rightChild = pointNode->right;
	if (nullptr == rightChild)
	{
		CONSOLE_ERROR_LOG("rightChild nullptr!\n");
		return;
	}
	// ������ �ڽ� ����� ���� �ڽ� ��带 �θ� ����� ������ �ڽ����� �̵�
	pointNode->right = rightChild->left;

	if (rightChild->left != mNilNode)
	{
		rightChild->left->parent = pointNode;
	}
	rightChild->parent = pointNode->parent;

	// �θ� nullptr�̸� �� ���� root
	// �� ��쿡�� ���� �ڽ��� root ���� ����� ȸ��
	if (pointNode->parent == nullptr)
		mRootNode = rightChild;
	else
	{
		// ���� �ڽ� ��带 �θ� ��尡 �ִ� ���� ��ġ
		if (pointNode == pointNode->parent->left)
			pointNode->parent->left = rightChild;
		else
			pointNode->parent->right = rightChild;
	}

	rightChild->left = pointNode;
	pointNode->parent = rightChild;
}