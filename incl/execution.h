/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execution.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dode-boe <dode-boe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/09 15:25:23 by dode-boe      #+#    #+#                 */
/*   Updated: 2024/12/17 15:10:48 by dode-boe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H COUNTER

# ifndef BACKWARDS_PROPAGATION

# endif

# if EXECUTION_H
# else
#  define BACKWARDS_PROPAGATION
# endif

# ifdef BACKWARDS_PROPAGATION

#  include "minishell.h"
#  include "dirent.h"

# endif

# include "pipex.h"

typedef struct s_fd
{
	int		out;
	bool	changed_out;
	int		in;
	bool	changed_in;
}			t_fd;

//Values are important because of bitwise operations later down the line
typedef enum e_child_type
{
	ONLY_CHILD = 0,
	FIRST_CHILD = 1,
	LAST_CHILD = 2,
	MIDDLE_CHILD = 3
}	t_child_type;

typedef enum e_builtin
{
	NOT_BUILTIN,
	CHANGE_DIRECTORY,
	LIST_ENVIRONMENT,
	EXPORT_ARGUMENT,
	UNSET_ARGUMENT,
	WORKING_DIRECTORY,
	ECHO_STRING,
	EXIT_SHELL
}	t_builtin;

typedef struct s_ugly_helper
{
	int		ret;
	char	buf[2000];
}				t_ugly_helper;

////////////					Input verification					////////////

void		ft_debug_welcome(void);
void		ft_printbatch(t_command *batch);

////////////					Builtin commands					////////////

void		heredoc_signals(void);

t_builtin	ft_isbuiltin(char *str);
int			handle_builtin(t_command *curr, char ***env);

int			ft_cd(char ***env, t_command *curr);
int			ft_env(char ***env, t_command *curr);
int			ft_export(char ***env, t_command *curr);
int			ft_unset(char ***env, t_command *curr);
int			ft_pwd(char ***env, t_command *curr);
int			ft_echo(char ***env, t_command *cur);
int			ft_exit(char ***env, t_command *curr);

int			ft_cd_child(char ***env, t_command *curr);
int			ft_echo_child(char ***env, t_command *cur);
int			ft_exit_child(char ***env, t_command *curr);
int			ft_export_child(char ***env, t_command *curr);
int			ft_pwd_child(char ***env, t_command *curr);
int			ft_unset_child(char ***env, t_command *curr);
int			ft_env_child(char ***env, t_command *curr);

int			ft_dummy_export(char ***env, int input);

int			errorcheck_export_argument(t_command *curr);
int			exportstrlen(char *str);

int			export_argument(char ***env, char *str);
void		unset_argument(char ***env, char *name, size_t len);

char		**ft_paths(char **env);

int			ft_execution(t_command *command, char ***env);

int			init_pipex(t_pipe *pipex, t_command *command);
int			ft_pipex(t_command *curr, char ***env, t_pipe *pipex);
int			ft_pipex_end(t_pipe *pipex);

void		do_here_doc(t_redirection *name, int pipe[2]);
int			init_here_doc(t_command *command);
void		update_temp(t_redirection **temp);
int			close_here_doc(t_redirection *list);
int			here_doc_cycle(t_redirection *first);
void		here_doc_end(int readsize, char *str, int pipe[2], int i);
int			update_redirection(int pipe_fd[2], t_redirection *temp);
int			here_doc_error(int pipe_fd[2], t_redirection *inbound, int mode);
void		update_temp(t_redirection **temp);
int			get_pipe(int pipe_fd[2], t_redirection *inbound);

char		*ft_strjoin_minishell(char *s1, char *s2);

int			write_to_pipe(char *str, int pipe_fd[2]);

void		init_fd(t_fd *fd_struct);

void		std_redirect(t_pipe *info, t_child_type mode);

void		redirect_input(t_pipe *info, t_command *curr, t_child_type mode);

void		redirect_output(t_pipe *info, t_command *curr, t_child_type mode);

int			pipex_main(t_command *command, char ***env);

void		child(t_command *curr, char **env, \
			t_pipe *pipex, t_child_type mode);

char		*prot_cwd(char	*buf, size_t size);
const char	*prot_find_entry(char **env, const char *name);

#endif