/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorenzo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 18:19:53 by lorenzo           #+#    #+#             */
/*   Updated: 2024/09/09 14:52:58 by lonulli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <string.h>

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!del || !lst)
		return ;
	if (lst)
	{
		(*del)(lst->content);
		free(lst);
	}
}
/*void free_node(void *data)
{
	free(data);
}

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}

int	main(void)
{
	char *str = (char *)malloc(sizeof(char ) *7);
	strcpy(str,"Test42");
	t_list *new = ft_lstnew(str);
	new->next = ft_lstnew("sium");
	new->next->next = ft_lstnew("daje");
	t_list *new2 = new->next;
	while(new)
	{
		if(new->next)
			printf("%s->", (char *)new->content);
		else
			printf("%s", (char *)new->content);
		new = new->next;
	}
	printf("\n");
	ft_lstdelone(new, free_node);
	while(new2)
	{
		if(new2->next)
			printf("%s->", (char *)new2->content);
		else
			printf("%s", (char *)new2->content);
		new2 = new2->next;
	}
	printf("\n");
}*/
