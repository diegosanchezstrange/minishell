#ifndef MINISHELL_H
# define MINISHELL_H

# include <libft.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef enum e_pstates
{
	P_NEUTRAL	= 0,
	P_D_QUOTE	= 1,
	P_S_QUOTE	= 2
}				t_pstates;

typedef enum e_token_type
{
	T_ARGUMENT	= 0,
	T_IN_REDIR	= 1,
	T_OUT_REDIR	= 2,
	T_PIPE		= 3
}				t_token_type;

typedef struct s_token
{
	char			*data;
	t_token_type	type;
}				t_token;

typedef struct s_ast
{
	char			*data;
	t_token_type	type;
	struct s_ast	*left;
	struct s_ast	*right;
}				t_ast;

typedef struct s_pstatus
{
	char		*data;
	int			curr;
	t_pstates	state;
}				t_pstatus;

// parse_env_vars
char	*ft_get_env_var(char *token, int *num);
char	*ft_join_env_var(char *name, char *token, int i, int num);
void	ft_extend_vars(char **token);

// utils
void	ft_skip_spaces(t_pstatus *status);
char	**ft_resize_tokens(int num, char **tokens);

// parser_quotes.c
void	ft_parse_quotes(char **token);

// lexer
t_list	**ft_get_tokens(t_pstatus *status);

// parser.c

#endif
