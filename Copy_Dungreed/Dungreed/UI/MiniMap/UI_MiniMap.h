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
	const Vector2 _tileSize = Vector2(5, 5);
	const Vector2 _doorSize = Vector2(5, 5);

	const float _mapSizeRatio = 0.05f;

	shared_ptr<RenderTarget> _mapRtv;
	shared_ptr<RenderTarget> _tileRtv;
	shared_ptr<RenderTarget> _doorRtv;
	shared_ptr<Quad> _mapBase;

	shared_ptr<InstanceQuad> _tile;
	shared_ptr<InstanceQuad> _door;
	vector<shared_ptr<Object>> _enemy;
	shared_ptr<Object> _player;
};

