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
} Scene;

/**
 * Initialize the scene by loading models.
 */
void init_scene(Scene *scene);

/**
 * Set the lighting of the scene.
 */
void set_lighting(const Lighting *lighting);

/**
 * Set the current material.
 */
void set_material(const Material *material);

/**
 * Update the scene.
 */
void update_scene(Scene *scene, Camera *camera);

/*
 * Draws the room.
 */
void draw_walls(Room room);

/*
 * Draws the crosshair.
 */
void draw_crosshair();

/*
 * Sets the show help variable.
 */
void set_help(Scene *scene, bool isHelpOn);

/*
 * Draws the help picture.
 */
void drawHelp(int texture);

/**
 * Render the scene objects.
 */
void render_scene(const Scene *scene);

/**
 * Renders the weapon objects.
 */
void draw_weapon(const Scene *scene);

/**
 * Sets the lightning's x position
 */
void set_lightning_x_position(Lighting *lighting, double speed);

/**
 * Sets the lightning's x position
 */
void set_lightning_y_position(Lighting *lighting, double speed);

/**
 * Sets the lightning's x position
 */
void set_lightning_z_position(Lighting *lighting, double speed);

/**
 * Draws the lighting
 */
void draw_lighting_position(const Lighting *lighting, const Scene *scene);

#endif /* SCENE_H */