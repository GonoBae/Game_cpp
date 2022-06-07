#pragma once

// 컴파일 속도를 위해 헤더파일을 참조하지 않음 -> 둘 중 하나가 바뀌면 하나하나 봐줘야함 -> 컴파일 순서 때문에
// 헤더가 헤더를 참조하는 것은 최대한 방지해야 함
class CObject; // 전방선언은 타입 자체를 쓸 수는 없음 -> 포인터 써야함 (크기는 알기 때문)

class CScene
{
private:
	vector<CObject*> m_arrObj[(UINT)GROUP_TYPE::END]; // 부모포인터 타입으로는 자식들을 모두 받을 수 있음
													  // 오브젝트 저장 및 관리할 벡터를 그룹 개수만큼 선언
	wstring			 m_strName; // Scene 이름

public:
	CScene();
	virtual ~CScene(); // 꼭 알아두자. (상속시킬 부모는 소멸자를 virtual)

	void SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() { return m_strName; }

	virtual void Enter() = 0; // 순수 가상 함수를 가지고 있는 객체는 추상화 클래스라서 직접 객체생성불가
	virtual void Exit() = 0;

	void update();
	void finalupdate();
	void render(HDC _dc);


	void AddObject(CObject* _pObj, GROUP_TYPE _eType) // 헤더에 구현해서 inline 처리 (함수 호출비용 없음)
	{
		m_arrObj[(UINT)_eType].push_back(_pObj);
	}

	const vector<CObject*>& GetGroupObject(GROUP_TYPE _eType) // 그룹 자체를 주기위해 참조형 반환 (원본을 훼손하지 못하도록)
	{
		return m_arrObj[(UINT)_eType];
	}
};

