#pragma once

#include <sstream>

#define STRING(x) #x

namespace Lib
{
	enum class TokenType { Unknown, EndOfFile, Space, Number, Add, Sub, Mul, Div, LeftBracket, RightBracket, Semicolon };

	class Token
	{
	public:
		TokenType Type;
		std::string Text;
	public:
		Token(TokenType Type = TokenType::Unknown, const std::string& Text = "") : Type(Type), Text(Text)
		{
		}

		static TokenType GetType(const char Char)
		{
			if (Char == '\0' || Char == EOF) return TokenType::EndOfFile;
			if ((Char >= '\t' && Char <= '\r') || Char == ' ') return TokenType::Space;
			if ((Char >= '0' && Char <= '9') || Char == '.') return TokenType::Number;
			if (Char == ';') return TokenType::Semicolon;
			if (Char == '+') return TokenType::Add;
			if (Char == '-') return TokenType::Sub;
			if (Char == '*') return TokenType::Mul;
			if (Char == '/') return TokenType::Div;
			if (Char == '(') return TokenType::LeftBracket;
			if (Char == ')') return TokenType::RightBracket;
			return TokenType::Unknown;
		}
	};

	std::ostream& operator<<(std::ostream& Output, const Token& Object)
	{
		return Output << "{" << static_cast<int>(Object.Type) << ",\"" << Object.Text << "\"}";
	}
}
