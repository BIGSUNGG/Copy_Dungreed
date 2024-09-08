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
	map<shared_ptr<Map>, bool> _visited; // �湮�� �� ����Ʈ

	shared_ptr<RenderTarget> _filter;
	shared_ptr<Quad> _filterQuad;
	shared_ptr<Quad> _mapBase;
	shared_ptr<UI_Button> _exitButton;
	shared_ptr<InstanceQuad> _mapBlock; // �� ǥ���ϴ� �ؽ���
	shared_ptr<InstanceQuad> _verticalLine; // �ʿ��� �� �Ʒ��� ����� ���� ǥ���ϴ� �ؽ���
	shared_ptr<InstanceQuad> _horizonLine; // �ʿ��� �¿�� ����� ���� ǥ���ϴ� �ؽ���

	shared_ptr<Quad> _blinkBlock; // ���� ���� ǥ�����ִ� �ؽ���
	bool _blink = true; //_blinkBlock�� �����ִ���
	const float _blinkDelay = 0.5f; // _blinkBlock�� ������ ������ ������
	float _blinkRunTime = 0.0f;

};
