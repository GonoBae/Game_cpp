#pragma once
#include "CScene.h"
class CScene_Start :
    public CScene
{
public:
    CScene_Start();
    ~CScene_Start();

    virtual void Enter(); // virtual 없어도 되지만 구분하기 위해 적어주자.
    virtual void Exit();
};

