all:
	gcc -Iinclude/ source/app.c source/camera.c source/main.c source/scene.c source/texture.c -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lobj -lopengl32 -lm -o beadando.exe -Wall -Wextra -Wpedantic

linux:
	gcc -Iinclude/ source/app.c source/camera.c source/main.c source/scene.c source/texture.c -lobj -lSDL2 -lSDL2_image -lGL -lm -o beadando -Wall -Wextra -Wpedantic
