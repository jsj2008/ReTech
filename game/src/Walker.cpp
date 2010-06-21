#include "GameCommonIncludes.h"
#include "Walker.h"

Walker::Walker()
	: mSpeed(50.0f)
{
	mLayer = 10;
	SetResource("./media/redist/sprites/actors/zombie_jaw_body.tga");
}

Walker::~Walker()
{

}

void Walker::Update( float iFrameTime )
{
	SetWorldPosition(GetWorldPosition() + sf::Vector2f(mSpeed * iFrameTime, 0));
}