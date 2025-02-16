/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crud_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estferna <estferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 21:08:28 by estferna          #+#    #+#             */
/*   Updated: 2025/02/15 21:08:28 by estferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_list	*create_list(void) //cria e inicializa uma estrutura de lista vazia
{
	t_list	*list;

	list = (t_list *)ft_calloc(1, sizeof(t_list)); //aloca e zera a memoria da lista
	list->begin = NULL; //inicializa ponteiro do primeiro nó
	list->end = NULL; // inicializa ponteiro do ultimo nó
	list->size = 0; //inicializa contador de tamanho
	return (list); // nova t_list alocada com ponteiros NULL e tamanho 0
}

t_node	*create_node(char *str) // Cria um novo nó contendo string de comando dividida por espaços
{
	t_node	*node; 

	node = malloc(sizeof(t_node)); // Aloca memoria do nó
	node->str = ft_split(str, ' '); // Divide string por espaços
	node->next = NULL; // Inicializa proximo ponteiro
	return (node); // Novo nó alocado com comando dividido e ponteiro next NULL
}

void	push_node(t_list *list, char *str) 
{
	t_node	*node;

	node = create_node(str); // Cria novo nó com comando
	if (list->begin == NULL) // SE lista está vazia
	{
		list->begin = node; // Define nó como primeiro e último
		list->end = node;
	}
	else
	{
		list->end->next = node; // Liga ultimo atual ao novo nó
		list->end = list->end->next; // Atualiza ponteiro end
	}
	list->size++; // Incrementa tamanho da lista
}

void	free_list(t_list **list_ref) // Libera toda memória associada à lista e seus nós
{
	t_list	*list;
	t_node	*node;
	t_node	*aux;

	list = *list_ref; //Obtém ponteira da lista
	node = list->begin; // Começa no primeiro nó
	aux = NULL; // Inicializa ponteiro auxiliar
	while (node != NULL) // Enquanto houver nós
	{
		aux = node; // Salva nó atual
		node = node->next; // Move para proximo nó
		minifree(aux->str); // Libera strings do comando
		free(aux); // Libera estrutura do nó
	}
	free(list); // Libera estrutura da lista
	*list_ref = NULL; // Define ponteiro original como NULL
}
