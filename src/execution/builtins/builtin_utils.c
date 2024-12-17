/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dode-boe <dode-boe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/03 16:05:46 by dode-boe      #+#    #+#                 */
/*   Updated: 2024/10/01 15:32:12 by dode-boe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "bottleneck.h"
#include "pipex.h"

int	duplicate_fds(t_fd *fd_struct)
{
	int	temp;

	fd_struct->in = dup(STDIN_FILENO);
	if (fd_struct->in == -1)
		return (-1);
	fd_struct->out = dup(STDOUT_FILENO);
	if (fd_struct->out == -1)
	{
		temp = errno;
		if (close(fd_struct->in) == -1)
			return (-1);
		errno = temp;
		return (-1);
	}
	return (0);
}

int	bt_restore_fds(t_fd *fd_struct, int err)
{
	int	temp_err;

	temp_err = err;
	if (fd_struct->changed_in)
		if (dup2(fd_struct->in, STDIN_FILENO) == -1)
			err = (errno << 1) + EXIT;
	if (close(fd_struct->in) == -1)
		err = (errno << 1) + EXIT;
	if (fd_struct->changed_out)
		if (dup2(fd_struct->out, STDOUT_FILENO) == -1)
			err = (errno << 1) + EXIT;
	if (close(fd_struct->out) == -1)
		err = (errno << 1) + EXIT;
	return (err);
}

void	init_fd(t_fd *fd_struct)
{
	fd_struct->changed_in = 0;
	fd_struct->changed_out = 0;
	fd_struct->in = -1;
	fd_struct->out = -1;
}
