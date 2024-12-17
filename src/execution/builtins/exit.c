/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dode-boe <dode-boe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/08 17:35:48 by dode-boe      #+#    #+#                 */
/*   Updated: 2024/12/05 14:21:50 by dode-boe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"

int	ft_exit(char ***env, t_command *curr)
{
	unsigned char	ret;

	(void)env;
	ret = 0;
	if (curr->argv[1] != NULL && !curr->argv[2])
		ret = 0 + ft_atoi(curr->argv[1]);
	else if (curr->argv[1] != NULL)
		return ((EINVAL << 1) + CONT);
	return ((ret << 1) + EXIT);
}

int	ft_exit_child(char ***env, t_command *curr)
{
	unsigned char	ret;

	(void)env;
	ret = 0;
	if (curr->argv[1] != NULL)
		ret = 0 + ft_atoi(curr->argv[1]);
	exit(ret);
}
