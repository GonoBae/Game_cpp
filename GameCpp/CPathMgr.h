#pragma once


class CPathMgr
{
	SINGLE(CPathMgr);
private:
	wchar_t m_szContentPath[255]; // 윈도우에서도 255로 제한이 걸려있기에 더 길게 만들어 줄 필요가 없음

public:
	void init();
	const wchar_t* GetContentPath() { return m_szContentPath; }
};

