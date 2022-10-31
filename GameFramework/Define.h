#pragma once

// ¸ÅÅ©·Î¶û enum class
#define SINGLE(type) static type* GetInst(){ static type mgr; return &mgr; }

#define WINDOW_NAME L"Game_Framework"

#define FDT		TimeManager::GetInst()->GetFDT()
#define DT		TimeManager::GetInst()->GetDT()