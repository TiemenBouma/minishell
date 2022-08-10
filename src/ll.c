#include "../includes/minishell.h"

char **e(char **ss)
{
	return (ss);
}


int main()
{

	struct s_main main_struct;
	struct s_node env;
	struct s_node env2;
	char **y;

	env.str = malloc(2);
	env2.str = malloc(2);
	env.str[0] = 'Y';
	env.str[1] = '\n';
	env2.str[0] = 'E';
	env2.str[1] = '\n';
	// main_struct.env_llist = &(struct s_node *)e((char**)env2);
	main_struct.env_llist = &env;
	printf ("str1:|%s|", main_struct.env_llist->str);
	
	*y =  &env2;
	// main_struct.env_llist = &(struct s_node *)e((char**)env2);
	// main_struct.env_llist = &env2;

	main_struct.env_llist = (struct s_node *) e(y)[0];
	printf ("str2:|%s|", main_struct.env_llist->str);



	return (0);
}