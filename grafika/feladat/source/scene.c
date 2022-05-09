#include "scene.h"
#include "move.h"
#include "app.h"

#include <obj/load.h>
#include <obj/draw.h>

#ifndef GL_EXT_texture_edge_clamp
#define GL_EXT_CLAMP_TO_EDGE 0x812F
#endif

void init_scene(Scene *scene)
{
    load_model(&(scene->weapon.model), "assets/models/m4a1.obj");
    load_model(&(scene->lamp.model), "assets/models/duck.obj");

    scene->weapon.texture = load_texture("assets/textures/handgun.jpg");
    scene->lamp.texture = load_texture("assets/textures/handgun.jpg");

    scene->crosshair.texture = load_texture("assets/textures/crosshair.png");

    scene->help.texture = load_texture("assets/textures/help.png");
    scene->help.isHelpOn = false;

    scene->room.size = 500;

    // Room
    scene->room.back = load_texture("assets/textures/wall.jpg");
    scene->room.front = load_texture("assets/textures/wall.jpg");
    scene->room.left = load_texture("assets/textures/wall.jpg");
    scene->room.right = load_texture("assets/textures/wall.jpg");
    scene->room.top = load_texture("assets/textures/ceiling.jpg");
    scene->room.ground = load_texture("assets/textures/floor.jpg");

    scene->material.ambient.red = 0.0;
    scene->material.ambient.green = 0.0;
    scene->material.ambient.blue = 0.0;

    scene->material.diffuse.red = 1.0;
    scene->material.diffuse.green = 1.0;
    scene->material.diffuse.blue = 1.0;

    scene->material.specular.red = 0.0;
    scene->material.specular.green = 0.0;
    scene->material.specular.blue = 1.0;

    scene->material.shininess = 127.0;

    scene->lighting.ambient_light[0] = 1.0f;
    scene->lighting.ambient_light[1] = 1.0f;
    scene->lighting.ambient_light[2] = 1.0f;
    scene->lighting.ambient_light[3] = 1.0f;

    scene->lighting.diffuse_light[0] = 1.0f;
    scene->lighting.diffuse_light[1] = 1.0f;
    scene->lighting.diffuse_light[2] = 1.0f;
    scene->lighting.diffuse_light[3] = 1.0f;

    scene->lighting.specular_light[0] = 1.0f;
    scene->lighting.specular_light[1] = 1.0f;
    scene->lighting.specular_light[2] = 1.0f;
    scene->lighting.specular_light[3] = 1.0f;

    scene->lighting.position[0] = 10.0f;
    scene->lighting.position[1] = 10.0f;
    scene->lighting.position[2] = 10.0f;
    scene->lighting.position[3] = 1.0f;

    scene->weapon.position.x = 0.0;
    scene->weapon.position.y = 0.0;
    scene->weapon.position.z = 0.0;

    scene->weapon.rotation.x = 0.0;
    scene->weapon.rotation.y = 0.0;
    scene->weapon.rotation.z = 0.0;
}

void set_lighting(Lighting *lighting)
{
    glLightfv(GL_LIGHT0, GL_AMBIENT, lighting->ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lighting->diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lighting->specular_light);
    glLightfv(GL_LIGHT0, GL_POSITION, lighting->position);
}

void set_material(const Material *material)
{
    float ambient_material_color[] = {
        material->ambient.red,
        material->ambient.green,
        material->ambient.blue};

    float diffuse_material_color[] = {
        material->diffuse.red,
        material->diffuse.green,
        material->diffuse.blue};

    float specular_material_color[] = {
        material->specular.red,
        material->specular.green,
        material->specular.blue};

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_material_color);

    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &(material->shininess));
}

void set_lightning_z_position(Lighting *lighting, double speed)
{
    lighting->position[0] += speed * 10;
}

void set_lightning_y_position(Lighting *lighting, double speed)
{
    lighting->position[2] += speed * 10;
}

void set_lightning_x_position(Lighting *lighting, double speed)
{
    lighting->position[1] += speed * 10;
}

void update_scene(Scene *scene, double time, Camera *camera)
{
    moveItem(scene, time, camera);
}

void render_environment(const Scene *scene)
{
    GLuint boxList = glGenLists(1);
    glNewList(boxList, GL_COMPILE);

    GLfloat zeros[] = {0, 0, 0};
    GLfloat ones[] = {1, 1, 1};

    glMaterialfv(GL_FRONT, GL_DIFFUSE, zeros);
    glMaterialfv(GL_FRONT, GL_AMBIENT, ones);

    draw_walls(scene->room);
    // draw_crosshair(scene->crosshair);
    if (scene->help.isHelpOn)
    {
        drawHelp(scene->help.texture);
    }

    glEndList();

    glCallList(boxList);
}

void draw_walls(Room room)
{
    glBindTexture(GL_TEXTURE_2D, room.left);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_EXT_CLAMP_TO_EDGE);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(-room.size, 0, -room.size);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(-room.size, room.size, -room.size);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-room.size, room.size, room.size);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(-room.size, 0, room.size);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, room.right);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_EXT_CLAMP_TO_EDGE);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(room.size, 0, room.size);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(room.size, room.size, room.size);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(room.size, room.size, -room.size);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(room.size, 0, -room.size);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, room.front);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_EXT_CLAMP_TO_EDGE);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(-room.size, 0, -room.size);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(room.size, 0, -room.size);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(room.size, room.size, -room.size);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-room.size, room.size, -room.size);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, room.back);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_EXT_CLAMP_TO_EDGE);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(-room.size, 0, room.size);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(-room.size, room.size, room.size);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(room.size, room.size, room.size);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(room.size, 0, room.size);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, room.top);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_EXT_CLAMP_TO_EDGE);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(room.size, room.size, room.size);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(room.size, room.size, -room.size);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-room.size, room.size, -room.size);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(-room.size, room.size, room.size);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, room.ground);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_EXT_CLAMP_TO_EDGE);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(room.size, 0, room.size);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(room.size, 0, -room.size);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-room.size, 0, -room.size);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(-room.size, 0, room.size);
    glEnd();
}

/*void draw_crosshair(Crosshair crosshair)
{
    glBindTexture(GL_TEXTURE_2D, crosshair);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_EXT_CLAMP_TO_EDGE);
    glEnd();
}*/

void set_help(Scene *scene, bool isHelpOn)
{
    scene->help.isHelpOn = isHelpOn;
}

void drawHelp(int texture)
{
    glDisable(GL_LIGHTING);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    glBindTexture(GL_TEXTURE_2D, texture);

    /*glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3d(-4, 3, -5);

    glTexCoord2f(1, 0);
    glVertex3d(4, 3, -5);

    glTexCoord2f(1, 1);
    glVertex3d(4, -3, -5);

    glTexCoord2f(0, 1);
    glVertex3d(-4, -3, -5);*/

    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(0, 0, -5);

    glTexCoord2f(1, 0);
    glVertex3f(WINDOW_WIDTH, 0, -5);

    glTexCoord2f(1, 1);
    glVertex3f(WINDOW_WIDTH, WINDOW_HEIGHT, -5);

    glTexCoord2f(0, 1);
    glVertex3f(0, WINDOW_HEIGHT, -5);

    glEnd();

    glEnable(GL_LIGHTING);
}

void render_scene(const Scene *scene)
{
    glRotatef(90, 1, 0, 0);
    set_material(&(scene->material));
    set_lighting(&(scene->lighting));
    draw_lighting_position(&(scene->lighting), scene);
    render_environment(scene);
    draw_weapon(scene);
}

void draw_weapon(Scene *scene)
{
    glBindTexture(GL_TEXTURE_2D, scene->weapon.texture);
    glPushMatrix();
    glTranslatef(scene->weapon.position.x, scene->weapon.position.y, scene->weapon.position.z);
    glScalef(
        4.0f,
        4.0f,
        4.0f);
    glRotatef(scene->weapon.rotation.x, 1, 0, 0);
    glRotatef(scene->weapon.rotation.y, 0, 1, 0);
    glRotatef(scene->weapon.rotation.z, 0, 0, 1);
    draw_model(&(scene->weapon.model));
    glPopMatrix();
}

void draw_lighting_position(Lighting *lighting, Scene *scene)
{
    glPushMatrix();
    glRotatef(-90, 1, 0, 0);
    glScalef(
        15.0f,
        15.0f,
        15.0f);
    glTranslatef(lighting->position[0], lighting->position[1], lighting->position[2]);
    glBindTexture(GL_TEXTURE_2D, scene->lamp.texture);
    draw_model(&(scene->lamp.model));

    glPopMatrix();
}