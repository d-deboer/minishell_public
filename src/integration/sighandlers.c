/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sighandlers.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmosk <mmosk@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/15 11:08:43 by mmosk         #+#    #+#                 */
/*   Updated: 2024/12/03 21:48:03 by mmosk         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>

void	no_action(int sigval)
{
	(void)sigval;
}

void	stop_process(int sigval)
{
	g_sigval = sigval;
	write(1, "\n", 1);
}

void	new_line(int sigval)
{
	(void)sigval;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}
