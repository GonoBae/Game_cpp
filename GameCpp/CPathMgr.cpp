#include "pch.h"
#include "CPathMgr.h"
#include "CCore.h"



CPathMgr::CPathMgr()
	: m_szContentPath{}
{
}

CPathMgr::~CPathMgr()
{
}

void CPathMgr::init()
{
	GetCurrentDirectory(255, m_szContentPath);

	// 상위폴더로
	int iLen = wcslen(m_szContentPath);
	for (int i = iLen - 1; i >= 0; --i)
	{
		if ('\\' == m_szContentPath[i])
		{
			m_szContentPath[i] = '\0';
			break;
		}
	}

	// + bin\\content\\ //
	wcscat_s(m_szContentPath, 255, L"\\bin\\content\\");

	

	//SetWindowText(CCore::GetInst()->GetMainHwnd(), m_szContentPath);
}
