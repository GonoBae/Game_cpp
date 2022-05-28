#pragma once
#include "CObject.h"
class CPlayer :
    public CObject
{
private:
    void CreateMissile();

public:
    virtual void update();


};

