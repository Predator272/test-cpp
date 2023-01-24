#pragma once

#include <sstream>
#include <memory>

namespace Lib
{
	class IExpression
	{
	public:
		virtual double Exec() { return 0.0; }
		virtual std::string String() { return ""; }
	};

	class NumberExpression : public IExpression
	{
	private:
		double Value;
	public:
		NumberExpression(double Value) : Value(Value) {}
		double Exec() override { return this->Value; }
		std::string String() override { std::stringstream ss; ss << this->Value; return ss.str(); }
	};

	class UnaryPlus : public IExpression
	{
	private:
		std::shared_ptr<IExpression> Expr;
	public:
		UnaryPlus(std::shared_ptr<IExpression>& Expr) : Expr(Expr) {}
		double Exec() override { return +this->Expr->Exec(); }
		std::string String() override { return "(+" + this->Expr->String() + ")"; }
	};

	class UnaryMinus : public IExpression
	{
	private:
		std::shared_ptr<IExpression> Expr;
	public:
		UnaryMinus(std::shared_ptr<IExpression>& Expr) : Expr(Expr) {}
		double Exec() override { return -this->Expr->Exec(); }
		std::string String() override { return "(-" + this->Expr->String() + ")"; }
	};

	class BinaryAdd : public IExpression
	{
	private:
		std::shared_ptr<IExpression> Expr1, Expr2;
	public:
		BinaryAdd(std::shared_ptr<IExpression>& Expr1, std::shared_ptr<IExpression>& Expr2) : Expr1(Expr1), Expr2(Expr2) {}
		double Exec() override { return this->Expr1->Exec() + this->Expr2->Exec(); }
		std::string String() override { return "(" + this->Expr1->String() + "+" + this->Expr2->String() + ")"; }
	};

	class BinarySub : public IExpression
	{
	private:
		std::shared_ptr<IExpression> Expr1, Expr2;
	public:
		BinarySub(std::shared_ptr<IExpression>& Expr1, std::shared_ptr<IExpression>& Expr2) : Expr1(Expr1), Expr2(Expr2) {}
		double Exec() override { return this->Expr1->Exec() - this->Expr2->Exec(); }
		std::string String() override { return "(" + this->Expr1->String() + "-" + this->Expr2->String() + ")"; }
	};

	class BinaryMul : public IExpression
	{
	private:
		std::shared_ptr<IExpression> Expr1, Expr2;
	public:
		BinaryMul(std::shared_ptr<IExpression>& Expr1, std::shared_ptr<IExpression>& Expr2) : Expr1(Expr1), Expr2(Expr2) {}
		double Exec() override { return this->Expr1->Exec() * this->Expr2->Exec(); }
		std::string String() override { return "(" + this->Expr1->String() + "*" + this->Expr2->String() + ")"; }
	};

	class BinaryDiv : public IExpression
	{
	private:
		std::shared_ptr<IExpression> Expr1, Expr2;
	public:
		BinaryDiv(std::shared_ptr<IExpression>& Expr1, std::shared_ptr<IExpression>& Expr2) : Expr1(Expr1), Expr2(Expr2) {}
		double Exec() override { return this->Expr1->Exec() / this->Expr2->Exec(); }
		std::string String() override { return "(" + this->Expr1->String() + "/" + this->Expr2->String() + ")"; }
	};

	std::ostream& operator<<(std::ostream& Output, const std::shared_ptr<IExpression>& Object)
	{
		return Output << Object->String() << "=" << Object->Exec();
	}
}
