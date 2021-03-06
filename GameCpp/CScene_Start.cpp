#include "pch.h"
#include "CScene_Start.h"

#include "CObject.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "CCore.h"

#include "CPathMgr.h"
#include "CTexture.h"

#include "CCollisionMgr.h"

CScene_Start::CScene_Start()
{
}

CScene_Start::~CScene_Start()
{
}

void CScene_Start::Enter()
{
	// Player Object 추가
	CObject* pObj = new CPlayer;

	//m_arrObj[(UINT)GROUP_TYPE::DEFAULT].push_back(pObj); // protected 하면 바로 쓸 수 있지만 좋은 방법은 아닌 것 같음 -> 아무리 부모, 자식 이라도 바로 접근이 가능 -> 디버깅 힘듦

	pObj->SetPos(Vec2(640.f, 384.f));
	pObj->SetScale(Vec2(100.f, 100.f));
	AddObject(pObj, GROUP_TYPE::PLAYER);

	// 몬스터 배치
	int iMonCount = 10;
	float fMoveDist = 25.f;
	float fObjScale = 50.f;

	Vec2 vResolution = CCore::GetInst()->GetResolution(); // 생성하자마자 = 하면 복사생성자
	CMonster* pMonsterObj = nullptr;
	float fTerm = (vResolution.x - ((fObjScale + fMoveDist) * 2)) / (iMonCount - 1);
	for (int i = 0; i < iMonCount; ++i)
	{
		// Monster Object 추가
		pMonsterObj = new CMonster;
		pMonsterObj->SetPos(Vec2((fObjScale + fMoveDist) + fTerm * i, 50.f));
		pMonsterObj->SetCenterPos(pMonsterObj->GetPos());
		pMonsterObj->SetScale(Vec2(fObjScale, fObjScale));
		AddObject(pMonsterObj, GROUP_TYPE::MONSTER);
	}

	// 충돌지정
	// Player 그룹과 Monster 그룹 간의 충돌체크
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);



}

void CScene_Start::Exit()
{
	CCollisionMgr::GetInst()->Reset();
}
