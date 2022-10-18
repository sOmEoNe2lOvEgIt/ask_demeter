##
## ATOS PROJECT 2022
## MAKEFILE
## File description:
## Wow, such make, much file!
##

SLURM_INCLUDE_DIR	=	/root/SLURM/slurm.build
LIB_DEMETER			=	/home/atos/lib_demeter
DEMETER_RUN_PATH	=	/home/atos/lib_demeter/

NAME				=	ask_demeter

SRC 				=	src/ask_demeter.c					\
						src/get_arg.c						\
						src/init_args.c						\
						src/get_demeter_job.c				\
						src/json/handle_json.c				\
						src/json/json_tools/parse_json.c	\
						src/json/json_tools/display_json.c	\

CC					=	gcc
CFLAGS				?=	-Wall -g3 -Iinclude -I$(LIB_DEMETER)/include -I$(SLURM_INCLUDE_DIR) -Wl,-rpath=$(DEMETER_RUN_PATH)
LDFLAGS				?=  -lcurl -L$(LIB_DEMETER) -ldemeter -ljson-c

all:			$(NAME)

default:		$(NAME)

$(NAME):	$(SRC)
		$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

send:	all
		scp $(NAME) my_vm:/home/compose_fake_taranis/shared/

clean:
		rm -f $(NAME)

re:		clean all