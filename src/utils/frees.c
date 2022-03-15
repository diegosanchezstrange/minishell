/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclerico <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 20:47:30 by mclerico          #+#    #+#             */
/*   Updated: 2022/02/22 20:51:57 by mclerico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_free_tree(t_ast **tree)
{
	if (!tree)
		return ;
	if (!*tree)
		return ;
	if ((*tree)->right)
		ft_free_tree(&((*tree)->right));
	if ((*tree)->left)
		ft_free_tree(&((*tree)->left));
	if ((*tree)->type == T_DOUBLE_IN_NODE)
		free((*tree)->data);
	free(*tree);
}

void	ft_free_token(void *t)
{
	t_token	*token;

	token = (t_token *)t;
	free(token->data);
	free(token);
}

void	ft_free_split(char **s)
{
	char	**str;

	str = s;
	while (*str)
	{
		free(*str);
		str++;
	}
	free(s);
}

void	ft_free_all(t_ast **tree, t_list **tokens)
{
	ft_free_tree(tree);
	free(tree);
	ft_lstclear(tokens, ft_free_token);
	free(tokens);
}
