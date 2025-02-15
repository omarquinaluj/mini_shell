/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owmarqui <owmarqui@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 14:33:22 by owmarqui          #+#    #+#             */
/*   Updated: 2024/09/24 17:53:26 by owmarqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	count_words(char const *s, char charset)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s != charset && in_word == 0)
		{
			in_word = 1;
			count++;
		}
		else if (*s == charset)
			in_word = 0;
		s++;
	}
	return (count);
}

static char	*conserv_world(int start, int end, char const *s)
{
	char	*word;
	int		size;
	int		i;

	i = 0;
	size = end - start;
	word = (char *)malloc(sizeof(char) * (size + 1));
	if (!word)
		return (NULL);
	while (i < size)
	{
		word[i] = s[start + i];
		i++;
	}
	word[size] = '\0';
	return (word);
}

static char	**free_memory(char **result, int pos)
{
	while (pos--)
		free(result[pos]);
	free(result);
	return (NULL);
}

static char	**ft_auxiliar(char const *s, char c, char **result)
{
	int	i;
	int	start;
	int	pos;

	i = 0;
	pos = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			start = i;
			while (s[i] && s[i] != c)
				i++;
			result[pos] = conserv_world(start, i, s);
			if (!result[pos])
				return (free_memory(result, pos));
			pos++;
		}
		else
			i++;
	}
	result[pos] = NULL;
	return (result);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	size_t	size;

	if (!s)
		return (NULL);
	size = count_words(s, c);
	result = (char **)malloc(sizeof(char *) * (size + 1));
	if (!result)
		return (NULL);
	if (!ft_auxiliar(s, c, result))
		return (NULL);
	return (result);
}
/*
#include <stdio.h>

void print_split(char **split) {
    int i = 0;
    while (split[i]) {
        printf("'%s'\n", split[i]);
        i++;
    }
}

int main() {
    char **result = ft_split("Hello,world! This is an example.", "o");
    print_split(result);
    int i = 0;
    while (result[i]) {
        free(result[i]);
        i++;
    }
    free(result);
    return 0;
}*/
