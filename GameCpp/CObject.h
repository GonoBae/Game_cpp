#pragma once
// 화면에 나타나는 물체

class CObject
{
private:
	Vec2 m_vPos;
	Vec2 m_vScale;

public:
	CObject();
	virtual ~CObject();

	void SetPos(Vec2 _vPos) { m_vPos = _vPos; }
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }

	Vec2 GetPos() { return m_vPos; }
	Vec2 GetScale() { return m_vScale; }

	virtual void update() = 0;
	virtual void render(HDC _dc);
};

