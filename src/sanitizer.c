#include "../include/minishell.h"

void	is_quote(char c, t_sani *s)
{
	if (c == S_QUOTE)
	{
		if (s->s == 0 && s->d == 0)
			s->s = 1;
		else if (s->s == 1)
			s->s = 0;
	}
	if (c == D_QUOTE)
	{
		if (s->d == 0 && s->s == 0)
			s->d = 1;
		
		else if (s->d == 1)
			s->d = 0;
	}
}

void	put_spaces(char *str, int len, t_sani *s, t_mini *m)
{
	m->input_sanitized = malloc(sizeof(char) * len + 1);
	while (str[s->i])
	{
		is_quote(str[s->i], s)

		if (str[s->i] == '|' && !s->s && !s->d)
		{
			m->input_sanitized[s->j++] = ' ';
			m->input_sanitized[s->j++] = str[s->i++];
			m->input_sanitized[s->j++] = ' ';
		}
		if ((str[s->i] == '>' || str[s->i] == '<') && !s->s && !s->d)
		{
			m->input_sanitized[s->j++] = ' ';
			m->input_sanitized[s->j++] = str[s->i++];
			while (str[s->i] == '<' || str[s->i] == '>')
				m->input_sanitized[s->j++] = str[s->i++];
			m->input_sanitized[s->j++] = ' ';
		}
		if ((str[s->i] != '|' && str[s->i] != '>' && str[s->i] != '<')
			|| (s->s == 1 || s->d == 1))
			m->input_sanitized[s->j++] = str[s->i++];
	}
	m->input_sanitized[s->j] = '\0';
}

int	correct_len(char *str, int len, int i, t_sani *s)
{
	while (str[i])
	{
		is_quote(str[i], s);
		
		if (str[i] == '|' && !s->s && !s->d)
			len += 3;
		
		if ((str[i] == '>' || str[i] == '<') && !s->s && !s->d)
		{
			len += 3;
			i++;
		}
		while ((str[i] == '<' || str[i] == '>') && !s->s && !s->d)
		{
			len++;
			i++;
		}
		if ((str[i] != '|' && str[i] != '>' && str[i] != '<')
			|| (s->s == 1 || s->d == 1))
			len++;
		i++;
	}
	return (len);
}

void	input_sanitizer(t_mini *mini, t_sani *sani)
{
	char	*aux;
	int		len;

	sani->s = 0;
	sani->d = 0;
	sani->i = 0;
	sani->j = 0;
	aux = ft_strtrim(mini->input, " ");
	len = correct_len(aux, 0, 0, sani);
	put_spaces(aux, len, sani, mini);
	free(aux);
} 