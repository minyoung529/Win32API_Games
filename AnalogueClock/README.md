# 아날로그 시계

방과후 시간에 선생님과 Win32Api로 만든 아날로그 시계를 리팩토링했다.

<br>

실제 컴퓨터 시간을 반영한 아날로그 시계.

<img src="https://user-images.githubusercontent.com/77655318/187896220-7affe2cc-cfb3-4289-8b9a-77b45b0d1821.png"  width="300">




## 리팩토링한 코드

### 1. 시계 객체화

[Clock.cpp 소스](https://github.com/minyoung529/Win32API_Games/blob/main/AnalogueClock/Clock.cpp)
[Clock.h 소스](https://github.com/minyoung529/Win32API_Games/blob/main/AnalogueClock/Clock.h)

WinProc 함수에 있었던 모든 시계 출력, 시간 계산 코드를 **Clock 클래스**의 멤버 함수로 넣어 Clock 객체를 생성하고, 메서드를 부를 수 있게 했다.

> Clock.h
``` cpp
class Clock
{
private:
	int radius;
	POINT pos;
	int clockState = HOUR | MINUTE | SECOND;

public:
	Clock() : radius(0)
	{
		memset(&pos, 0, sizeof(pos));
	}

  //...
  
	void RenderClock(SYSTEMTIME time, HDC hdc);

private:
	void RenderHour(SYSTEMTIME systemTime, HDC hdc);
	void RenderSecond(SYSTEMTIME systemTime, HDC hdc);
	void RenderMinute(SYSTEMTIME systemTime, HDC hdc);

	void RenderGraduation(HDC hdc);
	void RenderNumber(HDC hdc);
	void RenderCircle(HDC hdc);
	void PlaySound(SYSTEMTIME time);
};
```


> AnalogueClock.cpp (Main) 윈도우 생성시
``` cpp
// 처음 만들 때
case WM_CREATE:
{
  //...
	// 시계 생성
	clock = new Clock(radius, { nWidth, nWidth }, HOUR | SECOND | MINUTE | SOUND);

	// 시계 토글들 생성
	hourToggle =	new ClockToggle(HOUR_COLOR, { 40,450 }, 30, 20, clock, HOUR, L"시침");
	minuteToggle =	new ClockToggle(MINUTE_COLOR, { 140,450 }, 30, 20, clock, MINUTE, L"분침");
	secondToggle =	new ClockToggle(SECOND_COLOR, { 240,450 }, 30, 20, clock, SECOND, L"초침");
	soundToggle =	new ClockToggle(SOUND_COLOR, { 340,450 }, 30, 20, clock, SOUND, L"소리");
}break;
```

> AnalogueClock.cpp (Main) 화면 출력시
```cpp
case WM_PAINT:
{
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hWnd, &ps);

	GetLocalTime(&systemTime);
  
  // 토글 버튼들 갱신
	hourToggle	->Update(hdc, hWnd);
	minuteToggle->Update(hdc, hWnd);
	secondToggle->Update(hdc, hWnd);
	soundToggle	->Update(hdc, hWnd);

  // 시계 출력
	clock->RenderClock(systemTime, hdc);

	EndPaint(hWnd, &ps);
} break;
```

### 2. 삼각함수 가독성

sin, cos 함수에 매개변수로 들어가는 식들이 직관적으로 이해하기 힘들었기 때문에 `sin(RAD2DEG * degrees)`의 형태로 모두 바꿔주었다.

> RAD2DEG 상수
``` cpp
#define PI		3.141592
#define RAD2DEG		PI/180
```

> 시침 각도 계산 코드
``` cpp
// Before
x = sin(2 * PI * (st.wHour * 60 + st.wMinute) / 720);
y = -cos(2 * PI * (st.wHour * 60 + st.wMinute) / 720);

// After
x =  sin(RAD2DEG * (time.wHour * 30 + time.wMinute / 2));
y = -cos(RAD2DEG * (time.wHour * 30 + time.wMinute / 2))
```

> 분침 각도 계산 코드
``` cpp
// Before
x = sin(2 * PI * st.wMinute / 60);
y = -cos(2 * PI * st.wMinute / 60);

// After
x =  sin(DEG2RAD * time.wMinute * 6);
y = -cos(DEG2RAD * time.wMinute * 6);
```


>> 초침 각도 계산 코드
``` cpp
// Before
x = sin(2 * PI * st.wSecond / 60);
y = -cos(2 * PI * st.wSecond / 60);

// After
x =  sin(DEG2RAD * time.wSecond * 6);
y = -cos(DEG2RAD * time.wSecond * 6);
```


큰 차이는 없지만, 나 자신이 이해하기 수월하도록 고쳤다.


### 3. 매크로 상수




## 추가 사항

### ON / OFF 기능
### 숫자 추가
