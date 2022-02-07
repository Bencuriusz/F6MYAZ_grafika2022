#include <GL/gl.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include <stdbool.h>
#include <stdio.h>

/**
 * SDL2 OpenGL example
 */
int main(int argc, char *argv[])
{
  int error_code;
  SDL_Window *window;
  bool need_run;
  SDL_Event event;
  SDL_GLContext gl_context;
  int i;

  error_code = SDL_Init(SDL_INIT_EVERYTHING);
  if (error_code != 0)
  {
    printf("[ERROR] SDL initialization error: %s\n", SDL_GetError());
    return error_code;
  }

  window = SDL_CreateWindow(
      "Hello SDL!",
      SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
      1280, 720,
      SDL_WINDOW_OPENGL);

  gl_context = SDL_GL_CreateContext(window);
  glClearColor(0, 0, 0, 1);
  glClear(GL_COLOR_BUFFER_BIT);

  double speed_and_direction = 0.1;
  need_run = true;
  while (need_run)
  {
    while (SDL_PollEvent(&event))
    {
      switch (event.type)
      {
      case SDL_KEYDOWN:
        switch (event.key.keysym.scancode)
        {
        case SDL_SCANCODE_ESCAPE:
          need_run = false;
          break;
        case SDL_SCANCODE_A:
          speed_and_direction += 0.1;
          break;
        case SDL_SCANCODE_D:
          speed_and_direction -= 0.1;
          break;
        case SDL_SCANCODE_SPACE:
          speed_and_direction = 0;
          break;
        default:
          break;
        }
        break;
      }
    }

    glRotatef(speed_and_direction, 0, 0, 1);

    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_TRIANGLES);
    glColor3f(1, 0, 0);
    glVertex2f(0, 0);
    glColor3f(0, 1, 0);
    glVertex2f(1, 0);
    glColor3f(0, 0, 1);
    glVertex2f(0, 1);
    glEnd();

    SDL_GL_SwapWindow(window);
  }

  SDL_GL_DeleteContext(gl_context);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
