/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaferre <amaferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 23:17:11 by amaferre          #+#    #+#             */
/*   Updated: 2025/02/15 23:17:11 by amaferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_return;

int	main(void)
{
	t_mini	mini;
	t_list	*list;
	t_sani	sani;
	init(&mini, __environ);

	while (1)
	{
		signals(1);
		mini.in = STDIN_FILENO;
		mini.out = STDOUT_FILENO;

		list = create_list();
		get_input(&mini, &sani, list);
		if (ft_strlen(mini.input) != 0 && mini.input[0] != '|')
		{
			if (!input_validate(&mini) || !quotes_closed(&mini))
				printf("error\n");
			else if (split_cmd(&mini, list) && redir_validate(list))
				run(&mini, list, 0);

		}
		free_reset(&mini, list);
		mini.pipe = 0;
	}
	free_em_all(&mini);
	return (0);
}
