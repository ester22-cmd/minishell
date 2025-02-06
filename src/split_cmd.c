#include "../include/minishell.h"
// Função que verifica se uma string contém algo além de espaços
int	is_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{ // Se encontrar qualquer caractere diferente de espaço
		if (str[i] != ' ')
			return (1);
		i++;
	}
	return (0);
}
// Função auxiliar que lida com o final do input ou casos especiais
int	dirty_job_handler(t_mini *mini, t_list *list, char *str, int start)
{// Verifica se chegou ao final do input e não há aspas abertas
	if (mini->input_sanitized[mini->i + 1] == '\0' && mini->is_open_s == 0
		&& mini->is_open_d == 0)
	{
		str = ft_substr(mini->input_sanitized, start, mini->i - start + 1);
		// Se a string só tem espaços
		if (!is_space(str))
		{
			free(str);
			return (0);
		}
		push_node(list, str);
		free(str);
	}
	return (1);
}

void	dirty_job(t_mini *m, t_list *list, int start)
{
	char	*str;

	while (m->input_sanitized[m->i])
	{// Verifica aspas
       // Se encontrar pipe e não estiver entre aspas
		is_in_quote(m->input_sanitized[m->i], m);
		if (m->input_sanitized[m->i] == '|' && m->is_open_s == 0
			&& m->is_open_d == 0)
		{
			str = ft_substr(m->input_sanitized, start, (m->i - 1) - start);
			m->i++;
			start = m->i;
			// Se só tem espaços
			if (!is_space(str))
			{
				m->pipe--;
				free(str);
				return ;
			}
			push_node(list, str);
			free(str);
			m->pipe++;
		}// Processa final do input ou casos especiais
		if (dirty_job_handler(m, list, str, start) == 0)
			return ;
		m->i++;
	}
}

int	split_cmd(t_mini *mini, t_list *list)
{
	int		start;

	mini->i = 0;
	start = mini->i;
	dirty_job(mini, list, start);
	// Processa o input
   // Verifica se todas as aspas foram fechadas
	if (mini->is_open_s == 1 || mini->is_open_d == 1)
		return (0);
	return (1);
}