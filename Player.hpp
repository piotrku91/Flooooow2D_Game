#pragma once
#include "Collid.h"

class Body: public Collid
{
    public:
    bool onGround;
    bool onAir;
    bool isJumping=false;



};


class Player: public Body
{
    public:
    




};