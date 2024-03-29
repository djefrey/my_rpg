/*
** EPITECH PROJECT, 2021
** my_rpg
** File description:
** map
*/

#include <stdlib.h>
#include <math.h>
#include "my_rpg.h"
#include "map.h"
#include "rpgsh/rpgsh.h"
#include "scene/world_scene.h"

map_t *map_create(char *path)
{
    map_t *map = malloc(sizeof(map_t));
    char *bkgd_path = my_strmerge(path, "background.png");
    char *mask_path = my_strmerge(path, "mask.png");
    char *script_path = my_strmerge(path, "script.rpgsh");
    char *text_path = my_strmerge(path, "text.txt");

    if (!map || !bkgd_path || !mask_path || !script_path || !text_path)
        return (NULL);
    map->map_texture = sfTexture_createFromFile(bkgd_path, NULL);
    map->mask_img = sfImage_createFromFile(mask_path);
    map->script = open_rpgsh_file(script_path);
    map->text = load_text(text_path);
    if (!map->map_texture || !map->mask_img || !map->script || !map->text)
        return (NULL);
    map->map_size = sfTexture_getSize(map->map_texture);
    free(bkgd_path);
    free(mask_path);
    free(script_path);
    free(text_path);
    return (map);
}

sfColor map_check_mask(map_t *map, sfIntRect hb, unsigned char r_value)
{
    sfImage *mask = map->mask_img;
    sfColor color;

    for (int y = hb.top; y < hb.top + hb.height; y++) {
        for (int x = hb.left; x < hb.left + hb.width; x++) {
            if (x < 0 || x >= (int) map->map_size.x ||
            y < 0 || y >= (int) map->map_size.y)
                continue;
            color = sfImage_getPixel(mask, x, y);
            if (color.r == r_value)
                return (color);
        }
    }
    return (sfBlack);
}

void map_destroy(map_t *map, world_scene_t *world_scene)
{
    element_t *element;

    for (list_t *list = world_scene->entities; list; list = list->next) {
        element = (element_t*) list->data;
        if (element->type == INTERACTABLE
        || element->type == ENEMY || element->type == PROJECTILE)
            scene_remove_element((scene_t*) world_scene, element, 1);
    }
    for (char **line = map->script; *line; line++)
        free(*line);
    for (char **line = map->text; *line; line++)
        free(*line);
    free(map->script);
    free(map->text);
    sfTexture_destroy(map->map_texture);
    sfImage_destroy(map->mask_img);
    free(map);
}