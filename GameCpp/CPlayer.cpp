#include "pch.h"
#include "CPlayer.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CMissile.h"
#include "CSceneMgr.h"
#include "CScene.h"
#include "CTexture.h"
#include "CPathMgr.h"

CPlayer::CPlayer()
	: m_pTex(nullptr)
{
	// Texture 로딩하기
	m_pTex = new CTexture;
	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += L"texture\\FLY.bmp";
	m_pTex->Load(strFilePath);
}

CPlayer::~CPlayer()
{
	if(nullptr != m_pTex) delete m_pTex;
}



void CPlayer::CreateMissile()
{
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();

	Vec2 vMissilePos = GetPos();
	vMissilePos.y -= GetScale().y / 2.f;
	CMissile* pMissile = new CMissile;
	pMissile->SetPos(vMissilePos);
	pMissile->SetScale(Vec2(25.f, 25.f));
	pMissile->SetDir(Vec2(0, 1));

	pCurScene->AddObject(pMissile, GROUP_TYPE::MISSILE);

	vMissilePos = GetPos();
	vMissilePos.x -= GetScale().x / 2.f;
	vMissilePos.y -= GetScale().y / 2.f;
	CMissile* pMissile1 = new CMissile;
	pMissile1->SetPos(vMissilePos);
	pMissile1->SetScale(Vec2(25.f, 25.f));
	pMissile1->SetDir(Vec2(-1, 1));
	
	pCurScene->AddObject(pMissile1, GROUP_TYPE::MISSILE);

	vMissilePos = GetPos();
	vMissilePos.x += GetScale().x / 2.f;
	vMissilePos.y -= GetScale().y / 2.f;
	CMissile* pMissile2 = new CMissile;
	pMissile2->SetPos(vMissilePos);
	pMissile2->SetScale(Vec2(25.f, 25.f));
	pMissile2->SetDir(Vec2(1, 1));
	
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

void CPlayer::render(HDC _dc)
{
	int iWidth = (int)m_pTex->Width();
	int iHeight = (int)m_pTex->Height();

	Vec2 vPos = GetPos();
	
	// 전체 픽셀을 옮겨옴
	//BitBlt(_dc, 
	//	(int)(vPos.x - (float)(iWidth / 2)), 
	//	(int)(vPos.y - (float)(iHeight / 2)), 
	//	iWidth, iHeight, m_pTex->GetDC(), 
	//	0, 0, SRCCOPY); // 좌상단 좌표 , 가로 세로 길이, DC, 옮길이미지 좌상단

	// 지정한 조건의 색은 투명처리
	TransparentBlt(_dc,
		(int)(vPos.x - (float)(iWidth / 2)),
		(int)(vPos.y - (float)(iHeight / 2)),
		iWidth, iHeight, m_pTex->GetDC(),
		0, 0, iWidth, iHeight,
		RGB(255, 0, 255));
}
