/*
** EPITECH PROJECT, 2020
** my_runner
** File description:
** textures
*/

#include <stdlib.h>
#include <unistd.h>
#include "my_rpg.h"
#include "graphics/texture.h"
#include "graphics/texture_list.h"

static int load_texture(list_t **textures, const char *path)
{
    sfTexture *texture = sfTexture_createFromFile(path, NULL);

    if (texture == NULL)
        return (1);
    create_list(textures, texture);
    return (0);
}

list_t *load_textures(void)
{
    list_t *list = NULL;
    char destroy = 0;

    for (int i = 0; i < TEXTURES_NB && !destroy; i++) {
        if (load_texture(&list, TEXTURES_PATH[TEXTURES_NB - i - 1]))
            destroy = 1;
    }
    if (destroy) {
        write(2, "Textures failed to load\n", 24);
        destroy_textures(list);
        return (NULL);
    } else
        return (list);
}

sfTexture *get_texture(infos_t *infos, texture_t id)
{
    list_t *list = infos->textures;

    for (int i = 0; i < (int) id; i++, list = list->next);
    return ((sfTexture*) list->data);
}

void destroy_textures(list_t *textures)
{
    list_t *tmp;

    while (textures) {
        tmp = textures->next;
        if (textures->data)
            sfTexture_destroy((sfTexture*) textures->data);
        free(textures);
        textures = tmp;
    }
}