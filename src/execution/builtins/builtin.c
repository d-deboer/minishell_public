/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dode-boe <dode-boe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/15 15:35:34 by dode-boe      #+#    #+#                 */
/*   Updated: 2024/10/29 15:04:10 by mmosk         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "execution.h"

int	bt_redirect_output(t_command *curr, t_fd *fd_struct);
int	bt_redirect_input(t_command *curr, t_fd *fd_struct);
int	bt_restore_fds(t_fd *fd_struct, int err);
int	duplicate_fds(t_fd *fd_struct);

/**
 * @brief  recognizes names of builtin commands and returns an enum value
 * corresponding to the specific builtin recognized.
 * @note length given as argument is 1 longer than the amount of characters
 * in order to also have it verify the NULL terminator. Haven't tested yet.
 * @param  *str: string corresponding to the command
 * @retval t_builtin: enum outlining all the options for builtins
 */
t_builtin	ft_isbuiltin(char *str)
{
	if (str == NULL)
		return (NOT_BUILTIN);
	if (ft_strncmp(str, "cd", ft_strlen("cd") + 1) == 0)
		return (CHANGE_DIRECTORY);
	if (ft_strncmp(str, "env", ft_strlen("env") + 1) == 0)
		return (LIST_ENVIRONMENT);
	if (ft_strncmp(str, "export", ft_strlen("export") + 1) == 0)
		return (EXPORT_ARGUMENT);
	if (ft_strncmp(str, "unset", ft_strlen("unset") + 1) == 0)
		return (UNSET_ARGUMENT);
	if (ft_strncmp(str, "pwd", ft_strlen("pwd") + 1) == 0)
		return (WORKING_DIRECTORY);
	if (ft_strncmp(str, "echo", ft_strlen("echo") + 1) == 0)
		return (ECHO_STRING);
	if (ft_strncmp(str, "exit", ft_strlen("exit") + 1) == 0)
		return (EXIT_SHELL);
	return (NOT_BUILTIN);
}

int	handle_builtin(t_command *curr, char ***env)
{
	t_fd				fd;
	int					ret;
	const t_jt_builtin	jumptable[8] = {0, ft_cd, ft_env, ft_export, ft_unset, \
	ft_pwd, ft_echo, ft_exit};

	init_fd(&fd);
	if (duplicate_fds(&fd) == -1)
		return ((errno << 1) + EXIT);
	if (bt_redirect_input(curr, &fd) == -1 \
		|| bt_redirect_output(curr, &fd) == -1)
		return (bt_restore_fds(&fd, (errno << 1) + CONT));
	ret = jumptable[ft_isbuiltin(curr->argv[0])](env, curr);
	if (bt_restore_fds(&fd, 0) & EXIT)
		return ((errno << 1) + EXIT);
	return (ret);
}

int	ft_env(char ***env, t_command *curr)
{
	int	i;
	int	argc;

	argc = 0;
	while (curr->argv[argc])
		argc++;
	if (argc > 1)
		return (EXIT_SUCCESS);
	i = 0;
	while ((*env)[i])
	{
		if ((*env)[i][0] != '?')
			printf("%s\n", (*env)[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	bt_redirect_input(
		t_command *curr,
		t_fd *fd_struct
	)
{
	int				fd;
	t_redirection	*temp;

	temp = curr->inbound;
	while (temp)
	{
		if (temp->type == INBOUND)
			fd = open(temp->target, O_RDONLY);
		else if (temp->type == INBOUND_DELIMIT)
			fd = temp->fd;
		if (fd == -1)
			return (-1);
		if (dup2(fd, STDIN_FILENO) == -1)
		{
			close(fd);
			return (-1);
		}
		fd_struct->changed_in = true;
		if (close(fd) == -1)
			return (-1);
		temp = temp->next;
	}
	return (1);
}

int	bt_redirect_output(
		t_command *curr,
		t_fd *fd_struct
	)
{
	int				fd;
	t_redirection	*temp;

	temp = curr->outbound;
	while (temp)
	{
		if (temp->type == OUTBOUND)
			fd = open(temp->target, O_WRONLY | O_CREAT | O_TRUNC);
		else if (temp->type == OUTBOUND_APPEND)
			fd = open(temp->target, O_WRONLY | O_CREAT | O_APPEND);
		if (fd == -1)
			return (-1);
		if (dup2(fd, STDOUT_FILENO) == -1)
		{
			close(fd);
			return (-1);
		}
		fd_struct->changed_out = true;
		if (close(fd) == -1)
			return (-1);
		temp = temp->next;
	}
	return (1);
}
