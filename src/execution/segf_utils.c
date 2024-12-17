/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   segf_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dode-boe <dode-boe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/03 18:39:25 by dode-boe      #+#    #+#                 */
/*   Updated: 2024/04/19 19:29:47 by dode-boe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	print_2d_char_arr(char **split)
{
	int	i;

	i = 0;
	if (!split)
	{
		ft_printf("2d array is NULL, exiting function\n");
		return ;
	}
	while (split[i])
	{
		ft_printf("%s\n", split[i++]);
	}
	ft_printf("NULL\n");
	return ;
}

void	init_pipe_arr(t_pipe *info)
{
	info->pipe_arr[0][0] = -1;
	info->pipe_arr[0][1] = -1;
	info->pipe_arr[1][0] = -1;
	info->pipe_arr[1][1] = -1;
}

void	check_info(t_pipe *info)
{
	ft_printf("Checking info\n");
	ft_printf("i is: %i\n", info->i);
	ft_printf("close_open is : %i\n", info->close_open);
	ft_printf("newest fds:\n read: %i\n", info->pipe_arr[info->close_open][0]);
	ft_printf(" write: %i\noldest fds:\n", info->pipe_arr[info->close_open][1]);
	ft_printf("read: %i\n", info->pipe_arr[(info->close_open + 1) % 2][0]);
	ft_printf(" write: %i\n", info->pipe_arr[(info->close_open + 1) % 2][1]);
}

int	allspaces(char *str)
{
	int	i;

	i = 0;
	while (str && str[i] == ' ')
		i++;
	if (str[i] == '\0')
		return (1);
	return (0);
}

char	**ft_2dpointerstrdup(char *str)
{
	char	**ret;

	ret = (char **)malloc(2 * sizeof (char *));
	if (!ret)
		return (NULL);
	ret[0] = ft_strdup(str);
	if (!ret[0])
	{
		free(ret);
		return (NULL);
	}
	ret[1] = NULL;
	return (ret);
}
