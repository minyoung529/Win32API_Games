#pragma once

// ��ũ�ζ� enum class
#define SINGLE(type) static type* GetInst(){ static type mgr; return &mgr; }

#define WINDOW_NAME L"Game_Framework"