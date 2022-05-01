#include <math.h>
#include "move.h"
#include "scene.h"

void moveItem(Scene *scene)
{
    if (abs((int)(camera.vertices->x - scene->weapon.vertices->x)) < 70 && abs((int)(camera.vertices->z - scene->weapon.vertices->z)) < 70 && camera.vertices->y < 200)
    {
        double angle = degree_to_radian(camera.pose.z);
        double angle2 = degree_to_radian(camera.pose.z + 130);

        scene->weapon.vertices->x = camera.vertices->x - sin(angle) * 22 - sin(angle2) * -30;
        scene->weapon.vertices->y = camera.vertices->y - 20;
        scene->weapon.vertices->z = camera.vertices->z - cos(angle) * 22 - cos(angle2) * -30;
        // printf("%lf\n", camera.pose.x);
        // scene->weapon.angle.x = -camera.pose.x;
        // scene->weapon.angle.y = fmod((270 + camera.pose.z), 360);
    }
}