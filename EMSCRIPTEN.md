# Emscripten

## Build

```
emmake make
```

## Link

```
em++ -flto -O3 external/Box2D/Source/Gen/float/libbox2d.a external/glaserl/libglaserl.a external/petals_log/*.o external/stb_loader/*.o external/thp/*.o external/tinyxml2/*.o src/*.o platform/sdl2/*.o platform/gl/*.o -o index.html -sUSE_SDL=2 -sUSE_SDL_IMAGE=2 -sSDL2_IMAGE_FORMATS=png -sUSE_SDL_TTF=2 -sASYNCIFY -sENVIRONMENT=web --preload-file data/ -sLEGACY_GL_EMULATION -lGL --closure 1 -Wl,-u,fileno
```
