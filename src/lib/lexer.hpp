#pragma once

#include <iostream>
#include <list>

#include "token.hpp"

namespace Lib
{
	class Lexer
	{
	public:
		std::list<Token> Tokens;
	public:
		Lexer(std::istream& Stream)
		{
			while (!Stream.eof())
			{
				std::string Buffer;
				switch (Token::GetType(Stream.peek()))
				{
				case TokenType::Space:
				case TokenType::EndOfFile:
					Stream.get();
					continue;
				case TokenType::Add:
				case TokenType::Sub:
				case TokenType::Mul:
				case TokenType::Div:
				case TokenType::LeftBracket:
				case TokenType::RightBracket:
				case TokenType::Semicolon:
					Buffer.push_back(Stream.get());
					break;
				default:
					while (Buffer.empty() || Token::GetType(Stream.peek()) == Token::GetType(Buffer.back()))
					{
						Buffer.push_back(Stream.get());
					}
				}
				this->AddToken(Token::GetType(Buffer.back()), Buffer);
			}
		}
	private:
		void AddToken(TokenType Type, const std::string& Value = "")
		{
			Tokens.push_back(Token(Type, Value));
		}
	};
}
