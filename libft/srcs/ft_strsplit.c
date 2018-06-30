/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 16:03:12 by pmilan            #+#    #+#             */
/*   Updated: 2018/04/20 21:13:28 by pmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int		ft_count_words(char const *s, char c)
{
	int i;
	int count;

	i = 0;
	count = 0;
	if (s[0] == 0)
		return (0);
	while (s[i])
	{
		while (s[i] == c)
			i++;
		while (s[i] && s[i] != c)
			i++;
		count++;
	}
	if (s[i - 1] == c)
		count--;
	return (count);
}

static int		ft_malloc_strings(const char *s, char **ret, int nb, char c)
{
	int		i;
	int		j;
	int		length;

	i = 0;
	j = 0;
	while (s[i] && j < nb)
	{
		length = 0;
		while (s[i] == c)
			i++;
		while (s[i] && s[i] != c)
		{
			i++;
			length++;
		}
		if (!(ret[j] = (char *)malloc(sizeof(*s) * (length + 1))))
			return (-1);
		j++;
	}
	return (0);
}

static void		ft_cpy_words(const char *s, char **ret, int nb, char c)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	k = 0;
	while (s[k] && nb != 0)
	{
		while (s[k] && s[k] == c)
			k++;
		j = 0;
		while (s[k] && s[k] != c)
		{
			ret[i][j++] = s[k++];
			if (s[k] == c || s[k] == '\0')
				ret[i][j] = '\0';
		}
		--nb;
		i++;
	}
}

char			**ft_strsplit(char const *s, char c)
{
	int		nb_words;
	char	**ret;

	if (s == NULL)
		return (NULL);
	nb_words = ft_count_words(s, c);
	if (!(ret = (char **)malloc(sizeof(*ret) * (nb_words + 1))))
		return (NULL);
	ret[nb_words] = 0;
	if (nb_words != 0)
	{
		if (ft_malloc_strings(s, ret, nb_words, c) == -1)
		{
			free(ret);
			return (NULL);
		}
		ft_cpy_words(s, ret, nb_words, c);
	}
	return (ret);
}
