#include "pch.h"
#include "RedBlackClass.h"



RedBlackClass::RedBlackClass()
{
	// nilnode 생성
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

	// 노드가 비어있는 경우 루트노드에 삽입
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
	// 부모노드 등록
	insertNode->parent = tempNode;
	// nilNode 등록
	insertNode->left = mNilNode;
	insertNode->right = mNilNode;
	// 레드블랙트리 규칙에 따라 신규노드는 빨간색 삽입
	insertNode->color = NodeInfo::RED;
	// 노드 개수 증가
	++mNodeNum;
	//부모가 레드노드라면 노드 밸런싱
	if (insertNode->parent->color == NodeInfo::RED)
	{
		RedBlackInsert(insertNode);
	}
}

void RedBlackClass::DeleteNode(const int data)
{
	NodeInfo* tempNode = nullptr;
	NodeInfo* findDeleteNode = nullptr;
	NodeInfo* childNode = nullptr;
	bool isDeleteNode = false;
	BYTE color = NodeInfo::BLACK;

	findDeleteNode = mRootNode;
	if (findDeleteNode == nullptr)
	{
		MESSAGE_BOX(L"empty!");
		return;
	}

	// 삭제할 노드 서치
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
		CONSOLE_LOG("삭제하려는 노드를 찾을 수 없습니다.!");
		return;
	}

	// 자식노드가 없는 경우
	if (findDeleteNode->left == mNilNode && findDeleteNode->right == mNilNode)
	{
		if (findDeleteNode == mRootNode) // 삭제노드가 루트노드이고 자식노드도 없는 경우
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

		if (findDeleteNode->parent->left == findDeleteNode) // 삭제노드가 
		{
			findDeleteNode->parent->left = mNilNode;
		}
		else if (findDeleteNode->parent->right == findDeleteNode)
		{
			findDeleteNode->parent->right = mNilNode;
		}
		else
		{
			CONSOLE_ERROR_LOG("deleteNode find error!");
			return;
		}
		color = findDeleteNode->color;
		--mNodeNum;
		childNode = findDeleteNode->left;
		childNode->parent = findDeleteNode->parent;
		SafeDelete(findDeleteNode);

		// 레드블랙트리 밸런싱 작업 진행
		if (color == NodeInfo::BLACK)
		{
			// 자식이 없기 때문에 무조건 nil 노드이므로 left right 상관없이 전달.
			RedBlackDelete(childNode);
		}
	}
	//자식노드가 한쪽에만 있는 경우
	else if (findDeleteNode->left == mNilNode || findDeleteNode->right == mNilNode)
	{
		// 자식노드가 왼쪽에만 있는 경우
		if (findDeleteNode->left != mNilNode)
		{
			if (findDeleteNode->parent == nullptr) // 루트노드인 경우
			{
				mRootNode = findDeleteNode->left;
				mRootNode->parent = nullptr;
				mRootNode->color = NodeInfo::BLACK;
				SafeDelete(findDeleteNode);
				--mNodeNum;
				return;
			}

			// 부모노드의 자식왼쪽 노드가 삭제노드일 경우
			if (findDeleteNode->parent->left == findDeleteNode)
			{
				findDeleteNode->parent->left = findDeleteNode->left;
				findDeleteNode->left->parent = findDeleteNode->parent;
			}
			// 부모노드의 자식오른쪽 노드가 삭제노드일 경우
			else if (findDeleteNode->parent->right == findDeleteNode)
			{
				findDeleteNode->parent->right = findDeleteNode->left;
				findDeleteNode->left->parent = findDeleteNode->parent;
			}
			childNode = findDeleteNode->left;
		}
		// 자식노드가 오른쪽에만 있는 경우
		else if (findDeleteNode->right != mNilNode)
		{
			if (findDeleteNode->parent == nullptr) // 루트노드인 경우
			{
				mRootNode = findDeleteNode->right;
				mRootNode->parent = nullptr;
				mRootNode->color = NodeInfo::BLACK;
				SafeDelete(findDeleteNode);
				--mNodeNum;
				return;
			}

			// 부모노드의 자식왼쪽 노드가 삭제노드일 경우
			if (findDeleteNode->parent->left == findDeleteNode)
			{
				findDeleteNode->parent->left = findDeleteNode->right;
				findDeleteNode->right->parent = findDeleteNode->parent;
			}
			// 부모노드의 자식오른쪽 노드가 삭제노드일 경우
			else if (findDeleteNode->parent->right = findDeleteNode)
			{
				findDeleteNode->parent->right = findDeleteNode->right;
				findDeleteNode->right->parent = findDeleteNode->parent;
			}
			childNode = findDeleteNode->right;
		}
		color = findDeleteNode->color;
		--mNodeNum;
		SafeDelete(findDeleteNode);

		// 레드블랙트리 밸런싱 작업 진행
		if (color == NodeInfo::BLACK)
		{
			RedBlackDelete(childNode);
		}
	}
	// 양쪽 자식노드가 모두 있는 경우
	else if (findDeleteNode->left != mNilNode && findDeleteNode->right != mNilNode)
	{
		// 오른쪽 자식노드중 가장 작은 값으로 삭제노드를 교체 진행(교체하는 경우 값만 복사하여 진행)
		tempNode = findDeleteNode->right;
		while (true)
		{
			// 왼쪽 노드가 없으면 브레이크 교체할 노드 검색됨.
			if (tempNode->left == mNilNode)
				break;

			tempNode = tempNode->left;
		}

		// 삭제노드에 교체할 노드의 값 대입하여 노드를 삭제한것처럼 표현
		findDeleteNode->data = tempNode->data;
		// 삭제노드에 교체할 노드의 값이 대입되었기 때문에 교체노드는 삭제 진행.
		if (tempNode->parent->left == tempNode)
		{
			tempNode->parent->left = tempNode->right;
			tempNode->right->parent = tempNode->parent;
		}
		else if (tempNode->parent->right == tempNode)
		{
			tempNode->parent->right = tempNode->right;
			tempNode->right->parent = tempNode->parent;
		}
		--mNodeNum;
		color = tempNode->color;
		childNode = tempNode->right;
		SafeDelete(tempNode);

		// 레드블랙트리 밸런싱 작업 진행
		if (color == NodeInfo::BLACK)
		{
			// 마지막 리프노드 이기 때문에 자식노드가 무조건 nilnode 이기때문에 left right 상관없이 전달.
			RedBlackDelete(childNode);
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
	wprintf(L"deleteNode: %d ", deleteNode->data);
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

	// 부모가 있기 때문에 해당 함수에 들어왔기 때문에 예외처리 패스.
	while (pointNode != mRootNode && pointNode->parent->color != NodeInfo::BLACK)
	{
		parentNode = pointNode->parent;
		// 부모가 레드라는 것은 할아버지 노드가 있기 때문에 가능하기 때문에 예외처리 패스
		grandParentNode = parentNode->parent;
		// 삼촌 노드 검색
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

		// 할아버지 노드 기준으로 부모노드가 왼쪽에 있는지 오른쪽에 있는지 체크
		if (true == isLeft)
		{
			// 부모노드도 레드 삼촌레드도 레드
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
			// 부모노드도 레드 삼촌레드도 레드
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

void RedBlackClass::RedBlackDelete(NodeInfo* pointNode)
{
	NodeInfo* siblingNode = nullptr;

	if (nullptr == pointNode)
	{
		CONSOLE_ERROR_LOG("pointNode nullptr!\n");
		return;
	}

	while (true)
	{
		if (NodeInfo::RED == pointNode->color || pointNode == mRootNode)
		{
			pointNode->color = NodeInfo::BLACK;
			return;
		}

		// 부모노드를 기준으로 왼쪽인 경우
		if (pointNode == pointNode->parent->left)
		{
			siblingNode = pointNode->parent->right;
			// 삭제노드의 형제가 레드인 경우
			if (siblingNode->color == NodeInfo::RED)
			{
				siblingNode->color = NodeInfo::BLACK;
				pointNode->parent->color = NodeInfo::RED;
				LeftRotation(pointNode->parent);
			}
			// 삭제노드의 형제가 블랙인 경우
			else
			{
				// 자식노드가 모두 블랙인 경우
				if (siblingNode->left->color == NodeInfo::BLACK
					&& siblingNode->right->color == NodeInfo::BLACK)
				{
					siblingNode->color = NodeInfo::RED;
					pointNode = siblingNode->parent;
				}
				else
				{
					/* 형제노드 왼쪽자식이 레드인 경우 형제노드 기준으로 우회전하여 오른쪽자식이 
					레드인경우로 변경하여 부모노드기준으로 좌회전하여 밸런싱 가능하도록 작업.
					*/
					if (siblingNode->left->color == NodeInfo::RED)
					{
						siblingNode->left->color = NodeInfo::BLACK;
						siblingNode->color = NodeInfo::RED;
						RightRotation(siblingNode);
						siblingNode = siblingNode->parent;
					}
					siblingNode->color = pointNode->parent->color;
					pointNode->parent->color = NodeInfo::BLACK;
					siblingNode->right->color = NodeInfo::BLACK;
					LeftRotation(pointNode->parent);
					mRootNode->color = NodeInfo::BLACK;
					return;
				}
			}
		}
		// 부모노드를 기준으로 오른쪽인 경우
		else if (pointNode == pointNode->parent->right)
		{
			siblingNode = pointNode->parent->left;
			// 삭제노드의 형제가 레드인 경우
			if (siblingNode->color == NodeInfo::RED)
			{
				siblingNode->color = NodeInfo::BLACK;
				pointNode->parent->color = NodeInfo::RED;
				RightRotation(pointNode->parent);
			}
			// 삭제노드의 형제가 블랙인 경우
			else
			{
				// 자식노드가 모두 블랙인 경우
				if (siblingNode->left->color == NodeInfo::BLACK
					&& siblingNode->right->color == NodeInfo::BLACK)
				{
					siblingNode->color = NodeInfo::RED;
					pointNode = siblingNode->parent;
				}
				else
				{
					/* 형제노드 오른쪽자식이 레드인 경우 형제노드 기준으로 좌회전하여 왼쪽자식이
					레드인경우로 변경하여 부모노드기준으로 우회전하여 밸런싱 가능하도록 작업.
					*/
					if (siblingNode->right->color == NodeInfo::RED)
					{
						siblingNode->right->color = NodeInfo::BLACK;
						siblingNode->color = NodeInfo::RED;
						LeftRotation(siblingNode);
						siblingNode = siblingNode->parent;
					}
					siblingNode->color = pointNode->parent->color;
					pointNode->parent->color = NodeInfo::BLACK;
					siblingNode->left->color = NodeInfo::BLACK;
					RightRotation(pointNode->parent);
					mRootNode->color = NodeInfo::BLACK;
					return;
				}
			}
		}
	}
	
}

void RedBlackClass::RightRotation(NodeInfo* pointNode)
{
	if (nullptr == pointNode)
	{
		CONSOLE_ERROR_LOG("pointNode nullptr!\n");
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
	// 왼쪽 자식 노드의 오른쪽 자식 노드를 부모 노드의 왼쪽 자식으로 이동
	pointNode->left = leftChild->right;

	if (leftChild->right != mNilNode)
	{
		leftChild->right->parent = pointNode;
	}
	leftChild->parent = pointNode->parent;

	// 부모가 nullptr이면 이 노드는 root
	// 이 경우에는 왼쪽 자식을 root 노드로 만들어 회전
	if (pointNode->parent == nullptr)
		mRootNode = leftChild;
	else
	{
		// 왼쪽 자식 노드를 부모 노드가 있는 곳에 위치
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
	// 오른쪽 자식 노드의 왼쪽 자식 노드를 부모 노드의 오른쪽 자식으로 이동
	pointNode->right = rightChild->left;

	if (rightChild->left != mNilNode)
	{
		rightChild->left->parent = pointNode;
	}
	rightChild->parent = pointNode->parent;

	// 부모가 nullptr이면 이 노드는 root
	// 이 경우에는 왼쪽 자식을 root 노드로 만들어 회전
	if (pointNode->parent == nullptr)
		mRootNode = rightChild;
	else
	{
		// 왼쪽 자식 노드를 부모 노드가 있는 곳에 위치
		if (pointNode == pointNode->parent->left)
			pointNode->parent->left = rightChild;
		else
			pointNode->parent->right = rightChild;
	}

	rightChild->left = pointNode;
	pointNode->parent = rightChild;
}