#include "../cub.h"

// static int	check_letter(t_data *obj, int row)
// {
// 	int length;
// 	int	index;

// 	index = 0;
// 	length = ft_strlen(obj->parser.content[row]);
// 	while (index < length)
// 	{
// 		if (obj->parser.content[row][index] == 32)
// 			index++;
// 		else if (obj->parser.content[row][index] == 'F' || obj->parser.content[row][index] == 'C'
// 		&& obj->parser.content[row][index + 1] == 32)
// 			break ;
// 		index++;
// 	}
// 	return (index);
// }

// static int	check_number(t_data *obj, int index)
// {
// 	int	length;

// 	length = ft_strlen(obj->parser.content[4]);
// 	while (index < length)
// 	{
// 		if (obj->parser.content[4][index] == 32)
// 			index++;
// 		else if (ft_isdigit(obj->parser.content[4][index]))
// 			break ;
// 		index++;
// 	}
// 	return (index);
// }

// static void	get_color(t_data *obj, int index, int comma, int row)
// {
// 	char	*color;
// 	int	length;
// 	int	j;

// 	j = 0;
// 	length = ft_strlen(obj->parser.content[4]);
// 	while (index < length)
// 	{
// 		if (ft_isdigit(obj->parser.content[4][index]))
// 			j++;
// 		else if (obj->parser.content[4][index] == ',')
// 		{
// 			color = malloc(sizeof(char) * j);
// 			if (!color)
// 				return;
// 			ft_strlcpy(color, &obj->parser.content[4][i - j], (j + 1));
// 			obj->cred = ft_atoi(color);
// 			free(color);
// 			exit(0);
// 		}
// 	}
	
// }

satatic void	check_chars(t_data *obj)
{
	int length;
	int	row;
	int	i;

	row = 4;
	i = 0;
	while (row < 6)
	{
		length = ft_strlen(obj->parser.content[row]);
		while (i < length)
		{
			if (obj->parser.content[row][i] == 32 || ft_isdigit(obj->parser.content[row][i]) || )
				i++;
		}
		
	}
	
}

void	check_rgb(t_data *obj)
{
	int	comma;
	int	i;
	int	j;

	i = 0;
	j = 4;
	comma = 3;
	i = check_letter(obj);
	i = check_number(obj, i);
	i--;
	while (j < 6)
	{
		while()
		{
			
		}
	}
	
}