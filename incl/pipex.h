/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dode-boe <dode-boe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/17 17:27:27 by dode-boe      #+#    #+#                 */
/*   Updated: 2024/10/09 16:41:10 by mmosk         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <string.h>
# include <errno.h>
# include <unistd.h>
# include <limits.h>
# include <fcntl.h>
# include <stdbool.h>
# include <sys/wait.h>
# include <bsd/string.h>

# include "bottleneck.h"

typedef struct s_pipe
{
	int		error_pipes;
	int		ret;
	int		pid;
	int		i;
	int		max;
	int		close_open;
	int		pipe_arr[2][2];
	int		stdin_dup;
}				t_pipe;

typedef int	(*t_jt_builtin)(char ***, t_command *);

int			open_pipe(t_pipe *info);
int			close_pipes(t_pipe *info, t_command *command);
char		*get_path(char *str, char **path);
t_pipe		*pipex_error(t_pipe *info);
void		print_2d_char_arr(char **split);
void		init_pipe_arr(t_pipe *info);
void		check_info(t_pipe *info);
void		close_fds(t_pipe	*info, int also, int err);
int			ft_close(t_pipe	*info, int n1, int n2);
void		close_fds_exit(char	*str, t_pipe *info, int also, int err);
int			close_other_fds(t_pipe *info, int also, int err);
void		freesplit(char **split, char *str);
void		freesplit_err(char **split, int i);
char		**ft_2dpointerstrdup(char *str);
int			allspaces(char *str);
void		freeall(char **paths);

#endif
