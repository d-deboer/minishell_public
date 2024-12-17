/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   process.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmosk <mmosk@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/16 21:37:26 by mmosk         #+#    #+#                 */
/*   Updated: 2024/10/09 15:11:59 by mmosk         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline int	scroll_brace_level(t_lex **current, int brace_level)
{
	while (*current != NULL && is_brace((*current)->token))
	{
		if ((*current)->token == OPEN_BRACE)
			brace_level++;
		if ((*current)->token == CLOSE_BRACE)
			brace_level--;
		behead_sentence(current);
	}
	return (brace_level);
}

static inline bool	scroll_next_branch(t_lex **current, bool next_branch)
{
	if (*current != NULL && is_logic_symbol((*current)->token))
	{
		if ((*current)->token == AND)
			next_branch = true;
		if ((*current)->token == OR)
			next_branch = false;
		behead_sentence(current);
	}
	return (next_branch);
}

static inline bool	does_match(bool next_branch, char **env)
{
	const char	*exit_status;

	exit_status = find_entry(env, "?");
	if (exit_status == NULL)
		return (false);
	return ((exit_status[0] - '0' == 0) == next_branch);
}

int	pipe_cycle(t_lex **sentence, char ***env)
{
	t_command	*command;
	int			out;

	out = expand_variables(sentence, *env);
	if (out != SUCCESS)
		return (out);
	out = expand_wildcards(sentence, *env);
	if (out != SUCCESS)
		return (out);
	out = secure_command(sentence, &command);
	if (out != SUCCESS)
		return (out);
	out = ft_execution(command, env);
	free_command(command);
	return (out);
}

int	process(t_lex **sentence, char ***env)
{
	bool		next_branch;
	int			out;

	while (*sentence != NULL)
	{
		scroll_brace_level(sentence, 0);
		out = pipe_cycle(sentence, env);
		if (out != SUCCESS || g_sigval != 0)
			return (out);
		scroll_brace_level(sentence, 0);
		next_branch = scroll_next_branch(sentence, next_branch);
		while (*sentence != NULL && does_match(next_branch, *env) == false)
		{
			devour_command(sentence);
			next_branch = scroll_next_branch(sentence, next_branch);
		}
	}
	return (0);
}

//Handles logic symbols.
// int	abstractify(t_lex **sentence, t_exec_flow **out)
// {
// 	t_lex		**current;
// 	t_command	*command;
// 	t_exec_flow	*exec_flow;
// 	int			brace_level;
// 	bool		next_branch;

// 	brace_level = 0;
// 	current = sentence;
// 	while (*current != NULL)
// 	{
// 		scroll_brace_level(current, &brace_level);
// 		if (read_command(current, &command))
// 			return (FATAL_ERROR);
// 		exec_flow = make_exec_flow(command);
// 		if (exec_flow == NULL)
// 			return (FATAL_ERROR);
// 		exec_flow->brace_level = brace_level;
// 		append_exec_flow(out, exec_flow, next_branch);
// 		scroll_brace_level(current, &brace_level);
// 		scroll_next_branch(current, &next_branch);
// 	}
// 	return (0);
// }
