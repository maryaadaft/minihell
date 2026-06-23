/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walneama <walneama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 17:52:47 by walneama          #+#    #+#             */
/*   Updated: 2026/06/23 23:07:50 by walneama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_expand(t_token *tokens, t_shell *shell)
{
	char *new_value;

	while (tokens)
	{
		if (tokens->token_type == Ty_WORD
			|| tokens->token_type == Ty_Double_Q)
		{
			new_value = expand_str(tokens->value, shell);
			if (!new_value)
				return ;
			free(tokens->value);
			tokens->value = new_value;
		}
		tokens = tokens->next;
	}
}

static char *handle_dollar(char *str, int *i, t_shell *shell)
{
	char *key;
	char *piece;

	(*i)++;
	if (str[*i] == '?')  // $?
	{
		(*i)++;
		return (ft_itoa(shell->exit_status));
	}
	if (str[*i] == '$')  //$$ -> PID
	{
		(*i)++;
		return (ft_itoa(getpid()));
	}
	key = get_var(str, i);
	if (!key)
		return (NULL);
	piece = get_env_value(shell, key);
	free(key);
	return (piece);
}

static char *handle_literal(char *str, int *i)
{
	int start;

	start = *i;
	while (str[*i] && ( str[*i] != '$'))
		(*i)++;
	return(ft_substr(str, start, (*i - start)));
}

static int	append_piece(char **final_str, char *piece)
{
	if (!piece)
	{
		free(*final_str);
		return (-1);
	}
	*final_str = ft_strjoin_free(*final_str, piece);
	free(piece);
	if (!*final_str)
		return (-1);
	return (0);
}

char *expand_str(char *str, t_shell *shell)
{
	int		i;
	char	*piece;
	char	*final_str;

	i = 0;
	printf("DEBUG expand_str input: '%s'\n", str); 
	final_str = ft_strdup("");
	if (!final_str)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '$')
			piece = handle_dollar(str, &i, shell);
		else
			piece = handle_literal(str, &i);
		if (append_piece(&final_str, piece) == -1)
			return (NULL);
	}
	printf("DEBUG expand_str output: '%s'\n", final_str); 
	return (final_str);
}

char *get_var(char *str, int *pos)
{
	int start;

	start = *pos;
	while (str[*pos] && (ft_isalnum(str[*pos]) || str[*pos] == '_'))
		(*pos)++;
	printf("DEBUG get_var extracted: '%.*s'\n", *pos - start, str + start);
	return (ft_substr(str, start, (*pos - start)));
}

char    *get_env_value(t_shell *shell, char *key)
{
	t_env *node;

	node = find_env(shell, key);
	if (node && node->value)
		return (ft_strdup(node->value));
	return(ft_strdup(""));
}

char    *ft_strjoin_free(char *s1, char *s2)
{
	char *final_str;

	final_str = ft_strjoin(s1, s2);
	free(s1);
	if (!final_str)
		free(s2);
	return (final_str);
}
