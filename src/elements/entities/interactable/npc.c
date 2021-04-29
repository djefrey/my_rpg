/*
** EPITECH PROJECT, 2021
** my_rpg
** File description:
** NPC
*/

#include <math.h>
#include "my_rpg.h"
#include "elements/entities/npc.h"

npc_t *npc_create(sfVector2f pos, sfTexture *texture, char *action)
{
    npc_t *npc = (npc_t*) interactable_create(sizeof(npc_t), pos, texture);

    if (!npc)
        return (NULL);
    my_strcpy(npc->action_name, action);
    npc->update = &npc_update;
    npc->speed = 2;
    npc->mov_target = (sfVector2f) {-1, -1};
    sprite_set_origin_center(npc->sprite);
    element_set_hitbox((element_t*) npc,
    sfSprite_getGlobalBounds(npc->sprite));
    return (npc);
}

void npc_update(entity_t *entity, infos_t *infos, float elapsed)
{
    npc_t *npc = (npc_t*) entity;

    if (npc->mov_target.x == -1 && npc->mov_target.y == -1)
        interactable_update(entity, infos, elapsed);
    else {
        npc_movement(npc, elapsed);
        living_walk_sprite_anim(npc->sprite, npc->dir, npc->anim);
    }
}

void npc_movement(npc_t *npc, float elapsed)
{
    sfVector2f diff = (sfVector2f) {npc->mov_target.x - npc->pos.x,
     npc->mov_target.y - npc->pos.y};
    sfVector2f move = vector_normalize(diff);
    sfVector2f new_pos;
    float speed = npc->speed * elapsed;

    move.x *= speed;
    move.y *= speed;
    if (fabs(diff.x) <= fabs(move.x) && fabs(diff.y) <= fabs(move.y)) {
        new_pos = npc->mov_target;
        npc->mov_target = (sfVector2f) {-1, -1};
    } else
        new_pos = (sfVector2f) {npc->pos.x + move.x, npc->pos.y + move.y};
    walk_animation_set_anim_and_dir(&(npc->anim), &(npc->dir), move, speed);
    npc->move((element_t*) npc, new_pos);
}