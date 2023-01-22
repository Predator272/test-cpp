#pragma once

#include "lexer.hpp"
#include "expression.hpp"

namespace Lib
{
	class Parser
	{
	private:
		std::list<Token> Tokens;
		std::list<Token>::iterator Begin, End, Current;
	public:
		Parser(std::list<Token>& Tokens) : Tokens(Tokens), Begin(this->Tokens.begin()), End(this->Tokens.end()), Current(this->Begin)
		{
		}

		std::list<std::shared_ptr<IExpression>> Parse()
		{
			std::list<std::shared_ptr<IExpression>> Result;
			while (!this->Match(TokenType::EndOfFile))
			{
				Result.push_back(this->Expression());
			}
			return Result;
		}
	private:
		std::shared_ptr<IExpression> Expression()
		{
			return this->AddSub();
		}

		std::shared_ptr<IExpression> AddSub()
		{
			auto Result = this->MulDiv();

			while (true)
			{
				if (this->Match(TokenType::Add))
				{
					Result = std::make_shared<BinaryAdd>(Result, this->MulDiv());
					continue;
				}
				if (this->Match(TokenType::Sub)) {
					Result = std::make_shared<BinarySub>(Result, this->MulDiv());
					continue;
				}
				break;
			}

			return Result;
		}

		std::shared_ptr<IExpression> MulDiv()
		{
			auto Result = this->Unary();

			while (true)
			{
				if (this->Match(TokenType::Mul))
				{
					Result = std::make_shared<BinaryMul>(Result, this->Unary());
					continue;
				}
				if (this->Match(TokenType::Div)) {
					Result = std::make_shared<BinaryDiv>(Result, this->Unary());
					continue;
				}
				break;
			}

			return Result;
		}

		std::shared_ptr<IExpression> Unary()
		{
			if (this->Match(TokenType::Sub))
			{
				return std::make_shared<UnaryMinus>(this->Primary());
			}
			if (this->Match(TokenType::Add))
			{
				return std::make_shared<UnaryPlus>(this->Primary());
			}
			return this->Primary();
		}

		std::shared_ptr<IExpression> Primary()
		{
			Token Current = this->Peek();
			if (this->Match(TokenType::Number))
			{
				return std::make_shared<NumberExpression>(std::stod(Current.Value));
			}
			if (this->Match(TokenType::LeftBracket))
			{
				auto Result = this->Expression();
				if (!this->Match(TokenType::RightBracket))
				{
					throw std::runtime_error("required \")\"");
				}
				return Result;
			}
			throw std::runtime_error("unknown expression");
		}

		bool Match(TokenType Type)
		{
			if (Type != this->Peek().Type) return false;
			if (this->Current != this->End) this->Current++;
			return true;
		}

		Token Peek()
		{
			if (this->Current == this->End) return Token(TokenType::EndOfFile);
			return *this->Current;
		}
	};
}
