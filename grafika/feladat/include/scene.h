#ifndef SCENE_H
#define SCENE_H

#include "camera.h"
#include "texture.h"
#include "utils.h"

#include <obj/model.h>

typedef struct Room
{
    int front, back, left, right, ground, top;
    int size;
} Room;

typedef struct Weapon
{
    Model model;
    GLuint texture_weapon;
    vec3 position;
} Weapon;

typedef struct Scene
{
    Weapon weapon;
    Material material;
    Lighting lighting;
    Room room;
} Scene;

/**
 * Initialize the scene by loading models.
 */
void init_scene(Scene *scene);

/**
 * Set the lighting of the scene.
 */
void set_lighting();

/**
 * Set the current material.
 */
void set_material(const Material *material);

/**
 * Update the scene.
 */
void update_scene(Scene *scene, double time);

/*
 * Draws the room.
 */
void draw_walls(Room room);

/**
 * Render the scene objects.
 */
void render_scene(const Scene *scene);

void draw_weapon(Scene *scene);

void set_lightning_x_position(Lighting *lighting, double speed);
void set_lightning_y_position(Lighting *lighting, double speed);
void set_lightning_z_position(Lighting *lighting, double speed);

#endif /* SCENE_H */