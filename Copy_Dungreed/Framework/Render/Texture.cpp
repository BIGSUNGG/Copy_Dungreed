#include "framework.h"
#include "Texture.h"

unordered_map<wstring, shared_ptr<Texture>> Texture::_texturesMap;

Texture::Texture(Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> srv, ScratchImage& image)
    :_srv(srv)
    , _image(std::move(image))
{
}

Texture::~Texture()
{
}

shared_ptr<Texture>& Texture::Add(wstring file)
{
    if (_texturesMap.count(file) > 0)
        return _texturesMap[file];

    ScratchImage image;
    LoadFromWICFile(file.data(), WIC_FLAGS_NONE, nullptr, image);
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> srv;

    CreateShaderResourceView(DEVICE.Get(), image.GetImages(), image.GetImageCount(), image.GetMetadata(),
        srv.GetAddressOf());

    shared_ptr<Texture> texture = make_shared<Texture>(srv, image);
    texture->_file = file;

	return _texturesMap[file] = texture;
}

shared_ptr<Texture>& Texture::Add(wstring file, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> srv)
{
	if (_texturesMap.count(file) > 0)
		return _texturesMap[file];

	ScratchImage image;

	shared_ptr<Texture> texture = make_shared<Texture>(srv, image);

	return _texturesMap[file] = texture;
}

void Texture::Set(UINT slot)
{
    DEVICE_CONTEXT->PSSetShaderResources(slot, 1, _srv.GetAddressOf());
}

Vector2 Texture::GetSize()
{
    Vector2 v;
    v.x = static_cast<float>(_image.GetMetadata().width);
    v.y = static_cast<float>(_image.GetMetadata().height);

    return v;
}