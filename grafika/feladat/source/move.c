#include <math.h>
#include "scene.h"
#include "camera.h"

/*void moveItem(scene *scene)
{
    if (abs((int)(camera.position.x - scene->weapon.position.x)) < 70 && abs((int)(camera.position.z - scene->weapon.position.z)) < 70 && camera.position.y < 200)
    {
        double angle = degree_to_radian(camera.pose.z);
        double angle2 = degree_to_radian(camera.pose.z + 130);

        scene->weapon.position.x = camera.position.x - sin(angle) * 22 - sin(angle2) * -30;
        scene->weapon.position.y = camera.position.y - 20;
        scene->weapon.position.z = camera.position.z - cos(angle) * 22 - cos(angle2) * -30;
        // printf("%lf\n", camera.pose.x);
        // scene->weapon.angle.x = -camera.pose.x;
        scene->weapon.angle.y = fmod((270 + camera.pose.z), 360);
    }
}*/

void moveItem(Scene *scene, Camera *camera)
{
    if (abs((int)(camera->position.x - scene->weapon.position.x)) < 100 && abs((int)(camera->position.y - scene->weapon.position.y)) < 100)
    {
        // printf("%f", camera->position.y);
        double angle = degree_to_radian(camera->rotation.z);
        double side_angle = degree_to_radian(camera->rotation.z + 90.0);

        scene->weapon.position.x = camera->position.x;
        scene->weapon.position.y = camera->position.z;
        scene->weapon.position.z = camera->position.y - 250;
        // scene->weapon.rotation.y = fmod((270 + camera->rotation.z), 360);
    }
}