#include "pch.h"
#include "CScene_Start.h"

#include "CObject.h"

CScene_Start::CScene_Start()
{
}

CScene_Start::~CScene_Start()
{
}

void CScene_Start::Enter()
{
	// Object 추가
	CObject* pObj = new CObject;

	//m_arrObj[(UINT)GROUP_TYPE::DEFAULT].push_back(pObj); // protected 하면 바로 쓸 수 있지만 좋은 방법은 아닌 것 같음 -> 아무리 부모, 자식 이라도 바로 접근이 가능 -> 디버깅 힘듦

	pObj->SetPos(Vec2(640.f, 384.f));
	pObj->SetScale(Vec2(100.f, 100.f));
	AddObject(pObj, GROUP_TYPE::DEFAULT);

	
}

void CScene_Start::Exit()
{
}
