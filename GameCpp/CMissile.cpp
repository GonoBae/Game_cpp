#include "pch.h"
#include "CMissile.h"

#include "CTimeMgr.h"

CMissile::CMissile()
	: m_fTheta(0.f), m_vDir(Vec2(0.f, 0.f))
{
	CreateCollider();
}

CMissile::~CMissile()
{

}

void CMissile::update()
{
	Vec2 vPos = GetPos();
	
	// 각도를 통한 이동
	//vPos.x += 400.f * fDT * cos(m_fTheta);
	//vPos.y -= 400.f * fDT * sin(m_fTheta);

	vPos.x += 400.f * fDT * m_vDir.x;
	vPos.y -= 400.f * fDT * m_vDir.y;

	SetPos(vPos);
}

void CMissile::render(HDC _dc)
{
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();
	Ellipse(_dc, (int)(vPos.x - vScale.x / 2.f), (int)(vPos.y - vScale.y / 2.f),
		(int)(vPos.x + vScale.x / 2.f), (int)(vPos.y + vScale.y / 2.f));
}
