#include "app.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
    App app;

    init_app(&app, WINDOW_WIDTH, WINDOW_HEIGHT);
    while (app.is_running)
    {
        handle_app_events(&app);
        update_app(&app);
        render_app(&app);
    }
    destroy_app(&app);

    return 0;
}
