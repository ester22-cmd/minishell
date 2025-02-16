/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minipwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estferna <estferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 23:18:23 by estferna          #+#    #+#             */
/*   Updated: 2025/02/15 23:18:23 by estferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	minipwd(void)
{
	char	wd[1024];

	getcwd(wd, sizeof(wd));
	printf("%s\n", wd);
	g_return = 0; 
}