NAME = ./lem_in
SRC_DIR = ./src/
SRC_FILES = main.c\
	find_path.c\
	find_path_helpers.c\
	bfs.c\
	print_mtx.c\
	queue_helpers.c\
	run_ants.c\
	free.c\
	parse/parse_links.c\
	parse/parse_rooms.c\
	parse/parse.c\
	parse/read_state.c
SRCS = $(addprefix $(SRC_DIR), $(SRC_FILES))

OBJ_DIR = ./obj/
OBJ_FILES  = main.o\
	find_path.o\
	find_path_helpers.o\
	bfs.o\
	print_mtx.o\
	queue_helpers.o\
	run_ants.o\
	free.o\
	parse/parse_links.o\
	parse/parse_rooms.o\
	parse/parse.o\
	parse/read_state.o
OBJS = $(addprefix $(OBJ_DIR), $(OBJ_FILES))
HDR = lem_in.h
FLAGS = #-Wall  -Wextra -Werror
LIBFTDIR = libft/
LIBFT = libft/libft.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	gcc $(FLAGS) -o $(NAME) $(SRCS) -I $(HDR) -L. $(LIBFT)

$(LIBFT):
	make -C $(LIBFTDIR)

$(OBJS): $(SRCS)
	@gcc $(FLAGS) -c $< -o $@

clean:
	/bin/rm -f $(OBJS)
	make -C $(LIBFTDIR) clean

fclean: clean
	/bin/rm -f $(NAME)
	make -C $(LIBFTDIR) fclean

re: fclean all
