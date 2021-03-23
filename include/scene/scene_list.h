/*
** EPITECH PROJECT, 2021
** my_rpg
** File description:
** scene list
*/

#ifndef SCENE_LIST_H_
#define SCENE_LIST_H_

#include "my_rpg.h"
#include "scene/menu_scene.h"
#include "scene/settings_scene.h"
#include "scene/howtoplay_scene.h"

typedef scene_t *(*scene_create_fct_t)(infos_t* infos);

#define NB_SCENES 3

const int LOAD_ACTION[] = {
    LOAD_MENU_SCENE_ACTION,
    LOAD_SETTINGS_SCENE_ACTION,
    LOAD_HOWTOPLAY_SCENE_ACTION,
};

const game_state_t SCENE_STATE[] = {
    MAIN_MENU,
    SETTINGS,
    HOWTOPLAY,
};

const scene_create_fct_t LOAD_SCENE_FCT[] = {
    &menu_scene_create,
    &settings_scene_create,
    &howtoplay_scene_create,
};

#endif /* !SCENE_LIST_H_ */
