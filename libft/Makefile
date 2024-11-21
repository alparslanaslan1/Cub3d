# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bsen <bsen@student.42kocaeli.com.tr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/26 16:06:07 by alaslan           #+#    #+#              #
#    Updated: 2024/10/16 20:00:50 by bsen             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	libft.a
CC			= 	cc
CFLAGS		=	-Wall -Wextra -Werror -g
RM			=	rm -rf


GET_NEXT_LINE = get_next_line

SRC			=	ft_atoi.c			\
				ft_bzero.c			\
				ft_calloc.c			\
				ft_isalnum.c		\
				ft_isalpha.c		\
				ft_isascii.c		\
				ft_isdigit.c		\
				ft_isprint.c		\
				ft_itoa.c			\
				ft_memchr.c			\
				ft_memcmp.c			\
				ft_memcpy.c			\
				ft_memmove.c		\
				ft_strcmp.c			\
				ft_memset.c			\
				ft_putchar_fd.c		\
				ft_putendl_fd.c		\
				ft_putnbr_fd.c		\
				ft_putstr_fd.c		\
				ft_split.c			\
				ft_strchr.c			\
				ft_strdup.c			\
				ft_striteri.c		\
				ft_strjoin.c		\
				ft_strlcat.c		\
				ft_strlcpy.c		\
				ft_strlen.c			\
				ft_strmapi.c		\
				ft_strncmp.c		\
				ft_strnstr.c		\
				ft_strrchr.c		\
				ft_split_free.c		\
				ft_strtrim.c		\
				ft_substr.c			\
				ft_tolower.c		\
				ft_toupper.c		\
				ft_is_made_of_char.c\
				ft_strcpy.c			\
				ft_strncpy.c		\
				get_next_line_utils.c\
				get_next_line.c

B			=	ft_lstnew.c			\
				ft_lstadd_front.c	\
				ft_lstsize.c		\
				ft_lstlast.c		\
				ft_lstadd_back.c

OBJ			=	$(SRC:.c=.o)

B_OBJ		=	$(B:.c=.o)

all:			$(NAME)

bonus:			$(B_OBJ)
						ar rcs $(NAME) $(B_OBJ)

$(NAME):		$(OBJ)
						ar rcs $(NAME) $(OBJ)

clean:
				$(RM) $(OBJ) $(B_OBJ)

fclean: clean
				$(RM) $(NAME)

re:				fclean all

.PHONY:			all clean fclean re
