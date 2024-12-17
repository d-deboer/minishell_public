/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dode-boe <dode-boe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/16 15:12:16 by dode-boe      #+#    #+#                 */
/*   Updated: 2024/12/16 17:27:08 by dode-boe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void
	freesplit(
		char **split,
		char *str
		)
{
	int	i;
	int	err;

	if (str)
	{
		err = errno;
		perror(str);
	}
	i = 0;
	while (split && split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
	if (str)
		exit(err);
}

void	freesplit_err(char **split, int i)
{
	i -= 1;
	while (i >= 0)
	{
		free(split[i]);
		i--;
	}
	free(split);
}

void	update_temp(t_redirection **temp)
{
	while ((temp && *temp) && (*temp)->type != INBOUND_DELIMIT)
		*temp = (*temp)->next;
}

char	*ft_strjoin_minishell(char *s1, char *s2)
{
	char	*ret;
	int		i;
	int		j;

	if (s1)
		ret = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	else
		ret = malloc(ft_strlen(s2) + 1);
	if (!ret)
	{
		free(s2);
		free(s1);
		return (NULL);
	}
	i = -1;
	while (s1 && s1[++i])
		ret[i] = s1[i];
	j = -1;
	while (s2 && s2[++j])
		ret[i++] = s2[j];
	free(s1);
	free(s2);
	return (ret);
}
