#ifndef __INPUT_H__
#define __INPUT_H__

#include "Core.h"

#include <Windows.h>

/**
    @class   Input
    @brief   키보드 및 마우스 Input을 담당하는 싱글톤 클래스
    @details ~
**/
class ENGINE_API Input
{
    friend class Engine;

#pragma region KeyState_키_확인_구조체
    struct KeyState
    {
        enum CONST_KEYSTATE
        {
            VK_MAX = 255
        };
        bool _isKeyDown         = false;
        bool _previousKeyDown   = false;
    };
#pragma endregion

#pragma region MouseState_키_확인_구조체
    struct MouseState
    {
        enum CONST_MOUSESTATE
        {
            VK_MAX = 3
        };
        bool _isClick = false;
        COORD _mousePosition;
    };
#pragma endregion

#pragma region 특수 멤버 함수
public:
    Input();
    ~Input() = default;

    Input(const Input& rhs)             = delete;
    Input(Input&& rhs)                  = delete;
    Input& operator=(const Input& rhs)  = delete;
    Input& operator=(Input&& rhs)       = delete;
#pragma endregion

#pragma region static 함수
public:
    /**
        @brief  static 전역 객체를 반환하는 함수
        @retval  - static 클래스 객체
    **/
    static Input& GetInstance();
#pragma endregion

#pragma region 공개 함수
    /**
        @brief  현재 프레임에 가상 키 입력을 확인하는 함수
        @param  keyCode - 확인할 키 값
        @retval         - 성공 or 실패
    **/
    bool GetKey(int keyCode) const;

    /**
        @brief  현재 프레임에 가상 키가 눌렸는지 확인하는 함수
        @param  keyCode - 확인할 키 값.
        @retval         - 성공 or 실패
    **/
    bool GetKeyDown(int keyCode) const;

    /**
        @brief  현재 프레임에 가상 키가 눌린 상태(ing)로 유지 중인지 확인하는 함수
        @param  keyCode - 확인할 키 값.
        @retval         - 성공 or 실패
    **/
    bool GetKeyPressed(int keyCode) const;
    
    /**
        @brief  가상 키를 땟는지(Up) 확인하는 함수
        @param  keyCode - 확인할 키 값
        @retval         - 성공 or 실패
    **/
    bool GetKeyUp(int keyCode) const;

    /**
        @brief  마우스 왼쪽 클릭(Down) 확인 함수
        @retval  - 성공 or 실패
    **/
    bool	GetMouseLeftClickDown()     const;

    /**
        @brief  마우스 왼쪽 클릭 때짐(Up) 확인 함수
        @retval  - 성공 or 실패
    **/
    bool    GetMouseLeftClickUp()       const;

    /**
        @brief  마우스 왼쪽 클릭(ing) 확인 함수
        @retval  - 성공 or 실패
    **/
    bool    GetMouseLeftClickPressed()  const;

    /**
        @brief  마우스 오른쪽 클릭(Down) 확인 함수
        @retval  - 성공 or 실패
    **/
    bool	GetMouseRightClickDown()    const;
    
    /**
        @brief  마우스 오른쪽 클릭 때짐(Up) 확인 함수
        @retval  - 성공 or 실패
    **/
    bool    GetMouseRightClickUp()      const;

    /**
        @brief  마우스 오른쪽 클릭(ing) 확인 함수
        @retval  - 성공 or 실패
    **/
    bool    GetMouseRightClickPressed() const;

    /**
        @brief  마우스 가운데 클릭(Down) 확인 함수
        @retval  - 성공 or 실패
    **/
    bool	GetMouseMiddleClickDown()   const;
    /**
        @brief  마우스 가운데 클릭 때짐(Up) 확인 함수
        @retval  - 성공 or 실패
    **/
    bool    GetMouseMiddleClickUp()     const;
    
    /**
        @brief  마우스 가운데 클릭(ing) 확인 함수
        @retval  - 성공 or 실패
    **/
    bool    GetMouseMiddleClickPressed()const;

    /**
        @brief  마우스 버튼 이벤트 발생 시 가장 마지막 위치에 있던 마우스 위치 반환 함수
        @retval  - 마우스 위치 값
    **/
    COORD	GetMousePosition();
#pragma endregion

#pragma region 내부 함수
private:
    /**
        @brief 입력 이벤트를 처리하는 함수
    **/
    void ProcessInput();
    
    /**
        @brief 현재 프레임에 있던 input 정보를 기록하는 함수
    **/
    void SavePreviousKeyStates();
#pragma endregion

#pragma region static 변수
private:
    static Input*	_static_instance;
#pragma endregion

#pragma region 멤버 변수
private:
    KeyState	_keyStates[255] = {};
    MouseState	_mouseStates	= {};
#pragma endregion
};

#endif
