#include "headers/libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*p;
	t_list	*tmp;

	p = *lst;
	if (lst)
	{
		if (p)
		{
			while (p)
			{
				tmp = p->next;
				if (del)
					del (p->content);
				free(p);
				p = tmp;
			}
			*lst = 0;
		}
	}
}
