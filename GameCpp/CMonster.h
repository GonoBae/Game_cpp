#pragma once
#include "CObject.h"
class CMonster :
    public CObject
{
private:
    float m_fSpeed;
    
    Vec2 m_vCenterPos; // 중심점
    float m_fMaxDistance; // 최대 이동거리
    int m_iDir; // 1 , -1
public:
    CMonster();
    ~CMonster();

    virtual void update();

    float GetSpeed() { return m_fSpeed; }
    void SetSpeed(float _f) { m_fSpeed = _f; }
    void SetCenterPos(Vec2 _vPos) { m_vCenterPos = _vPos; }
    void SetMoveDistance(float _f) { m_fMaxDistance = _f; }
};

