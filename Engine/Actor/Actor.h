#ifndef __ACTOR_H__
#define __ACTOR_H__

#include "RTTI.h"

#include "Math/Vector2.h"
#include "Math/Color.h"

class Level;
class ENGINE_API Actor : public RTTI
{
	friend class Level;
	RTTI_DECLARATIONS(Actor, RTTI)

#pragma region Ư�� �ɹ� �Լ�
public:
	Actor(const char* pImage = "", Color color = Color::Color_White, const Vector2& position = Vector2::Zero);
	virtual ~Actor();
#pragma endregion

#pragma region ���� �Լ�
	/*
	*		�̺�Ʈ �Լ�
	*/
	virtual void BeginPlay();				// ��ü �����ֱ⿡ 1���� ȣ��(�ʱ�ȭ ����).
	virtual void Tick(float deltaTime = 0);	// �����Ӹ��� ȣ�� (�ݺ��� �۾�/���Ӽ��� �ʿ��� �۾�).
	virtual void Render();					// �׸��� �Լ�.

	/*
	*		�Ϲ� �Լ�
	*/
	void SetPosition(const Vector2& newPosition);
	Vector2 Position() const;

	void SetSortingOrder(unsigned int sortingOrder);
	
	/* Owner ���� �Լ� */
	void	SetOwner(Level* newOwner);
	virtual Level*	GetOwner() const;

	/* ���� �Լ� */
	void QuitGame();

	/* ��ü ���� �Լ� */
	void Destroy();

	/*
	*		�ζ��� �Լ�
	*/
	inline bool HasBeginPlay()	const { return _hasBeginPlay; }
	inline int	Width()			const { return _width; }
	inline int	Height()			const { return _height; }
	inline bool	Active()			const { return _isActive; }
	inline bool	Expired()			const { return _isExpired; }
	void SetActive(bool flag) { _isActive = flag; }
#pragma endregion

#pragma region ��� ����
private:
	Vector2 _position;
	char*	_pImage = nullptr;
	int		_width = 0;
	int		_height = 0;
	bool	_hasBeginPlay = false;
	Color	_color;
	unsigned int _sortingOrder = 0;
	Level*	_owner = nullptr;

	// ���Ͱ� Ȱ�� �������� �˷��ִ� ����
	bool _isActive = true;

	// ���� ��û�ƴ��� �˷��ִ� ����
	bool _isExpired = false;
#pragma endregion
};

#endif
