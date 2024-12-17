/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dode-boe <dode-boe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/08 17:39:58 by dode-boe      #+#    #+#                 */
/*   Updated: 2024/10/09 14:31:46 by dode-boe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"

int	ft_unset(char ***env, t_command *curr)
{
	int			argc;

	argc = 1;
	while (curr->argv[argc] != NULL)
	{
		unset_argument(env, curr->argv[argc], ft_strlen(curr->argv[argc]));
		argc++;
	}
	return (EXIT_SUCCESS);
}

void	unset_argument(char ***env, char *name, size_t len)
{
	int		i;

	i = 0;
	while ((*env)[i] != NULL && ft_strncmp(name, (*env)[i], len))
		i++;
	free((*env)[i]);
	while ((*env)[i])
	{
		(*env)[i] = (*env)[i + 1];
		i++;
	}
}

int	ft_unset_child(char ***env, t_command *curr)
{
	int			argc;

	argc = 1;
	while (curr->argv[argc] != NULL)
	{
		unset_argument(env, curr->argv[argc], ft_strlen(curr->argv[argc]));
		argc++;
	}
	exit(EXIT_SUCCESS);
}
