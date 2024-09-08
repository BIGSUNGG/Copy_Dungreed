#pragma once
class UI_Map : public UI
{
public:
	UI_Map();

	virtual void PreRender() override;
	virtual void Update() override;
	virtual void Render() override;

	virtual void Refresh() override;

protected:
	map<shared_ptr<Map>, bool> _visited; // 방문한 맵 리스트

	shared_ptr<RenderTarget> _filter;
	shared_ptr<Quad> _filterQuad;
	shared_ptr<Quad> _mapBase;
	shared_ptr<UI_Button> _exitButton;
	shared_ptr<InstanceQuad> _mapBlock; // 맵 표시하는 텍스쳐
	shared_ptr<InstanceQuad> _verticalLine; // 맵에서 위 아래로 연결된 것을 표시하는 텍스쳐
	shared_ptr<InstanceQuad> _horizonLine; // 맵에서 좌우로 연결된 것을 표시하는 텍스쳐

	shared_ptr<Quad> _blinkBlock; // 현재 맵을 표시해주는 텍스쳐
	bool _blink = true; //_blinkBlock이 나와있는지
	const float _blinkDelay = 0.5f; // _blinkBlock이 꺼지고 켜지는 딜레이
	float _blinkRunTime = 0.0f;

};
