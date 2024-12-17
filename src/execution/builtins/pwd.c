/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: dode-boe <dode-boe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/08 17:35:30 by dode-boe      #+#    #+#                 */
/*   Updated: 2024/10/09 14:32:30 by dode-boe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"

int	ft_pwd(char ***env, t_command *curr)
{
	char	str[2000];
	int		size;

	(void)env;
	if (curr->argv[1] && curr->argv[1][0] == '-')
	{
		ft_fprintf(STDERR_FILENO, "pwd: %s: no flags\n", curr->argv[1][0]);
		return (EXIT_FAILURE);
	}
	size = 200;
	while (size < 2000)
	{
		if (getcwd(str, size))
			break ;
		else if (errno == ERANGE)
			size += 200;
		else
			return ((errno << 1) + EXIT);
	}
	printf("%s\n", str);
	return (EXIT_SUCCESS);
}

int	ft_pwd_child(char ***env, t_command *curr)
{
	char	str[2000];
	int		size;

	(void)env;
	if (curr->argv[1] && curr->argv[1][0] == '-')
	{
		ft_fprintf(STDERR_FILENO, "pwd: %s: no flags\n", curr->argv[1][0]);
		exit(EXIT_FAILURE);
	}
	size = 200;
	while (size < 2000)
	{
		if (getcwd(str, size))
			break ;
		else if (errno == ERANGE)
			size += 200;
		else
			exit(errno);
	}
	printf("%s\n", str);
	exit(EXIT_SUCCESS);
}
