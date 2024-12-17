/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_command.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmosk <mmosk@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/17 16:06:37 by mmosk         #+#    #+#                 */
/*   Updated: 2024/10/29 15:03:07 by mmosk         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static inline int	get_argc_sentence(t_lex **command)
{
	int		argc;
	t_lex	**current;
	t_token	token;

	current = command;
	argc = 0;
	if (*current != NULL)
		token = (*current)->token;
	while (*current != NULL && is_command_end(token) == false)
	{
		token = (*current)->token;
		if (token == WORD)
			argc++;
		if (is_redirection(token))
			argc--;
		current = &(*current)->next;
	}
	return (argc);
}

//Handles commands & pipes.
//free() structure could use some work.
int	read_command(t_lex **current, t_command **out)
{
	int	argc;
	int	i;

	if (condense_command(current))
		return (FATAL_ERROR);
	argc = get_argc_sentence(current);
	*out = make_command(argc);
	if (*out == NULL)
		return (FATAL_ERROR);
	if (read_redirections(current, &(*out)->outbound, &(*out)->inbound))
		return (FATAL_ERROR);
	i = 0;
	while (i < argc)
	{
		(*out)->argv[i] = extract_word(current);
		if ((*out)->argv[i] == NULL)
			return (FATAL_ERROR);
		i++;
	}
	if (*current != NULL && (*current)->token == PIPE)
	{
		behead_sentence(current);
		return (read_command(current, &(*out)->next_pipe));
	}
	return (0);
}

int	secure_command(t_lex **current, t_command **out)
{
	*out = NULL;
	if (read_command(current, out) == FATAL_ERROR)
	{
		free_command(*out);
		*out = NULL;
		return (FATAL_ERROR);
	}
	return (SUCCESS);
}
