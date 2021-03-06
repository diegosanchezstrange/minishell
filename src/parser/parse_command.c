/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclerico <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 20:11:23 by mclerico          #+#    #+#             */
/*   Updated: 2022/03/30 20:11:25 by mclerico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_node_type	ft_map_types(t_token_type type)
{
	if (type == T_OUT_REDIR)
		return (T_OUT_NODE);
	else if (type == T_IN_REDIR)
		return (T_IN_NODE);
	else if (type == T_D_OUT_REDIR)
		return (T_DOUBLE_OUT_NODE);
	else if (type == T_D_IN_REDIR)
		return (T_DOUBLE_IN_NODE);
	return (0);
}

t_list	*ft_fill_simple_command(t_list *tokens, t_ast **tree)
{
	t_token	*a;

	if (!*tree)
		return (tokens);
	ft_astadd_right(tree, ft_astnew(T_REDIR_NODE, NULL));
	a = (t_token *)tokens->content;
	while (tokens && a && a->type != T_PIPE)
	{
		if (a->type == T_ARGUMENT && (*tree)->data == NULL)
			(*tree)->data = a->data;
		else if (a->type == T_ARGUMENT && (*tree)->data != NULL)
			ft_astappend_r(&((*tree)->left), ft_astnew(1, a->data));
		else if (a->type == T_D_OUT_REDIR || a->type == T_OUT_REDIR)
			ft_astappend_r(&((*tree)->right),
				ft_astnew(ft_map_types(a->type), a->data));
		else if (a->type == T_D_IN_REDIR || a->type == T_IN_REDIR)
			ft_astappend_l(&((*tree)->right),
				ft_astnew(ft_map_types(a->type), a->data));
		tokens = tokens->next;
		if (tokens)
			a = ((t_token *)tokens->content);
	}
	if (a->type == T_PIPE)
		tokens = tokens->next;
	return (tokens);
}
