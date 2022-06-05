#pragma once
// 화면에 나타나는 물체 (Game or UI)

class CCollider;

class CObject
{
private:
	Vec2 m_vPos;
	Vec2 m_vScale;

	CCollider* m_pCollider;

public:
	CObject();
	virtual ~CObject();

	void SetPos(Vec2 _vPos) { m_vPos = _vPos; }
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }

	Vec2 GetPos() { return m_vPos; }
	Vec2 GetScale() { return m_vScale; }
	CCollider* GetCollider() { return m_pCollider; }

	virtual void update() = 0;
	virtual void finalupdate() final; // 자식 클래스가 더이상 오버라이딩 할 수 없음
	virtual void render(HDC _dc);
	void component_render(HDC _dc);

	void CreateCollider();

	
};

