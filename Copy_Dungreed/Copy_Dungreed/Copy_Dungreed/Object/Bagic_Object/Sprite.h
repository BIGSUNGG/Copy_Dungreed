#pragma once
class Sprite : public Quad
{
public:
	Sprite(wstring file, Vector2 maxFrame = { 1,1 });
	~Sprite();

	virtual void Update() override;
	virtual void Render() override;
	virtual void CreateVertices() override;

	Vector2 GetFrameHalfSize();

	void SetCurFrame(Vector2 frame) { _frameBuffer->_data._curFrame = frame; }
	void SetActionToFrameBuffer(Action::Clip clip);
	void SetActionToActionBuffer(Action::Clip clip);

private:
	shared_ptr<ActionBuffer> _actionBuffer;
	shared_ptr<FrameBuffer> _frameBuffer;
	Vector2 _maxFrame = { 1,1 };
};

