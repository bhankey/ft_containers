CXX		=	clang++

CPPFLAGS	=	-Wall -Wextra -Werror  -IContainers -Iiterators -Itest -I. -std=c++98

all: my std
	diff myTest stdTest > differenceOfContainers

my:
	$(CXX) $(CPPFLAGS) tests/main.cpp -o my
	./my > myTest

std:
	$(CXX) $(CPPFLAGS) tests/main_std.cpp -o std
	./std > stdTest

clean:
			rm -f differenceOfContainers myTest stdTest

fclean:		clean
			rm -f ./my  ./std

re:			fclean all

.PHONY: 	my std clean fclean re