#pragma once

// 1. 동일 프레임 내에서 같은 키에 대해 동일한 이벤트를 가져간다. (코드 순서로 인해 다른 이벤트를 가져갈 수 있음)
//    프레임 동기화

// 2. 키 입력 이벤트 처리 -> 최초 한 번만 동작? 계속 동작?
// tap , hold , away

enum class KEY_STATE
{
	NONE, // 아무것도 아닌 상태 (눌리지 않았고, 이전에도 눌리지 않음)
	TAP, // 막 누른 시점
	HOLD, // 누르고 있는
	AWAY, // 막 뗀 시점
};

enum class KEY
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
	Q, 
	W, 
	E, 
	R, 
	T,
	Y, 
	U, 
	I, 
	O, 
	P,
	A, 
	S, 
	D, 
	F, 
	G, 
	Z, 
	X, 
	C, 
	V, 
	B,
	ALT,
	LCTRL,
	LSHIFT,
	SPACE,
	ENTER,
	ESC,
	LAST, // enum 의 끝
};

struct tKeyInfo
{
	KEY_STATE eState; // 키의 상태
	bool	  bPrevPush; // 이전 프레임에 이 값이 눌렸나
};

class CKeyMgr
{
	SINGLE(CKeyMgr);
private:
	vector<tKeyInfo> m_vecKey; // vector

public:
	void init();
	void update();

	KEY_STATE GetKeyState(KEY _key) { return m_vecKey[(int)_key].eState; }
};

