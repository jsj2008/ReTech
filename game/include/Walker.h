#ifndef __Walker_H__
#define __Walker_H__

class Walker : public rt::Sprite
{
public:
	Walker();
	virtual ~Walker();

	virtual void Update(float iFrameTime);

protected:
	float mSpeed;
};

#endif