##
## EPITECH PROJECT, 2020
## my_rpg
## File description:
## Makefile
##

MAIN_SRC		=	src/main.c													\
					src/my_rpg.c												\
					src/events.c												\
					src/infos.c													\
					src/graphics/textures.c										\
					src/graphics/subwindow.c									\
					src/graphics/default_subwindow_fcts.c						\
					src/graphics/pause.c										\
					src/graphics/pause_fcts.c									\
					src/graphics/effects.c										\
					src/audio/sounds.c											\
					src/audio/music.c											\
					src/audio/utils.c

ELEMENTS_SRC	=	src/elements/element.c										\
					src/elements/default_element_fcts.c							\
					src/elements/bar.c											\
					src/elements/bar_fcts.c										\
					src/elements/health_bar.c									\
					src/elements/image.c										\
					src/elements/entities/buffer.c								\
					src/elements/entities/enemy.c								\
					src/elements/entities/enemy_patterns.c						\
					src/elements/entities/enemy_attacks.c						\
					src/elements/entities/enemy_types.c							\
					src/elements/entities/player.c								\
					src/elements/entities/player_fcts.c							\
					src/elements/entities/player_move.c							\
					src/elements/entities/projectile.c							\
					src/elements/entities/text.c								\
					src/elements/entities/text_update_fcts.c					\
					src/elements/entities/dialogue.c							\
					src/elements/entities/dialogue_fcts.c						\
					src/elements/entities/buttons/button.c						\
					src/elements/entities/buttons/slot_button.c					\
					src/elements/entities/buttons/slot_button_fcts.c			\
					src/elements/entities/buttons/button_fcts.c					\
					src/elements/entities/buttons/button_types.c				\
					src/elements/entities/particles/falling_particle.c			\
					src/elements/entities/particles/meteo.c						\
					src/elements/entities/particles/meteo_effects.c				\
					src/elements/entities/particles/night_effect.c				\
					src/elements/entities/particles/hit_particle.c				\
					src/elements/entities/interactable/interactable.c			\
					src/elements/entities/interactable/interactable_fcts.c		\
					src/elements/entities/interactable/npc.c					\
					src/elements/entities/interactable/trigger.c

SCENE_SRC		=	src/scene/scene.c											\
					src/scene/scene_elements.c									\
					src/scene/load_scene.c										\
					src/scene/button_load_actions.c								\
					src/scene/menu_scene.c										\
					src/scene/gameover_scene.c									\
					src/scene/victory_scene.c									\
					src/scene/intro_scene.c										\
					src/scene/howtoplay/howtoplay_scene.c						\
					src/scene/howtoplay/button_htp_actions.c					\
					src/scene/settings/settings_scene.c							\
					src/scene/settings/settings_subwindows.c					\
					src/scene/settings/button_settings_actions.c				\
					src/scene/settings/button_settings_res_actions.c			\
					src/scene/world/world_scene.c								\
					src/scene/world/world_scene_fcts.c							\
					src/scene/world/world.c										\
					src/scene/world/hud.c										\
					src/scene/world/inventory.c									\
					src/scene/world/inventory_slots.c							\
					src/scene/world/items_actions.c								\
					src/scene/world/camera.c									\
					src/scene/world/map.c										\
					src/scene/world/save.c

RPGSH_SCR		=	src/rpgsh/rpgsh.c											\
					src/rpgsh/file.c											\
					src/rpgsh/args.c											\
					src/rpgsh/execute.c											\
					src/rpgsh/conditions.c										\
					src/rpgsh/attach.c											\
					src/rpgsh/commands/commands.c								\
					src/rpgsh/commands/npc_commands.c							\
					src/rpgsh/commands/world_commands.c							\
					src/rpgsh/commands/inv_commands.c

UTILS_SRC		=	src/utils/utils.c											\
					src/utils/int_str.c											\
					src/utils/origins.c											\
					src/utils/elements_interact.c								\
					src/utils/math.c											\
					src/utils/physics.c											\
					src/utils/animation.c										\
					src/utils/text_loader.c										\
					src/utils/read.c

BONUS_SRC		=	bonus/src/rpgsh/bonus_commands.c

LIB_DIR		=	./mylib
INC_DIR		=	./include

SFML_LIB	=	-lcsfml-system -lcsfml-window -lcsfml-graphics -lcsfml-audio

CFLAGS		+=	-W -Wall -Werror -I$(INC_DIR)

OBJ			=	$(MAIN_SRC:.c=.o) $(ELEMENTS_SRC:.c=.o) $(SCENE_SRC:.c=.o) $(RPGSH_SCR:.c=.o) $(UTILS_SRC:.c=.o)
BONUS_OBJ	=	$(BONUS_SRC:.c=.o)

NAME		=	my_rpg

all:	$(NAME)

$(NAME):	$(OBJ)
	make -C $(LIB_DIR)
	gcc $(CFLAGS) -o $(NAME) $(OBJ) -L$(LIB_DIR) $(SFML_LIB) -lm -lmy

debug:	CFLAGS += -g
debug: 	fclean $(OBJ)
	make -C $(LIB_DIR) debug
	gcc $(CFLAGS) -o $(NAME) $(OBJ) -L$(LIB_DIR) $(SFML_LIB) -lm -lmy

bonus:	CFLAGS += -D BONUS
bonus: fclean $(OBJ) $(BONUS_OBJ)
	make -C $(LIB_DIR)
	gcc $(CFLAGS) -o $(NAME) $(OBJ) $(BONUS_OBJ) -L$(LIB_DIR) $(SFML_LIB) -lm -lmy

clean:
	make -C $(LIB_DIR) clean
	rm -rf $(OBJ)
	rm -rf $(BONUS_OBJ)

fclean: clean
	make -C $(LIB_DIR) fclean
	rm -f $(NAME)

re: fclean all