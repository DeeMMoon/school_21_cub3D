/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gantedil <gantedil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 18:58:52 by gantedil          #+#    #+#             */
/*   Updated: 2022/09/12 19:34:58 by gantedil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub.h"

void	set_start_pos(t_data *data, char c, int i, int j)
{
	data->map->new_map[i][j] = '0';
	data->orientation = c;
	data->posX = j;
	data->posY = i;
}

void	get_start_pos(t_data *data)
{
	int	i;
	int	j;
	int	flag;

	i = 0;
	flag = 0;
	while (i <= data->map->height - 1)
	{
		j = 0;
		while (data->map->new_map[i][j])
		{
			if (data->map->new_map[i][j] == 'N' || data->map->new_map[i][j] == 'S' \
				|| data->map->new_map[i][j] == 'W' || data->map->new_map[i][j] == 'E')
			{
				if (flag == 1)
					ft_error("Use more one person");
				set_start_pos(data, data->map->new_map[i][j], i, j);
				flag = 1;
			}
			j++;
		}
		i++;
	}	
}

void	steps(t_data *data)
{
	if (data->rayDirX < 0)
    {
    	data->stepX = -1;
    	data->sideDistX = (data->posX - data->mapX) * data->deltaDistX;
	}
    else
    {
    	data->stepX = 1;
    	data->sideDistX = (data->mapX + 1.0 - data->posX) * data->deltaDistX;
    }
    if (data->rayDirY < 0)
    {
    	data->stepY = -1;
    	data->sideDistY = (data->posY - data->mapY) * data->deltaDistY;
    }
    else
    {
    	data->stepY = 1;
    	data->sideDistY = (data->mapY + 1.0 - data->posY) * data->deltaDistY;
    }
}

void	my_mlx_pixel_put(t_data *data, int x, int y, unsigned int color)
{
	char	*dst;

	dst = data->img->addr + (y * data->img->line_length + x * (data->img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	draw_line(t_data *data, int start, int end, int x)
{
	int		y;
	//int		ty;
	//int		color;

	y = 0;
	while (y < HEIGHT)
	{
		if (y < start)
			my_mlx_pixel_put(data, x, y, data->map->ceiling_color);
		else if (y > end)
			my_mlx_pixel_put(data, x, y, data->map->floor_color);
		else
		{
			//ty = (y - start) * 128 / (line_height);
			my_mlx_pixel_put(data, x, y, 123244);
		}
		y++;
	} 
}

void	draw_lines(t_data *data, int x)
{
	int	lineHeight;
	int	drawStart;
	int	drawEnd;

	lineHeight = (int)(HEIGHT / data->perpWallDist);
	drawStart = - lineHeight / 2 + HEIGHT / 2;
	if (drawStart < 0)
		drawStart = 0;
	drawEnd = lineHeight / 2 + HEIGHT / 2;
	if (drawEnd >= HEIGHT)
		drawEnd = HEIGHT - 1;
	draw_line(data, drawStart, drawEnd, x);
}

void	dda(t_data *data, int x)
{
	while(data->hit == 0)
	{
		if (data->sideDistX < data->sideDistY)
		{
			data->sideDistX += data->deltaDistX;
			data->mapX += data->stepX;
			data->side = 0;
		}
		else
		{
			data->sideDistY += data->deltaDistY;
			data->mapY += data->stepY;
			data->side = 1;			
		}
		if (data->num_map[data->mapY][data->mapX] > 0)
			data->hit = 1;
	}
	if (data->side == 0) 
		data->perpWallDist = (data->sideDistX - data->deltaDistX);
    else
		data->perpWallDist = (data->sideDistY - data->deltaDistY);
	draw_lines(data, x);
}

void	draw_image(t_data *data)
{
	int	x;

	x = 0;
	while (x < WIDTH)
	{
		data->cameraX = 2 * x / (double)WIDTH - 1;
		data->rayDirX = data->dirX + data->planeX * data->cameraX;
		data->rayDirY = data->dirY + data->planeY * data->cameraX;
		data->mapX = (int) data->posX;
		data->mapY = (int) data->posY;
		if (data->rayDirX == 0)
			data->deltaDistX = HUGE_VAL;
		else
			data->deltaDistX = fabs(1 / data->rayDirX);
		if (data->rayDirY == 0)
			data->deltaDistY = HUGE_VAL;
		else
			data->deltaDistY = fabs(1 / data->rayDirY);
		data->hit = 0;
		steps(data);
		dda(data, x);
		x++;
	}
}