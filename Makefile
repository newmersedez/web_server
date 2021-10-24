all:
	g++ -Wall -Wextra -Werror ./sources/*.cpp

fclean:
	rm -rf a.out

re: fclean all
