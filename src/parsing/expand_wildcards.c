/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_wildcards.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmosk <mmosk@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/06 13:57:32 by mmosk         #+#    #+#                 */
/*   Updated: 2024/10/09 15:16:24 by mmosk         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	concatenate_wildcards(t_lex **current)
{
	while (*current != NULL && (*current)->is_joined == true)
	{
		if ((*current)->token == WILDCARD
			&& (*current)->next != NULL
			&& (*current)->next->token == WILDCARD)
		{
			behead_sentence(current);
			continue ;
		}
		current = &(*current)->next;
	}
}

void	prune_dot(char **entries)
{
	unsigned int	i;

	i = 0;
	while (entries[i] != NULL)
	{
		if (entries[i][0] == '.')
		{
			prune_entry((void **)entries, i);
			continue ;
		}
		i++;
	}
}

void	prune_entries(char **entries, t_lex *current)
{
	unsigned int	i;

	i = 0;
	while (entries[i] != NULL)
	{
		if (match_entry(entries[i], current) == false)
		{
			prune_entry((void **)entries, i);
			continue ;
		}
		i++;
	}
}

int	lex_entries(char **env, t_lex **current)
{
	char	**entries;
	int		i;
	int		out;
	t_lex	*item;

	out = read_cwd(env, &entries);
	if (out != SUCCESS)
		return (out);
	concatenate_wildcards(current);
	if ((*current)->token == WILDCARD)
		prune_dot(entries);
	prune_entries(entries, *current);
	gut_word(current);
	i = 0;
	while (entries[i] != NULL)
	{
		item = make_lex(entries[i], ft_strlen(entries[i]), false, EXPANDED);
		if (item == NULL)
			return (free_ptr_arr((void **)entries), FATAL_ERROR);
		sentence_append_front(current, item);
		current = &(*current)->next;
		i++;
	}
	return (free_ptr_arr((void **)entries), SUCCESS);
}

int	expand_wildcards(t_lex **sentence, char **env)
{
	t_lex	**current;
	t_lex	**word_start;
	int		out;

	current = sentence;
	word_start = current;
	while (*current != NULL && is_pipeline_end((*current)->token) == false)
	{
		if ((*current)->token == WILDCARD)
		{
			out = lex_entries(env, word_start);
			if (out != SUCCESS)
				return (out);
			current = word_start;
			if (*current == NULL)
				break ;
		}
		if ((*current)->is_joined == false)
			word_start = &(*current)->next;
		current = &(*current)->next;
	}
	return (SUCCESS);
}
