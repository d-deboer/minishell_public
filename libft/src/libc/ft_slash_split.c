/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_slash_split.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmosk <mmosk@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/07 18:02:59 by mmosk         #+#    #+#                 */
/*   Updated: 2024/08/07 18:05:15 by mmosk         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_wordcounter(char const *s, char c);
static int	ft_wordlen(char const *s, char c, int word);
static void	ft_splitfree(char **s2, int i);
static void	ft_fillword(char const *s, char c, int word, char **s2);

char	**ft_slash_split(char const *s, char c)
{
	char	**s2;
	int		i;
	int		wrdcnt;

	wrdcnt = ft_wordcounter(s, c);
	s2 = (char **)malloc((wrdcnt + 1) * sizeof (char *));
	if (!s2)
		return (NULL);
	i = 0;
	while (i < wrdcnt)
	{
		s2[i] = (char *)malloc((ft_wordlen(s, c, i) + 2) * sizeof (char));
		if (!s2[i])
		{
			ft_splitfree(s2, i);
			return (NULL);
		}
		ft_fillword(s, c, i, s2);
		i++;
	}
	s2[i] = NULL;
	return (s2);
}

static int	ft_wordcounter(char const *s, char c)
{
	int	wordcount;
	int	counting;

	counting = 0;
	wordcount = 0;
	while (*s)
	{
		if (counting == 0)
		{
			while (*s == c)
				s++;
			if (*s != '\0')
				counting = 1;
		}
		if (counting == 1)
		{
			while (*s != c && *s != '\0')
				s++;
			wordcount++;
			counting = 0;
		}
	}
	return (wordcount);
}

static int	ft_wordlen(char const *s, char c, int word)
{
	int	wordlength;
	int	wordcount;
	int	i;

	i = 0;
	wordlength = 0;
	wordcount = 0;
	while (s[i] == c)
		i++;
	while (s[i] && wordcount < word)
	{
		while (s[i] != c && s[i] != '\0')
			i++;
		while (s[i] == c)
			i++;
		wordcount++;
	}
	while (s[(i + wordlength)] != c && s[(i + wordlength)] != '\0')
		wordlength++;
	return (wordlength);
}

static void	ft_splitfree(char **s2, int i)
{
	if (i > 0)
	{
		i--;
		while (i >= 0)
		{
			free(s2[i]);
			i--;
		}
	}
	free(s2);
}

static void	ft_fillword(char const *s, char c, int word, char **s2)
{
	int	i2;
	int	i;
	int	wordcount;

	i2 = 0;
	i = 0;
	wordcount = 0;
	while (s[i] == c)
		i++;
	while (s[i] && wordcount < word)
	{
		while (s[i] != c && s[i] != '\0')
			i++;
		while (s[i] == c)
			i++;
		wordcount++;
	}
	while ((s[i + i2] != c) && (s[i + i2] != '\0'))
	{
		s2[wordcount][i2] = (char)s[(i + i2)];
		i2++;
	}
	s2[wordcount][i2] = '/';
	i2++;
	s2[wordcount][i2] = '\0';
}
