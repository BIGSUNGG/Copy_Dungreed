#pragma once
class Chest : public Ect
{
public:
	Chest(int type, int num);

	virtual void Update() override;

	virtual void Interaction() override;

	virtual void SetOwnerMap(shared_ptr<Map> map);	
	virtual void SetOpenTexture(const wstring& image) { _openImage = image; }

protected:
	virtual void MakeRandomItem();
	
protected:
	shared_ptr<MovementComponent> _movement;
	shared_ptr<DropItem> _dropItem;
	wstring _openImage;
	bool _spawn = false;

};

