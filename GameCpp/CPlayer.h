#pragma once
#include "CObject.h"

class CTexture;

class CPlayer :
    public CObject
{
private:
    CTexture* m_pTex;

    void CreateMissile();

public:
    CPlayer();
    ~CPlayer();

    virtual void update();
    virtual void render(HDC _dc);

};

