#include "pch.h"
#include "CPlayer.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CMissile.h"
#include "CSceneMgr.h"
#include "CScene.h"

void CPlayer::CreateMissile()
{
	Vec2 vMissilePos = GetPos();
	vMissilePos.y -= GetScale().y / 2.f;
	CMissile* pMissile = new CMissile;
	pMissile->SetPos(vMissilePos);
	pMissile->SetScale(Vec2(25.f, 25.f));
	pMissile->SetDir(PI / 2.f);

	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	pCurScene->AddObject(pMissile, GROUP_TYPE::MISSILE);

	Vec2 vMissilePos1 = GetPos();
	vMissilePos1.x -= GetScale().x / 2.f;
	vMissilePos1.y -= GetScale().y / 2.f;
	CMissile* pMissile1 = new CMissile;
	pMissile1->SetPos(vMissilePos1);
	pMissile1->SetScale(Vec2(25.f, 25.f));
	pMissile1->SetDir((3 * PI / 4.f));

	
	pCurScene->AddObject(pMissile1, GROUP_TYPE::MISSILE);

	Vec2 vMissilePos2 = GetPos();
	vMissilePos2.x += GetScale().x / 2.f;
	vMissilePos2.y -= GetScale().y / 2.f;
	CMissile* pMissile2 = new CMissile;
	pMissile2->SetPos(vMissilePos2);
	pMissile2->SetScale(Vec2(25.f, 25.f));
	pMissile2->SetDir(PI / 4.f);

	
	pCurScene->AddObject(pMissile2, GROUP_TYPE::MISSILE);
}

void CPlayer::update()
{
	Vec2 vPos = GetPos();

	if (KEY_HOLD(KEY::W))
	{
		vPos.y -= 200.f * fDT;
	}
	if (KEY_HOLD(KEY::S))
	{
		vPos.y += 200.f * fDT;
	}
	if (KEY_HOLD(KEY::A))
	{
		vPos.x -= 200.f * fDT;
	}
	if (KEY_HOLD(KEY::D))
	{
		vPos.x += 200.f * fDT;
	}

	if (KEY_TAP(KEY::SPACE))
	{
		CreateMissile();
	}

	SetPos(vPos);
}
