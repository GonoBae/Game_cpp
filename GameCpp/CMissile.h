#pragma once
#include "CObject.h"



class CMissile :
    public CObject
{
private:
    float m_fTheta; // 각도로 방향을 정하자
    Vec2 m_vDir; // 방향

public:
    CMissile();
    ~CMissile();

    virtual void update();
    virtual void render(HDC _dc);
    
    void SetDir(float _fTheta) { m_fTheta = _fTheta; }
    void SetDir(Vec2 _vDir) 
    {
        m_vDir = _vDir; 
        m_vDir.Normalize();
    }
};

