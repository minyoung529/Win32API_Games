#pragma once

// ��ũ�ζ� enum class
#define SINGLE(type) static type* GetInst(){ static type mgr; return &mgr; }
