/*
** EPITECH PROJECT, 2021
** my_rpg
** File description:
** textures
*/

#ifndef TEXTURE_H_
#define TEXTURE_H_

#include "my_list.h"
#include <SFML/Graphics/Texture.h>

typedef struct infos_s infos_t;

typedef enum texture_e {
    BUTTONS_TEXT,
    MENU_BACKGROUND_TEXT,
    SETTINGS_BACKGROUND_TEXT,
    HOWTOPLAY_BACKGROUND_TEXT,
    PAUSE_BACKGROUND_TEXT,
    SETTINGS_SUBWINDOW_TEXT,
    HOWTOPLAY_IMG_TEXT,
    INVENTORY_TEXT,
    PLAYER_TEXT,
    INV_SLOT_TEXT,
    ITEMS_TEXT
} texture_t;

list_t *load_textures(void);
sfTexture *get_texture(infos_t *infos, texture_t id);
void destroy_textures(list_t *textures);

#endif /* !TEXTURE_H_ */
