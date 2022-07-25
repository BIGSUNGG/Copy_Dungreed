#pragma once

struct VertexPos
{
    VertexPos()
    : pos(0,0,0)
    {}

    DirectX::XMFLOAT3 pos;
};

struct VertexUV
{
    VertexUV() {}
    VertexUV(float x, float y, float u, float v)
    : pos(x,y,0)
    , uv(u,v)
    {}

    DirectX::XMFLOAT3 pos = { 0,0,0 };
    DirectX::XMFLOAT2 uv = { 0,0 };
};