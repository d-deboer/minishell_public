/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_paths.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dode-boe <dode-boe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/12 15:42:55 by dode-boe      #+#    #+#                 */
/*   Updated: 2024/10/09 16:38:11 by mmosk         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"
#include "execution.h"

char	**ft_paths(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (strncmp(env[i], "PATH=", 5) == 0)
			return (ft_slash_split(env[i] + 5, ':'));
		i++;
	}
	errno = EXIT_SUCCESS;
	return (NULL);
}
