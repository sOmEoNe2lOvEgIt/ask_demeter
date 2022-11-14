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

SRC 				=	src/ask_demeter.c								\
						src/tools/init/init_args.c						\
						src/tools/init/init_parsed_hostname_json.c		\
						src/tools/get/get_arg.c							\
						src/tools/get/get_demeter_job.c					\
						src/tools/get/get_list_size.c					\
						src/tools/get/get_first_host_after_hostname.c	\
						src/json/handle_json.c							\
						src/json/json_tools/parse_json.c				\
						src/json/json_tools/parse_json_host.c			\
						src/display/display_cgroup_tab.c				\
						src/display/display_log_counter_tab.c			\
						src/display/display_sys_log.c					\
						src/display/display_slurm_logs.c				\
						src/display/display_ib_logs.c					\
						src/display/display_sel_counters.c				\
						src/display/print_line.c						\

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