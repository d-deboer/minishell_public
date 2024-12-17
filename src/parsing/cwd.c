/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmosk <mmosk@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/26 11:23:22 by mmosk         #+#    #+#                 */
/*   Updated: 2024/10/09 15:14:46 by mmosk         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	get_dir_size(char *cwd)
{
	DIR		*dir;
	int		out;

	dir = opendir(cwd);
	if (dir == NULL)
		return (FATAL_ERROR);
	out = 0;
	while (readdir(dir) != NULL)
		out++;
	closedir(dir);
	return (out);
}

int	fill_cwd(char *cwd, int size, char ***out)
{
	DIR		*dir;
	int		i;

	dir = opendir(cwd);
	if (dir == NULL)
		return (free(out), FATAL_ERROR);
	i = 0;
	while (i < size)
	{
		(*out)[i] = ft_strdup(readdir(dir)->d_name);
		if ((*out)[i] == NULL)
			return (free_ptr_arr((void **)*out), FATAL_ERROR);
		i++;
	}
	closedir(dir);
	(*out)[i] = NULL;
	return (SUCCESS);
}

int	read_cwd(char **env, char ***out)
{
	char	*cwd;
	int		size;

	cwd = (char *)find_entry(env, "PWD");
	if (cwd == NULL)
		return (printf("Wildcard: Can't find PWD in environment.\n"));
	size = get_dir_size(cwd);
	if (size == FATAL_ERROR)
		return (FATAL_ERROR);
	*out = malloc((size + 1) * sizeof(char *));
	if (*out == NULL)
		return (FATAL_ERROR);
	return (fill_cwd(cwd, size, out));
}
