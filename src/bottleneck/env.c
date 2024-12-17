/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmosk <mmosk@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/05 15:40:27 by mmosk         #+#    #+#                 */
/*   Updated: 2024/10/29 14:54:18 by mmosk         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "bottleneck.h"

int	move_to_heap(char ***env)
{
	size_t	i;
	char	**out;

	i = 0;
	while ((*env)[i] != NULL)
		i++;
	out = malloc(sizeof(char *) * (i + 1));
	if (out == NULL)
		return (1);
	i = 0;
	while ((*env)[i] != NULL)
	{
		out[i] = ft_strdup((*env)[i]);
		if (out[i] == NULL)
			return (free_ptr_arr((void **)out), 1);
		i++;
	}
	out[i] = NULL;
	*env = out;
	return (0);
}

const char	*find_entry(char **env, const char *name)
{
	int	i;

	i = 0;
	while (env[i] != NULL && ft_strncmp(env[i], name, ft_strlen(name)))
		i++;
	if (!env[i])
		return (NULL);
	return (env[i] + ft_strlen(name) + 1);
}

const char	*find_entry_n(char **env, const char *name, size_t n)
{
	int	i;

	i = 0;
	while (env[i] != NULL && ft_strncmp(env[i], name, n))
		i++;
	if (!env[i])
		return (NULL);
	return (env[i] + n + 1);
}
