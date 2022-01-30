/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsanchez <dsanchez@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 16:14:18 by dsanchez          #+#    #+#             */
/*   Updated: 2022/01/26 21:06:41 by mclerico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <readline/readline.h>

extern char	**environ;

char	*ft_get_path(char *arg)
{
	char	*env;
	char	**path;
	char	*command;

	if (access(arg, F_OK) == 0)
		return (arg);
	env = getenv("PATH");
	if (!env)
		return ("");
	path = ft_split(env, ':');
	while (*path)
	{
		command = ft_strjoin(*path, ft_strjoin("/", arg));
		if (access(command, F_OK) == 0)
			return (command);
		path++;
	}
	return ("");
}

int	ft_execute(char **tokens)
{
	int			pid;

	pid = fork();
	if (pid == 0)
	{
		execve(ft_get_path(tokens[0]), tokens, environ);
		perror(tokens[0]);
		exit(0);
	}
	else if (pid < 0)
	{
		perror("minish");
		return (0);
	}
	else
	{
		waitpid(pid, NULL, 0);
		return (1);
	}
}

void	ft_print_tokens(char **tokens)
{
	if (!tokens)
		return ;
	printf("------------------- TOKENS -------------------\n");
	while (*tokens)
	{
		printf("%s\n", *tokens);
		tokens++;
	}
	printf("------------------- TOKENS -------------------\n");
}

void	ft_print_tokens_list(t_list **tokens)
{
	t_list	**pointer;

	if (!tokens)
		return ;
	pointer = malloc(sizeof(void *));
	if (!pointer)
		return ;
	*pointer = *tokens;
	printf("------------------- TOKENS -------------------\n");
	while (*pointer)
	{
		printf("data: %s , type: %d\n", ((t_token *)((*pointer)->content))->data, ((t_token *)((*pointer)->content))->type);
		*pointer = (*pointer)->next;
	}
	printf("------------------- TOKENS -------------------\n");
	free(pointer);
}

void	ft_free_token(void *t)
{
	t_token	*token;

	token = (t_token *)t;
	free(token->data);
	free(token);
}

int	main(void)
{
	t_list		**tokens;
	//t_ast		**tree;
	t_pstatus	status;
	int			state;

	state = 1;
	while (state)
	{
		status.data = readline("$ ");
		if (status.data != NULL)
			add_history(status.data);
		status.curr = 0;
		status.error = 0;
		tokens = ft_get_tokens(&status);
		ft_print_tokens_list(tokens);
		ft_lstclear(tokens, ft_free_token);
		free(tokens);
	/*if (tokens)
		{
			tree = ft_generate_ast(tokens);
			if (*tree)
				printf("HEAD : %s\n", (*tree)->data);
			else
				printf("NULL\n");
		}*/
	}
	return (0);
}
