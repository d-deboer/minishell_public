/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   match_entry.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmosk <mmosk@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/29 12:06:18 by mmosk         #+#    #+#                 */
/*   Updated: 2024/08/29 17:03:05 by mmosk         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

//Concatenate multiple wildcards?
bool	match_wildcard(char *entry, t_lex *current)
{
	char	*content;
	size_t	len;

	if (current->is_joined == false)
		return (true);
	current = current->next;
	content = current->content;
	len = ft_strlen(content);
	entry = ft_strnstr(entry, content, ft_strlen(entry));
	while (entry != NULL)
	{
		if (current->is_joined == false && ft_strlen(entry) == len)
			return (true);
		entry += len;
		if (match_entry(entry, current->next) == true)
			return (true);
		entry = ft_strnstr(entry, content, ft_strlen(entry));
	}
	return (false);
}

bool	match_word(char *entry, t_lex *current)
{
	char	*content;
	size_t	len;

	content = current->content;
	len = ft_strlen(content);
	if (strncmp(entry, content, len) != 0)
		return (false);
	if (current->is_joined == false && ft_strlen(entry) == len)
		return (true);
	entry += len;
	return (match_entry(entry, current->next));
}

bool	match_entry(char *entry, t_lex *current)
{
	if (current == NULL)
		return (false);
	if (current->token == WILDCARD)
		return (match_wildcard(entry, current));
	else
		return (match_word(entry, current));
}
