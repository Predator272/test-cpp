#include "lib/parser.hpp"

int main()
{
	while (true)
	{
		try
		{
			std::cout << "Enter expression: ";
			std::string Input;
			std::getline(std::cin, Input);

			std::istringstream StringStream(Input);
			Lib::Lexer Lexer(StringStream);

			Lib::Parser Parser(Lexer.Tokens);
			auto Expr = Parser.Parse();

			std::cout << "Result: ";
			for (auto Iter = Expr.begin(); Iter != Expr.end(); Iter++) {
				if (Iter != Expr.begin())
				{
					std::cout << ", ";
				}
				std::cout << Iter->get()->Exec();
			}
			std::cout << "\n";
		}
		catch (const std::exception& Error)
		{
			std::cerr << Error.what() << '\n';
		}
	}

	return 0;
}
