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

SRCS = test.c parsing/module.c
OBJS = $(SRCS:.c=.o)
INCS = main.h parsing/parsing.h

CC = cc
RM = rm -rf

CFLAGS = -Wall -Wextra -Werror
IFLAGS =  -Iexecution -Iparsing


all : $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(OBJS) -o $(@)
	@echo "🔗 $(CYAN)$(notdir $(OBJS)) $(@:=.o) $(BLACK)=> $(YELLOW)$(@)$(RESET)"

%.o: %.c $(INCS)
	@$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@
	@echo "🔨 $(BLUE)$(notdir $<) $(BLACK)=> $(CYAN)$(notdir $@)$(RESET)"

clean :
	@find . -type f -name "*.o" -printf "🧹 $(BLACK)%f$(RESET)\n" -delete

fclean : clean
	@$(RM) $(NAME) && echo "🧹 $(BLACK)$(NAME)$(RESET)"

re : fclean all

run: $(NAME)
	@./$<

.PHONY: all clean fclean re run
