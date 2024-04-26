# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sataskin <sataskin@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/23 13:03:26 by sataskin          #+#    #+#              #
#    Updated: 2024/04/26 17:13:05 by sataskin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CLIENT_NAME = client

SERVER_NAME = server

C_SOURCE = client.c

S_SOURCE = server.c
			
C_OBJECT = $(C_SOURCE:.c=.o)

S_OBJECT = $(S_SOURCE:.c=.o)

LIBFT = libft/libft.a

all: $(CLIENT_NAME) $(SERVER_NAME)

%.o:%.c
	@cc -Wall -Wextra -Werror -c $< -o $(<:.c=.o)

$(CLIENT_NAME): $(C_OBJECT)
	@make -C libft
	@cc -Wall -Wextra -Werror $(C_OBJECT) $(LIBFT) -o $(CLIENT_NAME)
	@echo client made

$(SERVER_NAME):$(S_OBJECT)
	@cc -Wall -Wextra -Werror $(S_OBJECT) $(LIBFT) -o $(SERVER_NAME)
	@echo server made

clean:
	rm -f $(C_OBJECT)
	rm -f $(S_OBJECT)
	@make clean -C libft

fclean: clean
	@rm -f $(CLIENT_NAME)
	@rm -f $(SERVER_NAME)
	@rm -f libft/libft.a

re: fclean all

.PHONY: clean fclean all re makelibft