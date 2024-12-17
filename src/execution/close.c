/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   close.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dode-boe <dode-boe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/16 13:57:59 by dode-boe      #+#    #+#                 */
/*   Updated: 2024/09/30 14:09:39 by dode-boe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "bottleneck.h"

int	ft_close(t_pipe *info, int n1, int n2)
{
	int	ret;

	ret = 0;
	if (info->pipe_arr[n1][n2] != -1)
	{
		ret = close(info->pipe_arr[n1][n2]);
		info->pipe_arr[n1][n2] = -1;
	}
	if (ret == -1)
		info->ret = (errno << 1) + EXIT;
	return (ret);
}

void	close_fds_exit(char *str, t_pipe *info, int also, int err)
{
	int	i;
	int	j;

	if (err == 127)
		ft_fprintf(2, "%s: command not found\n", str);
	else
		ft_fprintf(2, "%s: no such file or directory\n", str);
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 2)
		{
			if (ft_close(info, info->close_open, j) == -1)
				err = errno;
			i++;
			j++;
		}
		info->close_open = (info->close_open + 1) % 2;
	}
	err = close_other_fds(info, also, err);
	exit(err);
}

void	close_fds(t_pipe *info, int also, int err)
{
	int	i;
	int	j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 2)
		{
			if (ft_close(info, info->close_open, j) == -1)
			{
				err = errno;
				info->ret = (errno << 1) + EXIT;
				perror(NULL);
			}
			j++;
		}
		i++;
		info->close_open = (info->close_open + 1) % 2;
	}
	close_other_fds(info, also, err);
}

int	close_other_fds(t_pipe *info, int also, int err)
{
	if (also & 1)
	{
		if (close(STDIN_FILENO) == -1)
		{
			info->ret = (errno << 1) + EXIT;
			err = errno;
			perror(NULL);
		}
	}
	if (also & 2)
	{
		if (close(STDOUT_FILENO) == -1)
		{
			info->ret = (errno << 1) + EXIT;
			err = errno;
			perror(NULL);
		}
	}
	return (err);
}
