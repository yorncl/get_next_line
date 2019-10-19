


NAME = test.out
FILES = get_next_line.c get_next_line_utils.c  test.c

all : $(NAME)
$(NAME) : $(FILES)
	gcc -Wall -Werror -Wextra -D BUFFER_SIZE=3 -I get_next_line.h $(FILES) -o $(NAME)

test : 
	gcc -Wall -Werror -Wextra -g3 -fsanitize=address -I get_next_line.h $(FILES) -o $(NAME)
	./$(NAME)