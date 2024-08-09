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
	const Vector2 _tileSize = Vector2(5, 5); // 타일 블록의 크기
	const Vector2 _doorSize = Vector2(5, 5); // 문 블록의 크기

	const float _mapSizeRatio = 0.05f; // 맵 크기 비율

	shared_ptr<RenderTarget> _mapRtv; 
	shared_ptr<RenderTarget> _tileRtv;
	shared_ptr<RenderTarget> _doorRtv;
	shared_ptr<Quad> _mapBase; // 미니맵 베이스가될 텍스쳐

	shared_ptr<InstanceQuad> _tile; // 타일 미니맵 텍스쳐
	shared_ptr<InstanceQuad> _door; // 문 미니맵 텍스쳐
	vector<shared_ptr<Object>> _enemy; // 몬스터 미니맵 텍스쳐
	shared_ptr<Object> _player; // 플레이어 미니맵 텍스쳐
};

