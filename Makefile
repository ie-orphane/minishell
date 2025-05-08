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
MAKE = make -C

SRCS = test.c parsing/module.c\
		$(addprefix execution/, echo_builtin.c pwd_builtin.c env_builtin.c)
OBJS = $(SRCS:.c=.o)
INCS = main.h parsing/parsing.h\
		execution/exec.h

CC = cc
RM = rm -rf

CFLAGS = -Wall -Wextra -Werror
IFLAGS = -Iexecution -Iparsing -Ilibft -lreadline

all : $(NAME)

# added libft as a dependency

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(OBJS) $(LIBFT) $(IFLAGS) -o $(@)
	@echo "🔗 $(CYAN)$(notdir $(OBJS)) $(@:=.o) $(BLACK)=> $(YELLOW)$(@)$(RESET)"

%.o: %.c $(INCS)
	@$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@
	@echo "🔨 $(BLUE)$(notdir $<) $(BLACK)=> $(CYAN)$(notdir $@)$(RESET)"

$(LIBFT):
	@make -C libft

clean :
	@find . -type f -name "*.o" -printf "🧹 $(BLACK)%f$(RESET)\n" -delete

fclean : clean
	@make fclean -C libft
	@$(RM) $(NAME) && echo "🧹 $(BLACK)$(NAME)$(RESET)"

re : fclean all

run: $(NAME)
	@./$<

.PHONY: all clean fclean re run
