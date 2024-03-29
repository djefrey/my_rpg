/*
** EPITECH PROJECT, 2021
** my_rpg
** File description:
** graphicals effects
*/

#include "my_rpg.h"
#include "elements/element.h"
#include "map.h"

void element_behind_wall(element_t *element, map_t *map)
{
    sfColor color_filter = {0, 0, 0, 180};
    sfColor elem_color = sfSprite_getColor(element->sprite);

    if (map_check_mask(map, element->hitbox, BEHIND_WALL_MASK_VALUE).r)
        sfSprite_setColor(element->sprite, color_filter);
    else if (!elem_color.r && !elem_color.g
    && !elem_color.b && elem_color.a == 180)
        sfSprite_setColor(element->sprite, sfWhite);
}