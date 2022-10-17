NAME = ft_containers

CC = c++
C_FLAGS = -Wall -Wextra -Werror -std=c++98

C_FILES = main.cpp
O_FILES = $(C_FILES:.cpp=.o)

INCLUDES = -I containers

%.o: %.cpp
	@printf "\033[0;33mGenerating ${NAME} objects... %-33.33s\033[0m" $@
	@${CC} ${C_FLAGS} ${INCLUDES} -c $< -o $@
	@${CC} -DSTL ${C_FLAGS} ${INCLUDES} -c $< -o "stl_main.o"


all: ${NAME}

${NAME}: ${O_FILES}
	@echo "\n\n\033[0;34mCompiling ${NAME}...\033[0m"
	@${CC} ${O_FILES} -o ${NAME}
	@echo "\n\033[0;34mCompiling ${NAME}_stl...\033[0m\n"
	@${CC} stl_main.o -o "${NAME}_stl"
	@echo "-----FT-----"
	@./${NAME} 2>>log_error
	@echo "\n-----STL-----"
	@./${NAME}_stl 2>>log_error
	@./${NAME} > _diff_ft
	@echo "\n-----DIFF-----"
	@./${NAME}_stl > _diff_stl
	@diff _diff_ft _diff_stl
	@rm -f _diff_ft _diff_stl
	@echo

test:
	@${CC} test.cpp -o a.out
	@./a.out
	@rm a.out

clean:
	@echo "\n\033[0;31mRemoving objects files...\033[0m"
	@rm -f ${O_FILES} stl_main.o ${O_FILES_STL}

fclean: clean
	@echo "\n\033[0;31mRemoving ${NAME} executable...\033[0m\n"
	@rm -f ${NAME} ${NAME}_stl

re: fclean all
