# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: myrmarti <myrmarti@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/06 12:10:53 by aasli             #+#    #+#              #
#    Updated: 2023/02/20 10:17:16 by aasli            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

####### VARIABLES #######

INC_DIR        =    includes

CXX				=	c++

CXXFLAGS		=	-Wall -Werror -Wextra -std=c++98 -g3

SRCS			=	$(addprefix srcs/,	main.cpp)

STD_SRCS		=	$(addprefix srcs/,	std.cpp)

OBJS 			=	$(SRCS:%.cpp=%.o)

STD_OBJS 		=	$(STD_SRCS:%.cpp=%.o)

DEPS 			=	$(SRCS:%.cpp=%.d)

STD_DEPS 		=	$(STD_SRCS:%.cpp=%.d)

RM				=	rm -rf

NAME			=	containers

NAME2			=	std

####### COMMANDS #######

all:				${NAME} ${NAME2}

%.o : %.cpp
		${CXX} ${CXXFLAGS} -MMD -MP -c $< -o $@ -I includes 

-include ${DEPS}

${NAME}:	${OBJS}
		${CXX} ${CXXFLAGS} ${OBJS} -o ${NAME}

${NAME2}:	${STD_OBJS}
		${CXX} ${CXXFLAGS} ${STD_OBJS} -o ${NAME2}

v:			${OBJS}
		@${CXX} ${CXXFLAGS} -o ${NAME} ${OBJS}
		@echo "\e[32m"Compilation success"\033[0m"
		@valgrind -s --track-origins=yes --leak-check=full --show-leak-kinds=all ./${NAME}

clean:
		@${RM} srcs/*.o srcs/*.d
		@echo "\e[35m"Object files deleted"\033[0m"

fclean:			clean
		@${RM} ${NAME}
		@${RM} ${NAME2}
		@echo "\e[35m"Executable deleted"\033[0m"

re:		fclean all

.PHONY:			fclean all clean re
