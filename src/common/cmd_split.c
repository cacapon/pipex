/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttsubo <ttsubo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 12:58:01 by ttsubo            #+#    #+#             */
/*   Updated: 2025/03/06 15:53:40 by ttsubo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

static size_t	_quote_count(const char *s)
{
	int	i;

	i = 1;
	while (s[i] != '\0')
	{
		if (s[i] == '\'')
			return (i);
		i++;
	}
	return (1);
}

static size_t	_count_words(char const *s, char c)
{
	size_t		count;
	size_t		qt_count;
	t_word_type	sts;

	count = 0;
	sts = OUT_WORD;
	while (*s)
	{
		if (*s == '\'')
		{
			qt_count = _quote_count(s);
			if (qt_count != 1)
				count++;
			s += qt_count;
		}
		else if (sts == IN_WORD && *s == c)
			sts = OUT_WORD;
		else if (sts == OUT_WORD && *s != c)
		{
			sts = IN_WORD;
			count++;
		}
		s++;
	}
	return (count);
}

static char	**_free_result(char **result, size_t index)
{
	while (index > 0)
		free(result[--index]);
	free(result);
	return (NULL);
}

static int	_func(char **lst, char const **sp, char c, int i)
{
	size_t	wd_len;

	while (**sp == c && **sp)
		(*sp)++;
	if (**sp)
	{
		if (**sp == '\'')
			wd_len = ft_strchr((*sp) + 1, '\'') - (*sp) + 1;
		else if (!ft_strchr(*sp, c))
			wd_len = ft_strlen(*sp);
		else
			wd_len = ft_strchr(*sp, c) - (*sp);
		lst[i] = ft_substr(*sp, 0, wd_len);
		if (!lst[i])
			return (1);
		*sp += wd_len;
	}
	return (0);
}

char	**cmd_split(char const *s, char c)
{
	int		i;
	char	**lst;

	lst = (char **)ft_calloc(_count_words(s, c) + 1, sizeof(char *));
	if (!s || !lst)
		return (0);
	i = 0;
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (_func(lst, &s, c, i))
			return (_free_result(lst, i));
		i++;
	}
	lst[i] = NULL;
	return (lst);
}
