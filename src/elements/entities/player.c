/*
** EPITECH PROJECT, 2021
** my_rpg
** File description:
** player
*/

#include <math.h>
#include "my_rpg.h"
#include "elements/entities/player.h"
#include "scene/world_scene.h"
#include "graphics/texture.h"

static void player_init(player_t *player)
{
    player->hitbox = (sfIntRect) {0, 0, 48, 48};
    player->update = &player_update;
    player->health = 6;
    player->max_health = 6;
    player->speed = 3;
    player->can_move = 1;
    player->anim = 0;
    player->dir = NORTH;
    player->damage_time = 0;
    player->stamina = 100;
    player->attack_cooldown = 0;
    player->mov_target = (sfVector2f) {-1, -1};
}

player_t *player_create(infos_t *infos)
{
    element_t *element = element_create_default(sizeof(player_t),
    PLAYER, (sfVector2f) {0, 0});
    player_t *player = (player_t*) element;
    sfSprite *sprite = sfSprite_create();

    if (!player || !sprite)
        return (NULL);
    sfSprite_setTexture(sprite, get_texture(infos, PLAYER_TEXT), 0);
    sfSprite_setTextureRect(sprite, (sfIntRect) {0, 0, 64, 64});
    player->sprite = sprite;
    sprite_set_origin_center(sprite);
    player_init(player);
    return (player);
}

void player_update(entity_t *entity, infos_t *infos, float elapsed)
{
    player_t *player = (player_t*) entity;
    world_scene_t *world_scene = (world_scene_t*) infos->scene;

    if (player->damage_time > 0) {
        player->damage_time -= elapsed;
        if (player->damage_time <= 0)
            sfSprite_setColor(player->sprite, (sfColor) {255, 255, 255, 255});
    }
    if (player->attack_cooldown > 0) {
        player->attack_cooldown -= elapsed;
        if (player->attack_cooldown <= 0)
            player->can_move = 1;
        else
            player->can_move = 0;
    }
    player_stamina(player, infos);
    player_move_update(player, world_scene->map, infos, elapsed);
    element_behind_wall((element_t*) player, world_scene->map);
    living_walk_sprite_anim(player->sprite, player->dir, player->anim);
}
