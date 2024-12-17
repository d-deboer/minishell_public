/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_variables.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmosk <mmosk@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/06 13:21:28 by mmosk         #+#    #+#                 */
/*   Updated: 2024/10/29 15:01:29 by mmosk         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static bool	clear_whitespace(char **input)
{
	did_step((void *)*input);
	while (ft_isspace(**input))
		(*input)++;
	return (did_step((void *)*input));
}

static size_t	get_item_len(char *input)
{
	size_t	len;

	len = 0;
	while (input[len] != '\0' && ft_isspace(input[len]) == false)
		len++;
	return (len);
}

int	insert_variable(t_lex **current, t_lex *previous, char *variable)
{
	t_lex	*item;
	size_t	len;

	if ((*current)->quotation == DOUBLE)
	{
		item = make_lex(variable, ft_strlen(variable), true, DOUBLE);
		if (item == NULL)
			return (FATAL_ERROR);
		sentence_append_front(current, item);
		return (0);
	}
	if (clear_whitespace(&variable))
		previous->is_joined = false;
	while (*variable != '\0')
	{
		len = get_item_len(variable);
		item = make_lex(variable, len, !ft_isspace(variable[len]), EXPANDED);
		if (item == NULL)
			return (FATAL_ERROR);
		sentence_append_front(current, item);
		current = &(*current)->next;
		variable += len;
		clear_whitespace(&variable);
	}
	return (0);
}

const char	*find_variable(t_lex **current, char **env)
{
	char		*content;
	size_t		i;
	const char	*variable;

	content = (*current)->content;
	i = ft_strlen(content);
	while (i > 0)
	{
		variable = find_entry_n(env, content, i);
		if (variable != NULL)
		{
			ft_memmove(content, content + i, ft_strlen(content + i) + 1);
			return (variable);
		}
		i--;
	}
	content[0] = '\0';
	return (NULL);
}

int	expand_variables(t_lex **sentence, char **env)
{
	t_lex		**current;
	t_lex		*previous;
	const char	*variable;

	previous = NULL;
	current = sentence;
	while (*current != NULL && is_pipeline_end((*current)->token) == false)
	{
		if ((*current)->token == VARIABLE)
		{
			behead_sentence(current);
			variable = find_variable(current, env);
			if (variable != NULL)
			{
				if (insert_variable(current, previous, (char *)variable))
					return (FATAL_ERROR);
			}
			else
				behead_sentence(current);
		}
		previous = *current;
		if (*current != NULL)
			current = &(*current)->next;
	}
	return (0);
}
