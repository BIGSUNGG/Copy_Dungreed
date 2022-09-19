#pragma once
class GraySkel : public Monster
{
public:
	GraySkel(int level, int num);

	void AI() override;
	virtual void TileBlockCollision(shared_ptr<Tile> tile) override;

protected:
	float _targetDistanceGround = 100.0f;
	float _targetDistanceJumping = 20.0f;
};

