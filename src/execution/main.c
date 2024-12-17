/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dode-boe <dode-boe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/18 16:43:28 by dode-boe      #+#    #+#                 */
/*   Updated: 2024/12/16 17:43:09 by dode-boe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "execution.h"

int	ft_execution(t_command *command, char ***env)
{
	int	status;
	int	ret;

	status = SUCCESS;
	ret = pipex_main(command, env);
	if (ret & EXIT)
		status = FATAL_ERROR;
	if (ft_dummy_export(env, ret >> 1) == FATAL_ERROR)
		return (FATAL_ERROR);
	return (status);
}

int
	pipex_main(
		t_command *command,
		char ***env
		)
{
	t_pipe		pipex;
	int			ret;

	ret = init_here_doc(command);
	if (ret)
		return (ret);
	if (init_pipex(&pipex, command) == -1)
		return (pipex.ret);
	while (command)
	{
		open_pipe(&pipex);
		ft_pipex(command, env, &pipex);
		close_pipes(&pipex, command);
		command = command->next_pipe;
		pipex.i++;
		pipex.close_open = !pipex.close_open;
		if (pipex.ret & EXIT)
			return (ft_pipex_end(&pipex));
	}
	return (ft_pipex_end(&pipex));
}

int	ft_pipex_end(t_pipe *pipex)
{
	int	ret;
	int	issignaled;

	if (close(pipex->stdin_dup) == -1)
		pipex->ret = (errno << 1) + EXIT;
	ret = 0;
	issignaled = 0;
	if (pipex->i > pipex->error_pipes)
		waitpid(pipex->pid, &ret, 0);
	pipex->i--;
	while (pipex->i > 0)
	{
		wait(NULL);
		pipex->i--;
	}
	if (pipex->ret)
		return (pipex->ret);
	if (WIFEXITED(ret))
		return ((WEXITSTATUS(ret) << 1) + CONT);
	else if (WIFSIGNALED(ret))
		return ((WTERMSIG(ret) << 1) + CONT);
	return ((ret << 1) + EXIT);
}

int	init_pipex(t_pipe *pipex, t_command *command)
{
	pipex->error_pipes = 0;
	pipex->ret = 0;
	pipex->pid = 0;
	pipex->i = 0;
	pipex->max = 1;
	while (command->next_pipe)
	{
		command = command->next_pipe;
		pipex->max++;
	}
	pipex->max--;
	pipex->close_open = 0;
	pipex->pipe_arr[0][0] = -1;
	pipex->pipe_arr[0][1] = -1;
	pipex->pipe_arr[1][0] = -1;
	pipex->pipe_arr[1][1] = -1;
	pipex->stdin_dup = dup(STDIN_FILENO);
	if (pipex->stdin_dup == -1)
	{
		pipex->ret = (errno << 1) + EXIT;
		close_here_doc(command->inbound);
		return (-1);
	}
	return (0);
}

int	init_here_doc(t_command *command)
{
	t_command	*temp;
	int			ret;

	temp = command;
	while (temp)
	{
		ret = here_doc_cycle(temp->inbound);
		if (ret)
			return (ret);
		temp = temp->next_pipe;
	}
	return ((SUCCESS << 1) + CONT);
}
