#pragma once
class CMissileCheckPlayerCollisionBehavior:
	public IBehavior
{
public:
	CMissileCheckPlayerCollisionBehavior();
	~CMissileCheckPlayerCollisionBehavior();
	void Update(float dt_);
};

