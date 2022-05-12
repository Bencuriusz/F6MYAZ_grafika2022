#include "camera.h"
#include <math.h>
#include <GL/gl.h>
#include <stdio.h>
#include "utils.c"

void init_camera(Camera *camera)
{
	camera->position.x = 0.0;
	camera->position.y = 0.0;
	camera->position.z = 250.0;
	camera->rotation.x = 0.0;
	camera->rotation.y = 0.0;
	camera->rotation.z = 0.0;
	camera->speed.x = 0.0;
	camera->speed.y = 0.0;
	camera->speed.z = 0.0;
}

void collisionDetection(Camera *camera)
{
	int size = 500;

	if (camera->position.x > size || camera->position.x < -size || camera->position.y < -size || camera->position.y > size)
		camera->position = camera->prevPosition;
}

void set_view(const Camera *camera)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glRotatef(-(camera->rotation.x + 90), 1.0, 0, 0); // vertical
	glRotatef(-(camera->rotation.z - 90), 0, 0, 1.0); // horizontal
	glTranslatef(-camera->position.x, -camera->position.y, -camera->position.z);
}

void rotate_camera(Camera *camera, double horizontal, double vertical)
{
	camera->rotation.z += horizontal;
	camera->rotation.x += vertical;

	if (camera->rotation.z < 0)
	{
		camera->rotation.z += 360.0;
	}

	if (camera->rotation.z > 360.0)
	{
		camera->rotation.z -= 360.0;
	}

	if (camera->rotation.x < -90)
	{
		camera->rotation.x = -90;
	}

	if (camera->rotation.x > 90.0)
	{
		camera->rotation.x = 90.0;
	}

	// printf("| %.1f | ", camera->rotation.x);
	// printf("horizontal: %.1f", camera->rotation.z);
}

void update_camera(Camera *camera, double time)
{
	double angle;
	double side_angle;
	int speedBooster = 250;

	angle = degree_to_radian(camera->rotation.z);
	side_angle = degree_to_radian(camera->rotation.z + 90.0);

	camera->prevPosition = camera->position;

	camera->position.x += cos(angle) * camera->speed.y * time * speedBooster;
	camera->position.y += sin(angle) * camera->speed.y * time * speedBooster;
	camera->position.x += cos(side_angle) * camera->speed.x * time * speedBooster;
	camera->position.y += sin(side_angle) * camera->speed.x * time * speedBooster;
	camera->position.z += camera->speed.z * time;

	collisionDetection(camera);
}

void set_camera_speed(Camera *camera, double speed)
{
	camera->speed.y = speed;
}

void set_camera_side_speed(Camera *camera, double speed)
{
	camera->speed.x = speed;
}

void squat(Camera *camera, int isSquatting)
{
	if (isSquatting)
	{
		camera->position.z = 150.0;
	}
	else
	{
		camera->position.z = 250.0;
	}
}
