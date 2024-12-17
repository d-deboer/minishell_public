/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dode-boe <dode-boe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/09 16:34:15 by dode-boe      #+#    #+#                 */
/*   Updated: 2024/12/17 14:43:16 by dode-boe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "pipex.h"

void
	std_redirect(
		t_pipe *info,
		t_child_type mode
	)
{
	if (mode & FIRST_CHILD)
	{
		if (dup2(info->pipe_arr[info->close_open][1], STDOUT_FILENO) == -1)
			close_fds_exit(NULL, info, 0, errno);
		if (ft_close(info, info->close_open, 1) == -1)
			close_fds_exit(NULL, info, 2, errno);
	}
	if (mode & LAST_CHILD)
	{
		if (dup2(info->pipe_arr[!info->close_open][0], STDIN_FILENO) == -1)
		{
			if (mode == MIDDLE_CHILD)
				close_fds_exit(NULL, info, 2, errno);
			close_fds_exit(NULL, info, 0, errno);
		}
		if (ft_close(info, !info->close_open, 0) == -1)
		{
			if (mode == MIDDLE_CHILD)
				close_fds_exit(NULL, info, 3, errno);
			close_fds_exit(NULL, info, 1, errno);
		}
	}
}

void
	redirect_input(
		t_pipe *info,
		t_command *curr,
		t_child_type mode
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
			close_fds_exit(NULL, info, mode, errno);
		mode = mode & (FIRST_CHILD + LAST_CHILD);
		if (dup2(fd, STDIN_FILENO) == -1)
		{
			info->ret = errno;
			if (close(fd) == -1)
				info->ret = errno;
			close_fds_exit(NULL, info, mode, info->ret);
		}
		if (close(fd) == -1)
			close_fds_exit(NULL, info, mode, errno);
		temp = temp->next;
	}
}

void
	redirect_output(
		t_pipe *info,
		t_command *curr,
		t_child_type mode
	)
{
	int				fd;
	t_redirection	*temp;

	temp = curr->outbound;
	while (temp)
	{
		if (temp->type == OUTBOUND)
			fd = open(temp->target, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		else if (temp->type == OUTBOUND_APPEND)
			fd = open(temp->target, O_WRONLY | O_CREAT | O_APPEND, 0666);
		if (fd == -1)
			close_fds_exit(NULL, info, mode, errno);
		mode = mode & (LAST_CHILD + FIRST_CHILD);
		if (dup2(fd, STDOUT_FILENO) == -1)
		{
			info->ret = errno;
			if (close(fd) == -1)
				info->ret = errno;
			close_fds_exit(NULL, info, mode, info->ret);
		}
		if (close(fd) == -1)
			close_fds_exit(NULL, info, mode, errno);
		temp = temp->next;
	}
}

int	write_to_pipe(char *str, int pipe_fd[2])
{
	int	ret;

	if (str && write(pipe_fd[1], str, ft_strlen(str)) == -1)
	{
		ret = errno;
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		exit ((ret << 1) + EXIT);
	}
	if (close(pipe_fd[1]) == -1)
	{
		ret = errno;
		close(pipe_fd[0]);
		exit((ret << 1) + EXIT);
	}
	if (close(pipe_fd[0]) == -1)
		exit((errno << 1) + EXIT);
	exit((SUCCESS << 1) + CONT);
}

int	update_redirection(int pipe_fd[2], t_redirection *temp)
{
	if (close(pipe_fd[1]) == -1)
	{
		close(pipe_fd[0]);
		return (-1);
	}
	temp->fd = pipe_fd[0];
	return (0);
}
