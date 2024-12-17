/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   bottleneck.h                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmosk <mmosk@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/29 18:25:43 by mmosk         #+#    #+#                 */
/*   Updated: 2024/08/29 16:30:36 by dode-boe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOTTLENECK_H
# define BOTTLENECK_H

# include <stdlib.h>
# include <stdbool.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include "libft.h"
# include "ft_printf.h"

# define FATAL_ERROR -1
# define SUCCESS 0
# define ERROR 1

//Flatten data structure by opening files during tokenizing?

typedef enum e_redirection_type
{
	INBOUND = 1,
	INBOUND_DELIMIT = 2,
	OUTBOUND = 3,
	OUTBOUND_APPEND = 4
}	t_redirection_type;

typedef struct s_redirection
{
	struct s_redirection	*next;
	t_redirection_type		type;
	int						fd;
	char					*target;
}	t_redirection;

typedef struct s_command
{
	struct s_command	*next_pipe;
	t_redirection		*inbound;
	t_redirection		*outbound;
	char				**argv;
}	t_command;

typedef enum e_exec_act
{
	CONT = 0,
	EXIT = 1
}	t_exec_act;

//My naming style:
//"free" functions free a struct, and all its existing members.
//"make" functions malloc a struct, initialize all values that must be
//	initialized for the struct to be "valid" anywhere in the program,
//	and take as few arguments as possible.
//"init" functions also malloc a struct, but fill in as many values as fits.
//"clone" functions clone a struct, creating a hard copy in memory.

////////////					Redirections						////////////

t_redirection	*make_redirection(t_redirection_type type, char *target);
void			free_redirection(t_redirection *redirection);
void			append_redirection(t_redirection **head, t_redirection *item);

////////////					Commands							////////////

t_command		*make_command(int argc);
void			free_command(t_command *command);

////////////					Environment							////////////

int				move_to_heap(char ***env);
const char		*find_entry(char **env, const char *name);
const char		*find_entry_n(char **env, const char *name, size_t n);

////////////					Shenanigans							////////////

bool			did_step(void *ptr);
int				get_argc(char **argv);
void			prune_entry(void **ptr_arr, unsigned int entry);

#endif
