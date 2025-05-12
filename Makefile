BLACK = \033[30m
RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
BLUE = \033[34m
MAGENTA = \033[35m
CYAN = \033[36m
WHITE = \033[37m
RESET = \033[0m

NAME = minishell
LIBFT = libft/libft.a
MAKE = make --no-print-directory

SRCS = test.c
# SRCS += $(addprefix execution/, \
# 		echo_builtin.c pwd_builtin.c env_builtin.c)
# ft_substr.c ft_strsjoin.c
SRCS += $(addprefix parsing/, \
		ft_strcmp.c ft_parse.c \
		ft_fill.c ft_isx.c utils.c )
OBJS = $(SRCS:.c=.o)
INCS = main.h parsing/parsing.h \
		# execution/exec.h

CC = cc

CFLAGS = -Wall -Wextra -Werror
IFLAGS = -Iexecution -Iparsing -Ilibft
LFLAGS = -lreadline -Llibft -lft -fsanitize=address


all : $(NAME)

%.o: %.c $(INCS)
	@$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@
	@echo "🔨 $(BLUE)$(notdir $<) $(BLACK)=> $(CYAN)$(notdir $@)$(RESET)"

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(OBJS) $(LFLAGS) -o $(@)
	@echo "🔗 $(CYAN)$(notdir $(LIBFT)) $(notdir $(OBJS)) $(BLACK)=> $(YELLOW)$(@)$(RESET)"


$(LIBFT):
	@$(MAKE) -C libft

clean :
	@find . -type f -name "*.o" -printf "🧹 $(BLACK)%f$(RESET)\n" -delete

fclean : clean
	@$(MAKE) fclean -C libft
	@find . -type f -name "$(NAME)" -printf "🧹 $(BLACK)%f$(RESET)\n" -delete

re : fclean all

run: $(NAME)
	@./$<

.PHONY: all clean fclean re run
