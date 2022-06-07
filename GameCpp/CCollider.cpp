#include "pch.h"
#include "CCollider.h"

#include "CObject.h"
#include "CCore.h"

#include "SelectGDI.h"

UINT CCollider::g_iNextID = 0;

// 생성될 때 마다 아이디 가지고 하나씩 증가시켜 절대 중복안됨
CCollider::CCollider()
	: m_pOwner(nullptr) , m_iID(g_iNextID++)
{
}

CCollider::~CCollider()
{
}

void CCollider::finalupdate()
{
	// Object 의 위치를 따라가자.
	Vec2 vObjectPos = m_pOwner->GetPos();
	m_vFinalPos = vObjectPos + m_vOffsetPos;
}

void CCollider::render(HDC _dc)
{
	// 테두리만 그려야 좋음
	// 1. 점찍고 선긋기
	// 2. hollow brush (공백 브러쉬) 사용하기 --> 채택

	// 임시객체 , 지역변수
	SelectGDI pen(_dc, PEN_TYPE::GREEN); 
	SelectGDI brush(_dc, BRUSH_TYPE::HOLLOW);

	Rectangle(_dc,
		(int)(m_vFinalPos.x - m_vScale.x / 2.f),
		(int)(m_vFinalPos.y - m_vScale.y / 2.f), 
		(int)(m_vFinalPos.x + m_vScale.x / 2.f),
		(int)(m_vFinalPos.y + m_vScale.y / 2.f));
}
