#include "framework.h"
#include "Sprite.h"

Sprite::Sprite(wstring file, Vector2 maxFrame)
: _maxFrame(maxFrame)
{
    // Texture 세팅
    _texture = Texture::Add(file);
    _size = _texture->GetSize();

    _frameBuffer = make_shared<FrameBuffer>();
    _frameBuffer->_data._maxFrame.x = maxFrame.x;
    _frameBuffer->_data._maxFrame.y = maxFrame.y;

    _actionBuffer = make_shared<ActionBuffer>();
    _actionBuffer->_data._maxSize = { _texture->GetSize().x , _texture->GetSize().y };

    CreateVertices();
    _vertexBuffer = make_shared<VertexBuffer>(_vertices.data(), sizeof(VertexUV), _vertices.size());
    _indexBuffer = make_shared<IndexBuffer>(_indices.data(), _indices.size());

    _vertexShader = ADD_VS(L"Shader/TextureVertexShader.hlsl");
    _pixelShader = ADD_PS(L"Shader/ActionShader.hlsl");

    _transform = make_shared<Transform>();
}

Sprite::~Sprite()
{
}

void Sprite::Update()
{
    Quad::Update();
}

void Sprite::Render()
{
    _frameBuffer->SetPSBuffer(0);
    _actionBuffer->SetPSBuffer(0);

    Quad::Render();
}

void Sprite::CreateVertices()
{
    Vector2 halfSize = _texture->GetSize() * 0.5f;
    halfSize.x /= _frameBuffer->_data._maxFrame.x;
    halfSize.y /= _frameBuffer->_data._maxFrame.y;

    _vertices.reserve(4);

    _vertices.emplace_back(-halfSize.x, halfSize.y, 0, 0);
    _vertices.emplace_back(halfSize.x, halfSize.y, 1, 0);
    _vertices.emplace_back(halfSize.x, -halfSize.y, 1, 1);
    _vertices.emplace_back(-halfSize.x, -halfSize.y, 0, 1);

    _indices.push_back(0);
    _indices.push_back(1);
    _indices.push_back(2);

    _indices.push_back(0);
    _indices.push_back(2);
    _indices.push_back(3);

}

Vector2 Sprite::GetFrameHalfSize()
{
    Vector2 src = GetHalfSize();
    src.x /= _maxFrame.x;
    src.y /= _maxFrame.y;

    return src;
}

void Sprite::SetActionToFrameBuffer(Action::Clip clip)
{
    // clip에 있는 정보:
    // startPos
    // size

    // frameBuffer
    // maxFrame
    // curFrame (0,4) -> (9,4)
    
    // clips.emplace_back(1200 * 0 + w * a, 1040 * 0.5f, w, h, Texture::Add(L"Resource/zelda.png"));
    // -> (0,4)
    float x = (int)(clip._startPos.x / clip._size.x) ; 
    float y = (int)(clip._startPos.y / clip._size.y);

    _frameBuffer->_data._curFrame = { x,y };
}

void Sprite::SetActionToActionBuffer(Action::Clip clip)
{
    _actionBuffer->_data._size = clip._size;
    _actionBuffer->_data._startPos = clip._startPos;
}
