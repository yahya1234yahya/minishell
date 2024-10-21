/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gcollector.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboughra <mboughra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 15:26:06 by mboughra          #+#    #+#             */
/*   Updated: 2024/08/24 15:26:06 by mboughra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	garb_add(t_garbage **lst, t_garbage *new)
{
	t_garbage	*lastone;

	if (!lst || !new)
		return ;
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	lastone = *lst;
	while (lastone->next)
		lastone = lastone->next;
	lastone->next = new;
	new->next = NULL;
}

static t_garbage	*garb_new(void *addrress)
{
	t_garbage	*newnode;

	newnode = malloc(sizeof(t_garbage));
	if (newnode == NULL)
	{
		perror("malloc");
		return (NULL);
	}
	newnode->adr = addrress;
	newnode->next = NULL;
	return (newnode);
}

static void	free_garb_list(t_garbage **head)
{
	t_garbage	*current;
	t_garbage	*next;

	current = *head;
	while (current != NULL)
	{
		next = current->next;
		if (current->is_free)
		{
			free(current->adr);
			current->adr = NULL;
		}
		current = next;
	}
}

void	*safe_malloc(size_t size, int flag)
{
	static t_garbage	*gooper;
	t_garbage			*node;
	void				*address;

	address = NULL;
	if (flag == 'a')
	{
		address = malloc(size);
		if (!address)
		{
			safe_malloc(0, 'f');
			exit (0);
		}
		if (gooper == NULL)
			gooper = garb_new(address);
		else
		{
			node = garb_new(address);
			garb_add(&gooper, node);
		}
	}
	else if (flag == 'f')
		free_garb_list(&gooper);
	return (address);
}
