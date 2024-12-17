/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dode-boe <dode-boe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/06 16:57:01 by dode-boe      #+#    #+#                 */
/*   Updated: 2024/10/09 14:32:55 by dode-boe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "execution.h"

//It's not necessary to strdup the whole environment, we only need to realloc
//	the index array.
//Also, env gets free'd all the way up at the main() function. it's malloc'd
//	there too.

int	ft_dummy_export(char ***env, int input)
{
	int		i;
	int		out;
	char	**new;
	char	arg[20];
	char	*val;

	ft_strlcpy(arg, "?=", 20);
	val = ft_itoa(input);
	if (val == NULL)
		return (FATAL_ERROR);
	ft_strlcat(arg, val, 20);
	free(val);
	i = get_argc(*env);
	new = ft_calloc(i + 2, sizeof(char *));
	if (new == NULL)
		return (FATAL_ERROR);
	ft_memmove(new, *env, (i + 1) * sizeof(char *));
	free(*env);
	*env = new;
	out = export_argument(env, arg);
	if (out == FATAL_ERROR)
		return (*env = new, FATAL_ERROR);
	return (EXIT_SUCCESS);
}

int	ft_export(char ***env, t_command *curr)
{
	int		i;
	int		argc;
	int		out;
	char	**new;

	if (errorcheck_export_argument(curr) != 0)
		return ((errorcheck_export_argument(curr) << 1) + CONT);
	i = get_argc(*env);
	argc = get_argc(curr->argv);
	new = ft_calloc(i + argc, sizeof(char *));
	if (new == NULL)
		return (FATAL_ERROR);
	ft_memmove(new, *env, (i + 1) * sizeof(char *));
	free(*env);
	*env = new;
	argc = 1;
	while (curr->argv[argc])
	{
		out = export_argument(env, curr->argv[argc]);
		if (out == FATAL_ERROR || out == ERROR)
			return (out);
		argc++;
	}
	return (EXIT_SUCCESS);
}

//Added questionmark to allowed characters. For storing return values.
//If there's no equal sign, export doesn't do anything (in bash).
int	export_argument(char ***env, char *str)
{
	int		i;
	char	*new;

	unset_argument(env, str, exportstrlen(str));
	new = ft_strdup(str);
	if (new == NULL)
		return ((errno << 1) + FATAL_ERROR);
	i = get_argc(*env);
	(*env)[i] = new;
	(*env)[i + 1] = NULL;
	return ((0 << 1) + EXIT_SUCCESS);
}

int	errorcheck_export_argument(t_command *curr)
{
	int	i;
	int	j;
	int	alpha;

	i = 1;
	while (curr->argv[i])
	{
		j = 0;
		alpha = 0;
		while (curr->argv[i][j] && curr->argv[i][j] != '=')
		{
			if (!ft_isalnum(curr->argv[i][j]) && curr->argv[i][j] != '_')
				return (1);
			else if (ft_isalpha(curr->argv[i][j]))
				alpha++;
			j++;
		}
		if ((j == 0 && curr->argv[i][j] == '=') || !alpha)
			return (1);
		i++;
	}
	if (i == 0)
		return (1);
	return (0);
}

int	exportstrlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}

// int		ft_export(char ***env, t_command *curr)
// {
// 	int		i;
// 	int		argc;
// 	char	**new;

// 	argc = 0;
// 	while (curr->argv[argc])
// 		argc++;
// 	if (argc <= 1)
// 		return (EXIT_SUCCESS);
// 	new = (char **)ft_recalloc_2d(*env, argc - 1);
// 	if (!new)
// 		return (FATAL_ERROR);
// 	while (new[i])
// 		i++;
// 	argc = 1;
// 	while (curr->argv[argc])
// 		new[i] = ft_strdup_exp(curr->argv[argc]);
// 	ft_free_2d_array(*env);
// 	*env = new;
// }

// char	**ft_recalloc_2d(char **old, int to_add)
// {
// 	int		i;
// 	int		oldlen;
// 	char	**new;

// 	i = 0;
// 	while (old[i])
// 		i++;
// 	new = (char **)malloc((i + to_add + 1) * sizeof (char *));
// 	if (!new)
// 		return (NULL);
// 	oldlen = i;
// 	i = 0;
// 	while (i < oldlen)
// 	{
// 		new[i] = ft_strdup(old[i]);
// 		if (!new[i])
// 		{
// 			free_2d_err(new, i);
// 			return (NULL);
// 		}
// 		i++;
// 	}
// 	while (to_add >= 0)
// 		new[i++] = NULL;
// 	return (new);
// }

// void	free_2d_err(char **to_free, int i)
// {
// 	i--;
// 	while (i >= 0)
// 	{
// 		free(to_free[i]);
// 		i--;
// 	}
// 	free(to_free);
// }

// void	ft_free_2d_array(char **to_free)
// {
// 	int	i;

// 	i = 0;
// 	while (to_free[i])
// 	{
// 		free(to_free[i]);
// 		i++;
// 	}
// 	free(to_free);
// }

// char	*ft_strdup_exp(char *str)
// {
// 	int		i;
// 	bool	addone;
// 	char	*new;

// 	addone = 0;
// 	if (!str[0])
// 		return (NULL);
// 	i = 0;
// 	while (ft_isalnum(str[i]) || str[i] == '_')
// 		i++;
// 	if (str[i] != '=' && str[i] != '\0')
// 		return (NULL);
// 	if (str[i] == '\0')
// 		addone = 1;
// 	while (str[i])
// 		i++;
// 	new = (char *)malloc((i + addone) * sizeof (char));
// 	if (!new)
// 		return (NULL);
// 	ft_strlcpy(new, str, i);
// 	if (addone)
// 		new[i] = '=';
// 	if (addone)
// 		new[i + 1] = '\0';
// 	return (new);
// }
