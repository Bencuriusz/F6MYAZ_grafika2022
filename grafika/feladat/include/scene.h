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

typedef struct Item
{
    Model model;
    GLuint texture;
    vec3 position;
    vec3 rotation;
    vec3 speed;
} Item;

typedef struct Crosshair
{
    vec2 position;
    GLuint texture;
} Crosshair;

typedef struct Help
{
    bool isHelpOn;
    GLuint texture;
} Help;

typedef struct Scene
{
    Help help;
    Item weapon;
    Item lamp;
    Material material;
    Lighting lighting;
    Room room;
    Crosshair crosshair;
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
void update_scene(Scene *scene, double time, Camera *camera);

/*
 * Draws the room.
 */
void draw_walls(Room room);

void set_help(Scene *scene, bool isHelpOn);

void drawHelp(int texture);

/**
 * Render the scene objects.
 */
void render_scene(const Scene *scene);

void draw_weapon(Scene *scene);

void set_lightning_x_position(Lighting *lighting, double speed);
void set_lightning_y_position(Lighting *lighting, double speed);
void set_lightning_z_position(Lighting *lighting, double speed);

#endif /* SCENE_H */