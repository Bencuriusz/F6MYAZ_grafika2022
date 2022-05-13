#include <math.h>
#include "scene.h"
#include "camera.h"

void moveItem(Scene *scene, Camera *camera)
{
    // if (abs((int)(camera->position.x - scene->weapon.position.x)) < 100 && abs((int)(camera->position.y - scene->weapon.position.z)) < 100)

    double angle = degree_to_radian(camera->rotation.z);
    double angle2 = degree_to_radian(camera->rotation.z + 130);

    scene->weapon.position.x = camera->position.x - (sin(angle) * -10) - (sin(angle2) * 10);
    scene->weapon.position.y = camera->position.z - 70;
    scene->weapon.position.z = -camera->position.y - (cos(angle) * -10) - (cos(angle2) * 10);

    scene->weapon.rotation.y = fmod((camera->rotation.z + 90), 360);
    scene->weapon.rotation.x = -fmod((camera->rotation.x), 360);
}