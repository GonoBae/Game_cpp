#pragma once

class CCollider;

class CCollisionMgr
{
	SINGLE(CCollisionMgr)
private:
	// 충돌체 간의 이전 프레임 충돌 정보
	UINT m_arrCheck[(UINT)GROUP_TYPE::END]; // 그룹간의 충돌 체크 매트릭스

	void CollisionGroupUpdate(GROUP_TYPE _eLeft, GROUP_TYPE _eRight);

public:
	void init();
	void update();
	void CheckGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight);
	void Reset() { memset(m_arrCheck, 0, sizeof(UINT) * (UINT)GROUP_TYPE::END); } // memset -> 지정한 주소를 지정한 값으로 세팅

	bool IsCollision(CCollider* _pLeftCol, CCollider* _pRightCol);
};

