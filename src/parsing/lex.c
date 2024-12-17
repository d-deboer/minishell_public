/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lex.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmosk <mmosk@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/27 14:28:09 by mmosk         #+#    #+#                 */
/*   Updated: 2024/08/06 14:09:28 by mmosk         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_lex	*make_lex(char *src, size_t len, bool is_joined, t_quotation quotation)
{
	t_lex	*out;

	out = malloc(sizeof(t_lex));
	if (out == NULL)
		return (NULL);
	out->content = malloc(sizeof(char) * (len + 1));
	if (out->content == NULL)
		return (free(out), NULL);
	ft_strlcpy(out->content, src, len + 1);
	out->next = NULL;
	out->is_joined = is_joined;
	out->token = WORD;
	out->quotation = quotation;
	return (out);
}

void	free_lex(t_lex *lex)
{
	free(lex->content);
	free(lex);
}

t_lex	*find_next_unjoined(t_lex *lex)
{
	while (lex != NULL && lex->is_joined == true)
	{
		lex = lex->next;
	}
	if (lex == NULL)
		return (NULL);
	return (lex->next);
}
