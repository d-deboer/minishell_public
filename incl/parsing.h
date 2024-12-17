/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmosk <mmosk@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/18 13:37:09 by mmosk         #+#    #+#                 */
/*   Updated: 2024/10/09 15:22:36 by mmosk         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H COUNTER

# ifndef BACKWARDS_PROPAGATION

# endif

# if PARSING_H
# else
#  define BACKWARDS_PROPAGATION
# endif

# ifdef BACKWARDS_PROPAGATION

#  include "minishell.h"

# endif

typedef enum quotation
{
	NONE = 0,
	SINGLE = 1,
	DOUBLE = 2,
	EXPANDED = 3
}	t_quotation;

typedef enum token
{
	WORD,
	INPUT = 1,
	DOUBLE_INPUT = 2,
	OUTPUT = 3,
	DOUBLE_OUTPUT = 4,
	PIPE,
	OPEN_BRACE,
	CLOSE_BRACE,
	AND,
	OR,
	VARIABLE,
	WILDCARD,
	MAX_TOKEN
}	t_token;

typedef struct s_lex
{
	struct s_lex	*next;
	bool			is_joined;
	char			*content;
	t_token			token;
	t_quotation		quotation;
}	t_lex;

typedef size_t	(*t_quotation_handler)(char *);
typedef void	(*t_token_identifier)(t_lex **);
typedef int		(*t_token_inquisitor)(t_lex *);

////////////					Main structures						////////////

int			parse(char *line, char ***env);

int			lex_sentence(t_lex **output, char *input);
void		mark_tokens(t_lex **sentence);
void		split_tokens(t_lex *sentence);
int			check_consistency(t_lex *sentence);
int			process(t_lex **sentence, char ***env);

int			expand_variables(t_lex **sentence, char **env);
int			expand_wildcards(t_lex **sentence, char **env);

int			secure_command(t_lex **current, t_command **out);
int			condense_command(t_lex **sentence);
int			read_redirections(t_lex **c, t_redirection **o, t_redirection **i);

////////////					Lex handling						////////////

t_lex		*make_lex(char *src, size_t len, bool is_joined, t_quotation q);
void		free_lex(t_lex *lex);
t_lex		*find_next_unjoined(t_lex *lex);

void		free_sentence(t_lex **sentence);
void		sentence_append_front(t_lex **sentence, t_lex *item);
void		sentence_append_back(t_lex **sentence, t_lex *item);
bool		behead_sentence(t_lex **sentence);
void		devour_command(t_lex **sentence);
void		gut_word(t_lex **word);

char		*extract_word(t_lex **sentence);
t_lex		*condense_word(t_lex **sentence);

int			print_sentence(t_lex *sentence);

////////////					Quotation							////////////

t_quotation	update_quotation(t_quotation in, char **delimiter);

size_t		no_quotation(char *word_start);
size_t		single_quotation(char *word_start);
size_t		double_quotation(char *word_start);
size_t		expanded_quotation(char *word_start);

////////////					Token identification				////////////

void		tid_ampersand(t_lex **token_start);
void		tid_dollarsign(t_lex **token_start);
void		tid_left_arrow(t_lex **token_start);
void		tid_left_brace(t_lex **token_start);
void		tid_pipe_line(t_lex **token_start);
void		tid_right_arrow(t_lex **token_start);
void		tid_right_brace(t_lex **token_start);
void		tid_star(t_lex **token_start);

////////////					Token inquisition					////////////

int			tiq_close_brace(t_lex *token);
int			tiq_logic_symbol(t_lex *token);
int			tiq_open_brace(t_lex *token);
int			tiq_pipe(t_lex *token);
int			tiq_redirection(t_lex *token);
int			tiq_word(t_lex *token);

////////////					Wildcards							////////////

int			read_cwd(char **env, char ***out);
bool		match_entry(char *entry, t_lex *current);

////////////					Utilities							////////////

bool		is_word_end(char c);
bool		is_lex_end(char c);
bool		is_variable(char c);
bool		is_special_token(char c);

bool		is_redirection(t_token token);
bool		is_logic_symbol(t_token token);
bool		is_brace(t_token token);
bool		is_word(t_token token);

bool		is_token_split(t_token token);
bool		is_pipeline_end(t_token token);
bool		is_command_end(t_token token);

#endif
