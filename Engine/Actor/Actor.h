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

#pragma region 특수 맴버 함수
public:
	Actor(const wchar_t* pImage = L"", Color color = Color::Color_White, const Vector2& position = Vector2::Zero);
	virtual ~Actor();
#pragma endregion

#pragma region 공개 함수
	/*
	*		이벤트 함수
	*/
	virtual void BeginPlay();				// 객체 생명주기에 1번만 호출(초기화 목적).
	virtual void Tick(float deltaTime = 0);	// 프레임마다 호출 (반복적 작업/지속성이 필요한 작업).
	virtual void Render();					// 그리기 함수.

	virtual void Reset() {};					// 처음 상태로 복구

	/*
	*		일반 함수
	*/
	void SetPosition(const Vector2& newPosition);
	Vector2 Position() const;

	void SetSortingOrder(unsigned int sortingOrder);
	
	/* Owner 관련 함수 */
	void	SetOwner(Level* newOwner);
	virtual Level*	GetOwner() const;
	
	/* 종료 함수 */
	void QuitGame();

	/* 객체 삭제 함수 */
	void Destroy();

	/*
	*		인라인 함수
	*/
	inline bool HasBeginPlay()	const { return _hasBeginPlay; }
	virtual int	Width()			const { return _width; }
	virtual int	Height()			const { return _height; }
	inline void SetWidth(int width) { _width = width; }
	inline void SetHeight(int height) { _height = height; }
	inline bool	Active()			const { return _isActive; }
	inline bool	Expired()			const { return _isExpired; }
	void SetActive(bool flag) { _isActive = flag; }
#pragma endregion

#pragma region 멤버 변수
private:
	Vector2 _position;
	wchar_t*	_pImage = nullptr;
	int		_width = 0;
	int		_height = 0;
	bool	_hasBeginPlay = false;
	Color	_color;
	unsigned int _sortingOrder = 0;
	Level*	_owner = nullptr;

	// 엑터가 활성 상태인지 알려주는 변수
	bool _isActive = true;

	// 삭제 요청됐는지 알려주는 변수
	bool _isExpired = false;
#pragma endregion
};

#endif
