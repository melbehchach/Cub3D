#include "../cub.h"

static char	check_fc(char *row)
{
	char	letter;
	int		i;

	i = 0;
	letter = '\0';
	while (row[i] == 32)
		i++;
	if (row[i] == 'F')
		letter = 'F';
	else if (row[i] == 'C')
		letter = 'C';
	return (letter);
}

static int	assigne_floo_rgb(t_data *obj, char *row, int *size, char rgb)
{
	char	*color;

	color = malloc(sizeof(char) * (*size));
	if (!color)
		return (0);
	ft_strlcpy(color, row, *size + 1);
	if (rgb == 'r')
		obj->fred = ft_atoi(color);
	else if (rgb == 'g')
		obj->fgreen = ft_atoi(color);
	else if (rgb == 'b')
		obj->fbleu = ft_atoi(color);
	free(color);
	*size = 0;
	return (1);
}

static void	get_floor_info(t_data *obj, char *row)
{
	int	length;
	int	comma;
	int	i;
	int	j;

	i = -1;
	j = 0;
	comma = 0;
	length = ft_strlen(row);
	while (++i < (length + 1))
	{
		if (ft_isdigit(row[i]) && row[i] != ',')
			j++;
		if (row[i] == ',' && comma == 0)
			comma += assigne_floo_rgb(obj, &row[i - j], &j, 'r');
		else if (row[i] == ',' && comma == 1)
			comma += assigne_floo_rgb(obj, &row[i - j], &j, 'g');
		else if (!row[i] && comma == 2)
			assigne_floo_rgb(obj, &row[i - j], &j, 'b');
	}
}

static int	assigne_ceiling_rgb(t_data *obj, char *row, int *size, char rgb)
{
	char	*color;

	color = malloc(sizeof(char) * (*size));
	if (!color)
		return (0);
	ft_strlcpy(color, row, *size + 1);
	if (rgb == 'r')
		obj->cred = ft_atoi(color);
	else if (rgb == 'g')
		obj->cgreen = ft_atoi(color);
	else if (rgb == 'b')
		obj->cbleu = ft_atoi(color);
	free(color);
	*size = 0;
	return (1);
}

static void	get_ceiling_info(t_data *obj, char *row)
{
	int	length;
	int	comma;
	int	i;
	int	j;

	i = -1;
	j = 0;
	comma = 0;
	length = ft_strlen(row);
	while (++i < (length + 1))
	{
		if (ft_isdigit(row[i]) && row[i] != ',')
			j++;
		if (row[i] == ',' && comma == 0)
			comma += assigne_ceiling_rgb(obj, &row[i - j], &j, 'r');
		else if (row[i] == ',' && comma == 1)
			comma += assigne_ceiling_rgb(obj, &row[i - j], &j, 'g');
		else if (!row[i] && comma == 2)
			assigne_ceiling_rgb(obj, &row[i - j], &j, 'b');
	}
}

static int	rgb_range(int color)
{
	if (color < 0 || color > 255)
		return (0);
	return (1);
}

int	check_rgb(t_data *obj)
{
	int	i;

	i = -1;
	while (++i < 6)
	{
		if (check_fc(obj->parser.content[i]) == 'F')
			get_floor_info(obj, obj->parser.content[i]);
		else if (check_fc(obj->parser.content[i]) == 'C')
			get_ceiling_info(obj, obj->parser.content[i]);
	}
	if (!rgb_range(obj->fred))
		return (7);
	if (!rgb_range(obj->fgreen))
		return (7);
	if (!rgb_range(obj->fbleu))
		return (7);
	if (!rgb_range(obj->cred))
		return (7);
	if (!rgb_range(obj->cgreen))
		return (7);
	if (!rgb_range(obj->cbleu))
		return (7);
	return (1);
}