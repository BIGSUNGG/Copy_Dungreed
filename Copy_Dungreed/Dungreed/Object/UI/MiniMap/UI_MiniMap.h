#pragma once
class UI_MiniMap : public UI
{
public:
	UI_MiniMap();

	virtual void Update() override;
	virtual void PreRender() override;
	virtual void Render() override;

	virtual void Refresh();

protected:
	shared_ptr<RenderTarget> _rtv;
	shared_ptr<Quad> _rtvQuad;

	const Vector2 _miniTileSize = Vector2(500, 500);
	shared_ptr<InstanceQuads> _miniTile;
	shared_ptr<InstanceQuads> _miniPlayer;
	shared_ptr<InstanceQuads> _miniEnemy;
};

