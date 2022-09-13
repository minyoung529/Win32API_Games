<<<<<<< Updated upstream
# WinAPI
방과후 Win32API 시간에 만든 프로젝트들입니다.


## [⏰ 아날로그 시계 ⏰](https://github.com/minyoung529/Win32API_Games/blob/main/AnalogueClock/README.md)
=======
# 아날로그 시계

방과후 시간에 선생님과 Win32Api로 만든 아날로그 시계를 리팩토링했다.
>>>>>>> Stashed changes

<br>

실제 컴퓨터 시간을 반영한 아날로그 시계.

<img src="https://user-images.githubusercontent.com/77655318/187896220-7affe2cc-cfb3-4289-8b9a-77b45b0d1821.png"  width="300">




## 리팩토링한 코드

### 1. 시계 객체화

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

복잡한 sin, cos 함수의 매개변수를 (DEG2RAD * 각도) 형태로 간단하게 리팩토링했습니다.


### 3. 매크로 상수




## 추가 사항

### ON / OFF 기능
### 숫자 추가
