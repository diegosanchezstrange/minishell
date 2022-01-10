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
	T_COMMAND	= 0,
	T_ARGUMENT	= 1,
}				t_token_type;

typedef struct s_pstatus
{
	char		*data;
	int			curr;
	t_pstates	state;
}				t_pstatus;

typedef struct s_token
{
	char			*token;
	t_token_type	type;
	struct s_token	*next;
}				t_token;

// parser
char	**ft_get_tokens(t_pstatus *status);

#endif
