all:
	g++ -std=c++0x -Wall -Wextra -Werror ./sources/*.cpp

fclean:
	rm -rf a.out

re: fclean all
