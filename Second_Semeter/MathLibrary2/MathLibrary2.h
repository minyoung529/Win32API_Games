#pragma once

namespace MathLibrary2
{
	class Arithmetic
	{
	public:
		double Add(double a, double b);
		double Sub(double a, double b);
		double Mul(double a, double b);
		double Div(double a, double b);

	public:
		static double Add2(double a, double b);
		static double Sub2(double a, double b);
		static double Mul2(double a, double b);
		static double Div2(double a, double b);
	};
}