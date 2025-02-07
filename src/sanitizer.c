#include "../include/minishell.h"
// Função que verifica e gerencia o estado das aspas (simples e duplas)
void	is_quote(char c, t_sani *s)
{// Se encontrar aspas simples (S_QUOTE)
	if (c == S_QUOTE)
	{ // Se não houver nenhuma aspas aberta (s->s e s->d são 0)
		if (s->s == 0 && s->d == 0)
			s->s = 1;
		// Se já havia uma aspas simples aberta, fecha ela
		else if (s->s == 1)
			s->s = 0;// Fecha as aspas simples
	}// Se encontrar aspas duplas (D_QUOTE)
	if (c == D_QUOTE) // Se encontrar aspas duplas (")
	{// Se não houver nenhuma aspas aberta
		if (s->d == 0 && s->s == 0)
			s->d = 1;// Marca aspas duplas como aberta
		// Se já havia uma aspas dupla aberta, fecha ela
		else if (s->d == 1)
			s->d = 0;// Fecha as aspas duplas
	}
}

void	put_spaces(char *str, int len, t_sani *s, t_mini *m)
{
	m->input_sanitized = malloc(sizeof(char) * len + 1);
	while (str[s->i])
	{
		is_quote(str[s->i], s);
		// Se encontrar pipe (|) fora de aspas
		if (str[s->i] == '|' && !s->s && !s->d)
		{
			m->input_sanitized[s->j++] = ' ';// Adiciona espaço antes
			m->input_sanitized[s->j++] = str[s->i++];// Copia o pipe
			m->input_sanitized[s->j++] = ' ';// Adiciona espaço depois
		}// Se encontrar redirecionamentos (> ou <) fora de aspas
		if ((str[s->i] == '>' || str[s->i] == '<') && !s->s && !s->d)
		{
			m->input_sanitized[s->j++] = ' ';// Adiciona espaço antes
			m->input_sanitized[s->j++] = str[s->i++];// Copia o primeiro caractere
			while (str[s->i] == '<' || str[s->i] == '>')
				m->input_sanitized[s->j++] = str[s->i++];
			m->input_sanitized[s->j++] = ' ';
		}// Se não for operador especial ou estiver entre aspas, copia o caractere normalmente
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
		// Adiciona 3 ao comprimento para cada pipe (para os espaços extras)
		if (str[i] == '|' && !s->s && !s->d)
			len += 3;
		// Adiciona espaço para redirecionamentos
		if ((str[i] == '>' || str[i] == '<') && !s->s && !s->d)
		{
			len += 3;
			i++;
		}// Conta redirecionamentos consecutivos
		while ((str[i] == '<' || str[i] == '>') && !s->s && !s->d)
		{
			len++;
			i++;
		}// Incrementa para caracteres normais ou entre aspas
		if ((str[i] != '|' && str[i] != '>' && str[i] != '<')
			|| (s->s == 1 || s->d == 1))
			len++;
		i++;
	}
	return (len);
}
// Função principal que sanitiza a entrada
void	input_sanitizer(t_mini *mini, t_sani *sani)
{
	char	*aux;
	int		len;
// Inicializa as variáveis de controle
	sani->s = 0;// Estado das aspas simples
	sani->d = 0;// Estado das aspas duplas
	sani->i = 0;// Índice de leitura
	sani->j = 0;// Índice de escrita
	aux = ft_strtrim(mini->input, " ");// Remove espaços extras das extremidades
	len = correct_len(aux, 0, 0, sani);// Calcula o tamanho necessário
	put_spaces(aux, len, sani, mini);// Adiciona os espaços necessários
	free(aux);// Libera a memória temporária
} 