##
## ATOS PROJECT 2022
## MAKEFILE
## File description:
## Wow, such make, much file!
##

LIB_DEMETER			=	/home/atos/lib_demeter
DEMETER_RUN_PATH	=	/home/atos/lib_demeter/

NAME				=	ask_demeter

SRC 				=	src/ask_demeter.c	\
						src/get_arg.c		\
						src/init_args.c

CC					=	gcc
CFLAGS				?=	-Wall -g3 -gstrict-dwarf -Iinclude -I$(LIB_DEMETER)/include -Wl,-rpath=$(DEMETER_RUN_PATH)
LDFLAGS				?=  -lcurl -L$(LIB_DEMETER) -ldemeter

all:			$(NAME)

default:		$(NAME)

$(NAME):	$(SRC)
		$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

send:	all
		scp $(NAME) my_vm:/home/compose_fake_taranis/shared/

clean:
		rm -f $(NAME)

re:		clean all