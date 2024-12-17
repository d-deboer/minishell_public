/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   extract_word.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmosk <mmosk@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/09 13:25:50 by mmosk         #+#    #+#                 */
/*   Updated: 2024/07/10 16:16:11 by mmosk         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

size_t	get_word_len(t_lex *word)
{
	size_t	len;

	if (word == NULL)
		return (0);
	len = ft_strlen(word->content);
	while (word->next != NULL && word->is_joined == true)
	{
		word = word->next;
		len += ft_strlen(word->content);
	}
	return (len);
}

char	*extract_word(t_lex **sentence)
{
	size_t	len;
	char	*out;

	len = get_word_len(*sentence);
	out = malloc(sizeof(char) * (len + 1));
	if (out == NULL)
		return (NULL);
	out[0] = '\0';
	if (*sentence == NULL)
		return (out);
	ft_strlcat(out, (*sentence)->content, len + 1);
	while (behead_sentence(sentence))
	{
		ft_strlcat(out, (*sentence)->content, len + 1);
	}
	return (out);
}
