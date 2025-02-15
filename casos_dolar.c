/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casos_dolar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owmarqui <owmarqui@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 18:42:54 by owmarqui          #+#    #+#             */
/*   Updated: 2025/02/15 18:43:06 by owmarqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

static char	*replace_env_var2(char *token, int key_len, t_env *head, int i)
{
	char	*before;
	char	*after;
	char	*temp;

	// printf("---------1---------%s\n", token);
	before = ft_substr(token, 0, i);
	after = ft_strdup(token + i + key_len);
	temp = token;
	if (head)
	{
		token = ft_strjoin(before, head->value);
		free(before);
	}
	else
		token = before;
	free(temp);
	temp = token;
	token = ft_strjoin(token, after);
	free(temp);
	free(after);
	// printf("---------2---------%s\n", token);
	return (token);
}

static char	*replace_env_var_ext(char *token, int i,
	t_env *envs, bool *split_token)
{
	char	*key;
	size_t	key_len;
	size_t	y;

	// printf("---------3---------%s\n", token);
	y = 0;
	key_len = 1;
	while (token[i + key_len] && !special_char(token[i + key_len]))
		key_len++;
	if ((token[i + 1] >= '0' && token[i + 1] <= '9')
		|| token[i + 1] == '"' || token[i + 1] == '\'')
		key_len = 2;
	key = ft_substr(token, i + 1, key_len - 1);
	token = replace_env_var2(token, key_len, get_env(envs, key), i);
	free(key);
	while (token[y] && !isspace(token[y]))
		y++;
	if (token[y] && isspace(token[y]))
	{
		while (token[++y])
			if (!isspace(token[y]))
				*split_token = true;
	}
	// printf("---------4---------%s\n", token);
	return (token);
}

static int	replace_env_var_ext2(char **token, size_t *i,
	t_env *envs, bool *split_token)
{
	if ((*token)[(*i)] == '$' && (*token)[(*i) + 1]
		&& ((*token)[(*i) + 1] == '?'))
		(*token) = replace_env_var2((*token), 2, get_env(envs, "?"), *i);
	else if ((*token)[(*i)] == '$' && isinquote(*token, i)
				&& (*token)[(*i) + 1] && ((*token)[(*i) + 1] == '"'
				|| (*token)[(*i) + 1] == '\''))
	{
		(*i)++;
		return (0);
	}
	else if ((*token)[(*i) + 1] && (!special_char((*token)[(*i) + 1])
			|| (*token)[(*i) + 1] == '"' || (*token)[(*i) + 1] == '\''))
		(*token) = replace_env_var_ext((*token), (*i), envs, split_token);
	else
	{
		(*i)++;
		return (0);
	}
	(*i) = 0;
	return (1);
}

char	*ft_replace_env_var(t_env *envs, char *token, \
	bool *split_token, char *tokenpre)
{
	size_t	i;
	char	quote;

	i = 0;
	quote = 0;
	while (token && token[i])
	{
		if (!quote && (token[i] == '\'' || token[i] == '"'))
			quote = token[i++];
		else if (token[i] == quote)
		{
			quote = 0;
		}
		else if (tokenpre && !ft_strcmp(tokenpre, "<<"))
			break ;
		else if (token[i] == '$' && quote != '\'')
		{
			if (!replace_env_var_ext2(&token, &i, envs, split_token))
				continue ;
		}
		else
			i++;
	}
	return (token);
}
