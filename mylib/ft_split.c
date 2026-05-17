/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maryaada <maryaada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 15:35:17 by maryaada          #+#    #+#             */
/*   Updated: 2026/05/17 17:08:44 by maryaada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static	int	word_count(char const *s, char c)
{
	int	i;
	int	total_words;
	int	in_word;

	i = 0;
	total_words = 0;
	in_word = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && in_word == 0)
		{
			in_word = 1;
			total_words++;
		}
		else if (s[i] == c)
		{
			in_word = 0;
		}
		i++;
	}
	return (total_words);
}

static	void	free_all(char **dest)
{
	int	i;

	i = 0;
	while (dest[i] != NULL)
	{
		free(dest[i]);
		i++;
	}
	free (dest);
}

static	unsigned int	set_end(unsigned int start, const char *str, char c)
{
	unsigned int	end;

	end = start;
	while (str[end] != c && str[end] != '\0')
		end ++;
	return (end);
}

char	**ft_split(char const *s, char c)
{
	unsigned int		w_s;
	int					words;
	char				**basket;

	words = -1;
	w_s = 0;
	if (!s)
		return (NULL);
	basket = malloc(sizeof(char *) * (word_count(s, c) + 1));
	if (basket == NULL)
		return (NULL);
	while (s[w_s] != '\0')
	{
		while (s[w_s] == c && s[w_s] != '\0')
			w_s++;
		if (w_s < (set_end(w_s, s, c)))
		{
			basket[++words] = ft_substr(s, w_s, (set_end(w_s, s, c) - w_s));
			if (!basket[words])
				return (free_all(basket), NULL);
		}
		w_s = set_end(w_s, s, c);
	}
	return (basket[++words] = NULL, basket);
}
