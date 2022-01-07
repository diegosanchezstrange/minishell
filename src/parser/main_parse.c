
#include <minishell.h>

char	*ft_get_token(t_pstatus *state);

int	main()
{
	t_pstatus	state;

	state.data = "echo \" hola mundo \"";
	state.curr = 0;
	printf("token : --%s--\n", ft_get_token(&state));
	printf("token : --%s--\n", ft_get_token(&state));
	printf("token : --%s--\n", ft_get_token(&state));
	printf("token : --%s--\n", ft_get_token(&state));
	return (0);
}
