all:
	g++ -std=c++0x -Wall -Wextra -Werror ./sources/*.cpp -o server -lstdc++fs

fclean:
	rm -rf server

re: fclean all
