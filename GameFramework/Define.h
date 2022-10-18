#pragma once

// ¸ÅÅ©·Î¶û enum class
#define SINGLE(type) static type* GetInst(){ static type mgr; return &mgr; }
