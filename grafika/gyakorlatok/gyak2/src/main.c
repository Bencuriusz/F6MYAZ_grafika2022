#include <SDL2/SDL.h>

#include <stdbool.h>
#include <stdio.h>

struct Lines
{
    int P1x;
    int P1y;
    int P2x;
    int P2y;
    char Color;
};

int main(int argc, char *argv[])
{
    int error_code;
    SDL_Window *window;
    bool need_run;
    SDL_Event event;
    SDL_Renderer *renderer;
    int x, y;
    int firstClick = 1;
    int MAX_LINE_COUNT = 0;

    struct Lines L;

    error_code = SDL_Init(SDL_INIT_EVERYTHING);
    if (error_code != 0)
    {
        printf("[ERROR] SDL initialization error: %s\n", SDL_GetError());
        return error_code;
    }

    window = SDL_CreateWindow(
        "Hello SDL!",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        800, 800, 0);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_RenderPresent(renderer);

    need_run = true;

    while (need_run)
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_KEYDOWN:
            case SDL_SCANCODE_Q:
                need_run = false;
                break;
            case SDL_QUIT:
                need_run = false;
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (MAX_LINE_COUNT <= 5)
                {
                    if (firstClick)
                    {
                        SDL_GetMouseState(&x, &y);
                        L.P1x = x;
                        L.P1y = y;
                        firstClick = 0;
                    }
                    else
                    {
                        SDL_GetMouseState(&x, &y);
                        SDL_SetRenderDrawColor(renderer, 200, 200, 0, SDL_ALPHA_OPAQUE);
                        SDL_RenderDrawLine(renderer, L.P1x, L.P1y, x, y);
                        SDL_RenderPresent(renderer);
                        firstClick = 1;
                        MAX_LINE_COUNT++;
                    }
                }
                else
                {
                    printf("Reached the line limit!\n");
                }
            }
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
