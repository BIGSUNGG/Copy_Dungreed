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
	const Vector2 _tileSize = Vector2(5, 5); // Ÿ�� ����� ũ��
	const Vector2 _doorSize = Vector2(5, 5); // �� ����� ũ��

	const float _mapSizeRatio = 0.05f; // �� ũ�� ����

	shared_ptr<RenderTarget> _mapRtv; 
	shared_ptr<RenderTarget> _tileRtv;
	shared_ptr<RenderTarget> _doorRtv;
	shared_ptr<Quad> _mapBase; // �̴ϸ� ���̽����� �ؽ���

	shared_ptr<InstanceQuad> _tile; // Ÿ�� �̴ϸ� �ؽ���
	shared_ptr<InstanceQuad> _door; // �� �̴ϸ� �ؽ���
	vector<shared_ptr<Object>> _enemy; // ���� �̴ϸ� �ؽ���
	shared_ptr<Object> _player; // �÷��̾� �̴ϸ� �ؽ���
};

