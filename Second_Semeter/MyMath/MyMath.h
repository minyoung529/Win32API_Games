#pragma once

#ifndef MYMATH_EXPORTS
#define MYMATH_DECLSPEC __declspec(dllexport)

#else
#define MYMATH_DECLSPEC __declspec(dllimport)
#endif // CREATEDLL_EXPORTS

extern "C" MYMATH_DECLSPEC double Add(double a, double b);
extern "C" MYMATH_DECLSPEC double Sub(double a, double b);
extern "C" MYMATH_DECLSPEC double Mul(double a, double b);
extern "C" MYMATH_DECLSPEC double Div(double a, double b);