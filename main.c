#include "rush02.h"

int	is_valid_args(int argc, char **argv)
{
	int	i;

	if (argc < 2 || argc > 3)
		return (0);
	i = 0;
	if (argc == 2)
	{
		while (argv[1][i])
		{
			if (argv[1][i] < '0' || argv[1][i] > '9')
				return (0);
			i++;
		}
	}
	else
	{
		while (argv[2][i])
		{
			if (argv[2][i] < '0' || argv[2][i] > '9')
				return (0);
			i++;
		}
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_dict	*dict;
	char	*n;
	char	*dict_file;

	if (!is_valid_args(argc, argv))
	{
		ft_putstr("Error\n");
		return (0);
	}
	if (argc == 2)
	{
		dict_file = "numbers.dict";
		n = argv[1];
	}
	else
	{
		dict_file = argv[1];
		n = argv[2];
	}
	dict = parse_dict(dict_file);
	if (!dict)
	{
		ft_putstr("Dict Error\n");
		return (0);
	}
	convert_number(n, dict);
	ft_putstr("\n");
	free_dict(dict);
	return (0);
}
