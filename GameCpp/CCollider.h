#pragma once

class CObject;

class CCollider
{
private:
	CObject* m_pOwner; // collider 를 소유하고 있는 오브젝트

	Vec2 m_vOffsetPos; // 오브젝트로부터 상대적인 위치
	Vec2 m_vFinalPos; // finalupdate 에서 매 프레임마다 계산

	Vec2 m_vScale; // 충돌체 크기

public:
	CCollider();
	~CCollider();

	void finalupdate();
	void SetOffSetPos(Vec2 _vPos) { m_vOffsetPos = _vPos; }
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }

	Vec2 GetOffSetPos() { return m_vOffsetPos; }
	Vec2 GetScale() { return m_vScale; }

	void render(HDC _dc);

	friend class CObject;
};