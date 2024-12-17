/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dode-boe <dode-boe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/08 17:36:00 by dode-boe      #+#    #+#                 */
/*   Updated: 2024/12/17 14:34:06 by dode-boe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"

static int	ft_isoption(char *str);

int	ft_echo(char ***env, t_command *cur)
{
	int		i;
	int		nl;

	(void)env;
	i = 1;
	nl = ft_isoption(cur->argv[1]);
	if (cur->argv[1] != NULL)
		if (cur->argv[1][0] == '-' \
			&& (cur->argv[1][1] != 'n' || cur->argv[1][2]))
			return ((EINVAL << 1) + CONT);
	if (!nl)
		i++;
	while (cur->argv[i])
	{
		if (printf("%s", cur->argv[i++]) == -1)
			perror(NULL);
		if (cur->argv[i])
			printf(" ");
	}
	if (nl && printf("\n") == -1)
		perror(NULL);
	return (EXIT_SUCCESS);
}

static int	ft_isoption(char *str)
{
	if (str == NULL || ft_strncmp("-n", str, 3))
		return (1);
	return (0);
}

int	ft_echo_child(char ***env, t_command *cur)
{
	int		i;
	int		nl;

	(void)env;
	i = 1;
	nl = ft_isoption(cur->argv[1]);
	if (cur->argv[1] != NULL)
		if (cur->argv[1][0] == '-' \
			&& (cur->argv[1][1] != 'n' || cur->argv[1][2]))
			exit(EINVAL);
	if (!nl)
		i++;
	while (cur->argv[i])
	{
		if (printf("%s", cur->argv[i++]) == -1)
			perror(NULL);
		if (cur->argv[i])
			printf(" ");
	}
	if (nl && printf("\n") == -1)
		perror(NULL);
	exit(EXIT_SUCCESS);
}
