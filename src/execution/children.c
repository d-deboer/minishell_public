/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   children.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dode-boe <dode-boe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/11 17:32:21 by dode-boe      #+#    #+#                 */
/*   Updated: 2024/10/29 15:30:21 by dode-boe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "execution.h"

void	close_child_exit(t_command *curr, t_pipe *pipex, \
t_child_type mode, int err)
{
	if (mode & LAST_CHILD || curr->inbound)
		close(STDIN_FILENO);
	if (mode & FIRST_CHILD || curr->outbound)
		close(STDOUT_FILENO);
	close_fds(pipex, 0, err);
	exit(err);
}

/**
 * @brief  
 * @note   
 * @param  *curr: 
 * @param  *env: 
 * @param  *pipex: 
 * @param  mode: 
 * @retval None
 */
void
	child(
		t_command *curr,
		char **env,
		t_pipe *pipex,
		t_child_type mode
		)
{
	int					error;
	char				*path;
	const t_jt_builtin	jumptable[8] = {0, ft_cd_child, ft_env_child, \
	ft_export_child, ft_unset_child, ft_pwd_child, ft_echo_child, \
	ft_exit_child};

	std_redirect(pipex, mode);
	redirect_input(pipex, curr, mode);
	redirect_output(pipex, curr, mode);
	if (ft_isbuiltin(curr->argv[0]))
		error = jumptable[ft_isbuiltin(curr->argv[0])](&env, curr);
	path = get_path(curr->argv[0], ft_paths(env));
	execve(path, curr->argv, env);
	if (access(path, X_OK) == -1)
	{
		free(path);
		close_child_exit(curr, pipex, mode, 127);
	}
	error = errno;
	free(path);
	close_child_exit(curr, pipex, mode, error);
}

char
	*get_path(
		char *str,
		char **path
		)
{
	int		i;
	char	*ret;

	if (!path && errno == ENOMEM)
		return (NULL);
	i = 0;
	if (str && ((str[0] == '/' || str[0] == '.') || str[0] == '~'))
		return (ft_strdup(str));
	if (!path)
		return (ft_strjoin("./", str));
	while (str && path[i])
	{
		ret = ft_strjoin(path[i], str);
		if (!ret)
		{
			freeall(path);
			return (ret);
		}
		if (access(ret, F_OK | X_OK) == 0)
			return (free(path), ret);
		free(ret);
		i++;
	}
	freeall(path);
	return (str);
}

int
	ft_export_child(
		char ***env,
		t_command *curr
		)
{
	int		i;
	int		argc;
	int		out;
	char	**new;

	if (errorcheck_export_argument(curr) != 0)
		exit(errorcheck_export_argument(curr));
	i = get_argc(*env);
	argc = get_argc(curr->argv);
	new = ft_calloc(i + argc, sizeof(char *));
	if (new == NULL)
		exit(FATAL_ERROR);
	ft_memmove(new, *env, (i + 1) * sizeof(char *));
	free(*env);
	*env = new;
	argc = 1;
	while (curr->argv[argc])
	{
		out = export_argument(env, curr->argv[argc]);
		if (out == FATAL_ERROR || out == ERROR)
			exit(out);
		argc++;
	}
	exit(EXIT_SUCCESS);
}

int	
	ft_env_child(
		char ***env,
		t_command *curr
		)
{
	int		i;
	int		argc;

	argc = 0;
	while (curr->argv[argc])
		argc++;
	if (argc > 1)
		exit(EINVAL);
	i = 0;
	while ((*env)[i])
	{
		if ((*env)[i][0] != '?')
			printf("%s\n", (*env)[i]);
		i++;
	}
	exit(EXIT_SUCCESS);
}
