/*
** EPITECH PROJECT, 2021
** my_rpg
** File description:
** world
*/

#include <math.h>
#include <SFML/Window/Keyboard.h>
#include "my_rpg.h"
#include "scene/world_scene.h"
#include "graphics/texture.h"

void world_load(world_scene_t *world_scene, infos_t *infos)
{
    sfTexture *texture = get_texture(infos, WORLD_BACKGROUND_TEXT);

    world_scene->world_size = sfTexture_getSize(texture);
    world_scene->player->move((element_t*) world_scene->player, (sfVector2f)
    {world_scene->world_size.x / 2, world_scene->world_size.y / 2});
    sfSprite_setTexture(world_scene->background, texture, 0);
}

void world_move(world_scene_t *world_scene, infos_t *infos, float elapsed)
{
    const sfView *view = sfRenderWindow_getView(infos->window);
    sfVector2f player_pos = world_scene->player->pos;
    sfVector2f center = sfView_getCenter(view);
    float dist = get_distance(center, player_pos);
    float angle = atan2(player_pos.y - center.y, player_pos.x - center.x);
    sfVector2f move;
    subwindow_t *subwindow;

    if (dist < 0.01)
        return;
    move = (sfVector2f) {cos(angle) * dist / 10, sin(angle) * dist / 10};
    world_move_camera_limit(&move, view, world_scene);
    sfView_move(view, move);
    for (list_t *list = world_scene->subwindows; list; list = list->next) {
        subwindow = (subwindow_t*) list->data;
        subwindow->move(subwindow, (sfVector2f)
        {subwindow->pos.x + move.x, subwindow->pos.y + move.y});
    }
    sfRenderWindow_setView(infos->window, view);
}

void world_move_camera_limit(sfVector2f *move, const sfView *view,
world_scene_t *world_scene)
{
    sfVector2u size = world_scene->world_size;
    sfVector2f pos = sfView_getCenter(view);

    if (pos.x - WINDOW_WIDTH / 2 + move->x < 0)
        move->x = -pos.x + WINDOW_WIDTH / 2;
    else if (pos.x + WINDOW_WIDTH / 2 + move->x > size.x)
        move->x = size.x - pos.x - WINDOW_WIDTH / 2;
    if (pos.y - WINDOW_HEIGHT / 2 + move->y < 0)
        move->y = -pos.y + WINDOW_HEIGHT / 2;
    else if (pos.y + WINDOW_HEIGHT / 2 + move->y > size.y)
        move->y = size.y - pos.y - WINDOW_HEIGHT / 2;
}