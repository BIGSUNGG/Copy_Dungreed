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
	map<shared_ptr<Map>, bool> _visited;

	shared_ptr<RenderTarget> _filter;
	shared_ptr<Quad> _filterQuad;
	shared_ptr<Quad> _mapBase;
	shared_ptr<UI_Button> _exitButton;
	shared_ptr<InstanceQuad> _mapBlock;
	shared_ptr<InstanceQuad> _verticalLine;
	shared_ptr<InstanceQuad> _horizonLine;

	shared_ptr<Quad> _blinkBlock;
	bool _blink = true;
	const float _blinkDelay = 0.5f;
	float _blinkRunTime = 0.0f;

};
