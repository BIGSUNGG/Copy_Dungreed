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
	shared_ptr<RenderTarget> _filter;
	shared_ptr<Quad> _filterQuad;
	shared_ptr<Quad> _mapBase;
	shared_ptr<InstanceQuad> _mapBlock;
	shared_ptr<InstanceQuad> _verticalLine;
	shared_ptr<InstanceQuad> _horizonLine;

};

