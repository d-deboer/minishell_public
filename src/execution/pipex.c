/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dode-boe <dode-boe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/12 15:02:59 by dode-boe      #+#    #+#                 */
/*   Updated: 2024/12/16 17:04:07 by dode-boe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "bottleneck.h"
#include "execution.h"

int	ft_pipex(t_command *curr, char ***env, t_pipe *pipex)
{
	int	pid;

	(void)pid;
	if (pipex->max == 0 && ft_isbuiltin(curr->argv[0]))
	{
		pipex->ret = handle_builtin(curr, env);
		pipex->i--;
		return (pipex->ret);
	}
	pipex->pid = fork();
	if (pipex->pid == -1)
		pipex = pipex_error(pipex);
	else if (pipex->pid == 0)
	{
		if (pipex->max == 0)
			child(curr, *env, pipex, ONLY_CHILD);
		if (pipex->i == pipex->max)
			child(curr, *env, pipex, LAST_CHILD);
		ft_close(pipex, pipex->close_open, 0);
		if (pipex->i == 0)
			child(curr, *env, pipex, FIRST_CHILD);
		child(curr, *env, pipex, MIDDLE_CHILD);
	}
	return (0);
}

int
	open_pipe(
		t_pipe *info
		)
{
	if (info->i == info->max)
		return (0);
	if (pipe(info->pipe_arr[info->close_open]) == -1)
	{
		info->ret = (errno << 1) + EXIT;
		perror(NULL);
	}
	return (0);
}

int
	close_pipes(
		t_pipe *info,
		t_command *command
		)
{
	if (command && close_here_doc(command->inbound) == -1)
		info->ret = (errno << 1) + EXIT;
	if (info->max == 0)
		return (0);
	if (ft_close(info, info->close_open, 1) == -1)
	{
		info->ret = (errno << 1) + EXIT;
		perror(NULL);
	}
	if (info->i == 0)
		return (0);
	if (ft_close(info, (info->close_open + 1) % 2, 0) == -1)
	{
		info->ret = (errno << 1) + EXIT;
		perror(NULL);
	}
	if (info->i == info->max)
		close_fds(info, 0, 0);
	return (0);
}

t_pipe	*pipex_error(t_pipe *info)
{
	info->ret = (errno << 1) + EXIT;
	perror(NULL);
	info->error_pipes++;
	return (info);
}
