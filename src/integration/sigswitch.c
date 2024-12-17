/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sigswitch.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmosk <mmosk@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/05 17:57:13 by mmosk         #+#    #+#                 */
/*   Updated: 2024/12/16 16:15:07 by dode-boe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>

void	interactive_signals(void)
{
	signal(SIGINT, &new_line);
	signal(SIGQUIT, SIG_IGN);
}

void	execution_signals(void)
{
	signal(SIGINT, &stop_process);
	signal(SIGQUIT, &stop_process);
}

void	heredoc_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
