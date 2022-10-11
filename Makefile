##
## ATOS PROJECT 2022
## MAKEFILE
## File description:
## Wow, such make, much file!
##

SLURM_ROOT_DIR	=	/usr
SLURM_INC_DIR	=	/root/SLURM/slurm.build
SLURM_LIB_DIR	=	/usr/lib64/slurm
SLURM_BUILD		=	21.08.8-2
SLURM_BUILD_DIR	=	/root/rpmbuild/BUILD/slurm-$(SLURM_BUILD)

NAME			=	ask_demeter

SRC 			=	src/ask_demeter.c	\
					src/get_arg.c		\
					src/init_args.c		\

CC				=	gcc
CFLAGS			?=	-Wall -Iinclude -I$(SLURM_INC_DIR) -I$(SLURM_BUILD_DIR)
LDFLAGS			?=  -lcurl

all:			$(NAME)

default:		$(NAME)

$(NAME):	$(SRC)
		$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

send:	all
		scp $(NAME) my_vm:/home/compose_fake_taranis/shared/

clean:
		rm -f $(NAME)

re:		clean all