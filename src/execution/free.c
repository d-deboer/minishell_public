/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dode-boe <dode-boe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/15 15:46:57 by dode-boe      #+#    #+#                 */
/*   Updated: 2024/12/17 15:10:07 by dode-boe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "execution.h"

void
	freeall(
		char **paths
	)
{
	int	i;

	i = 0;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
}

void	here_doc_end(int readsize, char *str, int pipe[2], int i)
{
	if (readsize == 0)
		write_to_pipe(str, pipe);
	if (i >= 5000)
		exit((ENOBUFS << 1) + CONT);
	else
		exit((errno << 1) + CONT);
}

int	here_doc_cycle(t_redirection *first)
{
	t_redirection	*temp;
	int				pipe_fd[2];
	int				pid;

	temp = first;
	update_temp(&temp);
	while (temp)
	{
		if (get_pipe(pipe_fd, first) == -1)
			return ((errno << 1) + EXIT);
		pid = fork();
		if (pid == 0)
			do_here_doc(temp, pipe_fd);
		else if (pid == -1)
			return (here_doc_error(pipe_fd, first, 1));
		waitpid(pid, &pid, 0);
		if (WIFSIGNALED(pid))
			return (((128 + WTERMSIG(pid)) << 1) + CONT);
		if (update_redirection(pipe_fd, temp) == -1)
			return (here_doc_error(pipe_fd, first, 1));
		temp = temp->next;
		update_temp(&temp);
	}
	return ((SUCCESS << 1) + CONT);
}

const char	*prot_find_entry(char **env, const char *name)
{
	const char	*ret;
	int			i;

	ret = find_entry(env, name);
	if (ret)
		return (ret);
	i = 0;
	while (name[i])
		i++;
	return (name + i);
}

char	*prot_cwd(char	*buf, size_t size)
{
	char	*ret;

	ret = getcwd(buf, size);
	if (!ret)
		buf[0] = '\0';
	return (buf);
}
