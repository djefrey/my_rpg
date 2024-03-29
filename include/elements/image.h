/*
** EPITECH PROJECT, 2021
** my_rpg
** File description:
** image
*/

#ifndef IMAGE_H_
#define IMAGE_H_

#include "elements/element.h"
#include "graphics/texture.h"

typedef struct image_s {
    element_type_t type;
    sfVector2f pos;
    float rot;
    sfIntRect hitbox;
    sfSprite *sprite;
    move_element_fct_t move;
    rotate_element_fct_t rotate;
    draw_element_fct_t draw;
    on_click_fct_t on_click;
    get_infos_element_fct_t get_infos;
    destroy_element_fct_t destroy;
    sfVector2i size;
    sfVector2i texture_pos;
} image_t;

image_t *image_create(infos_t *infos, texture_t texture,
sfVector2f pos, sfVector2i size);
void image_add_texture_pos(image_t *image, int x, int y);
void image_set_texture_pos(image_t *image, int x, int y);

#endif /* !IMAGE_H_ */
