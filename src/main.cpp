#include "lib/parser.hpp"

int main()
{
	while (true)
	{
		try
		{
			std::cout << "Enter: ";
			std::string Input;
			std::getline(std::cin, Input);
			std::istringstream StringStream(Input);


			auto Tokens = Lib::Lexer(StringStream).Tokens;
			std::ostringstream TokensString;
			std::copy(Tokens.begin(), Tokens.end(), std::ostream_iterator<Lib::Token>(TokensString, "; "));
			std::cout << "Tokens: " << TokensString.str() << "\n";


			auto Expr = Lib::Parser(Tokens).Parse();
			std::ostringstream ExprString;
			std::copy(Expr.begin(), Expr.end(), std::ostream_iterator<std::shared_ptr<Lib::IExpression>>(ExprString, "; "));
			std::cout << "Result: " << ExprString.str() << "\n";
		}
		catch (const std::exception& Error)
		{
			std::cerr << Error.what() << '\n';
		}
	}

	return 0;
}
