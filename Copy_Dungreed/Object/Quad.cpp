#include "framework.h"
#include "Quad.h"

Quad::Quad()
{
}

Quad::Quad(wstring file, wstring vs, wstring ps)
    : _vs(vs)
    , _ps(ps)
{
    // Texture 세팅

    _texture = Texture::Add(file);
    _size = _texture->GetSize();

    CreateVertices();
    _vertexBuffer = make_shared<VertexBuffer>(_vertices.data(), sizeof(VertexUV), _vertices.size());
    _indexBuffer = make_shared<IndexBuffer>(_indices.data(), _indices.size());

    _vertexShader = ADD_VS(vs);
    _pixelShader = ADD_PS(ps);

    _transform = make_shared<Transform>();
}

Quad::~Quad()
{
}

void Quad::Update()
{
    _transform->UpdateWorld();
}

void Quad::Render()
{
    _transform->SetBuffer(0);

    _texture->Set(0);

    _vertexBuffer->IASetVertexBuffer(0);
    _indexBuffer->IASetIndexBuffer();

    IASetPT();

    _vertexShader->Set();
    _pixelShader->Set();

    DEVICE_CONTEXT->DrawIndexed(_indices.size(), 0, 0);

}

void Quad::ReverseToX()
{
    _vertices[0].uv.x = abs(_vertices[0].uv.x - 1);
    _vertices[1].uv.x = abs(_vertices[1].uv.x - 1);
    _vertices[2].uv.x = abs(_vertices[2].uv.x - 1);
    _vertices[3].uv.x = abs(_vertices[3].uv.x - 1);

    _vertexBuffer = make_shared<VertexBuffer>(_vertices.data(), sizeof(VertexUV), _vertices.size());
}

void Quad::ReverseToY()
{
    _vertices[0].uv.y = abs(_vertices[0].uv.y - 1);
    _vertices[1].uv.y = abs(_vertices[1].uv.y - 1);
    _vertices[2].uv.y = abs(_vertices[2].uv.y - 1);
    _vertices[3].uv.y = abs(_vertices[3].uv.y - 1);

    _vertexBuffer = make_shared<VertexBuffer>(_vertices.data(), sizeof(VertexUV), _vertices.size());
}

void Quad::Refresh()
{
    _size = _texture->GetSize();

    auto temp = _vertices;
    CreateVertices();

    for (int i = 0; i < _vertices.size(); i++)
    {
        _vertices[i].uv.x = temp[i].uv.x;
        _vertices[i].uv.y = temp[i].uv.y;
    }

    _vertexBuffer = make_shared<VertexBuffer>(_vertices.data(), sizeof(VertexUV), _vertices.size());
    _indexBuffer = make_shared<IndexBuffer>(_indices.data(), _indices.size());
}

void Quad::CreateVertices()
{
    Vector2 halfSize = _size * 0.5f;

    _vertices.clear();

    _vertices.emplace_back(-halfSize.x, halfSize.y,0,0); // 왼 위
    _vertices.emplace_back(halfSize.x, halfSize.y, 1, 0); // 오 위
    _vertices.emplace_back(-halfSize.x, -halfSize.y, 0, 1); // 왼 아래
    _vertices.emplace_back(halfSize.x, -halfSize.y, 1, 1); // 오 아래

    _indices.clear();
    _indices.push_back(0);
    _indices.push_back(1);
    _indices.push_back(2);

    _indices.push_back(2);
    _indices.push_back(1);
    _indices.push_back(3);
}

void Quad::SetTexture(wstring file)
{
    _texture = Texture::Add(file);
}

void Quad::SetVS(wstring vs)
{
    _vertexShader = ADD_VS(vs);
}

void Quad::SetPS(wstring ps)
{
    _pixelShader = ADD_PS(ps);
}
