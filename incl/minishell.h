/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmosk <mmosk@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/17 22:00:40 by mmosk         #+#    #+#                 */
/*   Updated: 2024/08/16 16:40:06 by mmosk         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H COUNTER

# include "bottleneck.h"

# ifndef BACKWARDS_PROPAGATION

#  include "execution.h"
#  include "parsing.h"

# endif

# if MINISHELL_H
# else
#  define BACKWARDS_PROPAGATION
# endif

# ifdef BACKWARDS_PROPAGATION

# endif

//Look Douwe! I made spaghetti!

//This include structure makes it so that when a header is included,
//	it automatically includes all headers it is dependent on,
//	and all the headers that are dependent on it.

//But in all seriousness, this seems like a pretty good include structure.
//Just far too over-engineered for this project.
//Oh, and use of the "COUNTER" macro instantly turns this into pure evil.

extern int	g_sigval;

void	no_action(int sigval);
void	stop_process(int sigval);
void	new_line(int sigval);

void	interactive_signals(void);
void	execution_signals(void);

#endif
