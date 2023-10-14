#include <iostream>
#include <cstdlib>
#include <time.h>
#include <string>
#include <vector>
#ifndef _WIN32
#include <alloca.h>
#else
#include <malloc.h>
#endif

#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
/* SDL_Mixer-X for audio code */
#include <SDL_mixer_ext/SDL_mixer_ext.h>

/* include your game source here */
#include "client/client_main.h"
#include "client/client_render.h"
