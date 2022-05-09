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

void moveItem(Scene *scene, double time, Camera *camera)
{
    // if (abs((int)(camera->position.x - scene->weapon.position.x)) < 100 && abs((int)(camera->position.y - scene->weapon.position.z)) < 100)

    double angle = degree_to_radian(camera->rotation.z);
    double angle2 = degree_to_radian(camera->rotation.z + 130);

    scene->weapon.position.x = camera->position.x - (sin(angle) * -10) - (sin(angle2) * 10);
    scene->weapon.position.y = camera->position.z - 70;
    scene->weapon.position.z = -camera->position.y - (cos(angle) * -10) - (cos(angle2) * 10);

    scene->weapon.rotation.y = fmod((camera->rotation.z + 90), 360);
    printf("x: %.2f | z: %.2f || r: %.2f\n", scene->weapon.position.x, scene->weapon.position.z, scene->weapon.rotation.y);
    // scene->weapon.rotation.x = fmod((camera->rotation.x), 360);
}