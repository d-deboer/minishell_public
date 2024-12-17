/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: dode-boe <dode-boe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/15 17:05:07 by dode-boe      #+#    #+#                 */
/*   Updated: 2024/12/17 14:25:01 by dode-boe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "bottleneck.h"
#include <signal.h>

//can fail
// I guess everything can fail
int	ctrldhandler(char *str, int n)
{
	return (ft_fprintf(STDERR_FILENO, \
	": warning: here-document at\
	 line %i delimited by end-of-file (wanted '%s')\n", \
	n, str));
}

void	do_here_doc(t_redirection *name, int pipe[2])
{
	char	str[5001];
	char	buffer[1001];
	int		i;
	int		readsize;

	heredoc_signals();
	i = 0;
	ft_bzero(str, 5001);
	readsize = read(STDIN_FILENO, buffer, 1000);
	while (i + readsize < 5000 && (readsize > 0))
	{
		buffer[readsize] = '\0';
		if (ft_strncmp(buffer, name->target, ft_strlen(buffer) - 1) == 0)
		{
			write_to_pipe(str, pipe);
		}
		ft_strncpy(str + i, buffer, readsize);
		i += readsize;
		readsize = read(STDIN_FILENO, buffer, 1000);
	}
	here_doc_end(readsize, str, pipe, i);
}

int	close_here_doc(t_redirection *list)
{
	int				ret;
	t_redirection	*temp;

	ret = 0;
	temp = list;
	update_temp(&temp);
	while (temp)
	{
		while (temp && temp->type != INBOUND_DELIMIT)
			temp = temp->next;
		if (temp && temp->fd != -1)
		{
			if (close(temp->fd) == -1)
				ret = -1;
		}
		temp = temp->next;
		update_temp(&temp);
	}
	return (ret);
}

int	get_pipe(int pipe_fd[2], t_redirection *inbound)
{
	int	ret;

	if (pipe(pipe_fd) == -1)
	{
		ret = errno;
		here_doc_error(NULL, inbound, 0);
		errno = ret;
		return (-1);
	}
	return (0);
}

int	here_doc_error(int pipe_fd[2], t_redirection *inbound, int mode)
{
	t_redirection	*temp;
	int				ret;

	ret = errno;
	temp = inbound;
	while (temp)
	{
		while (temp && temp->type != INBOUND_DELIMIT)
			temp = temp->next;
		if (temp && temp->fd != -1)
			close(temp->fd);
	}
	if (pipe_fd)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
	}
	if (mode == 0)
		return ((ret << 1) + EXIT);
	else
		return (-1);
}
