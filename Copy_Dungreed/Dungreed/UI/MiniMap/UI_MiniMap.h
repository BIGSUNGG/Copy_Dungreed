#pragma once
class UI_MiniMap : public UI
{
public:
	UI_MiniMap();

	virtual void Update() override;
	virtual void PreRender() override;
	virtual void Render() override;

	virtual void Refresh() override;

protected:
	const Vector2 _miniTileSize = Vector2(5, 5);
	const float _miniMapSizeRatio = 0.05f;

	shared_ptr<RenderTarget> _miniMapRtv;
	shared_ptr<RenderTarget> _miniTileRtv;
	shared_ptr<Quad> _miniMapBase;

	shared_ptr<InstanceQuad> _miniTile;
	vector<shared_ptr<Object>> _miniEnemy;
	shared_ptr<Object> _miniPlayer;
};

