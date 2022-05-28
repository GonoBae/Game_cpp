#pragma once
#include "CObject.h"



class CMissile :
    public CObject
{
private:
    float m_fTheta; // 각도로 방향을 정하자

public:
    CMissile();
    ~CMissile();

    virtual void update();
    virtual void render(HDC _dc);
    void SetDir(float _fTheta) { m_fTheta = _fTheta; }
};

