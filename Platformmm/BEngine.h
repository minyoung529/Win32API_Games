#ifndef	  BENGINE_H
#define	  BENGINE_H

#include "BWindow.h"
#include "BImage.h"
#include "BInput.h"
#include "BSound.h"
#include "SceneManager.h"

class BEngine : public BWindow
{
public:
	BEngine();
	~BEngine();

public:
	virtual void			Startup() override;
	virtual void			MainLoop() override;
	virtual void			Cleanup() override;

	virtual void			_Update(float dt);
	virtual void			_Render(HDC hdc, float dt);

private:
	void					RenderText(UINT fps, float dt);

public:
	virtual void			Init();
	virtual void			Update(float dt);
	virtual void			Render(HDC hdc, float dt);
	virtual void			Release();

private:
	LARGE_INTEGER			m_llPrevCount;
	LARGE_INTEGER			m_llCurCount;
	LARGE_INTEGER			m_llFrequency;

	float					m_fDT;			// 프레임간 시간 값
	float					m_fAcc;			// 1초 체크를 위한 누적 시간 	
	UINT					m_iCallCount;	// 함수 호출 횟수 체크
	UINT					m_iFPS;			// 초당 호출 횟수

public:
	BInput					m_InputObject;
	BSound					m_SoundObject;
	CSceneManager*			m_SceneManager;
};
#endif // BENGINE_H