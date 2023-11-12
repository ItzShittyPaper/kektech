#include <iostream>
#include <cfloat>
#include <cstdlib>
#include <cassert>
#include <climits>
#include <time.h>
#include <string>
#include <vector>
#include <bit>
#ifndef _WIN32
#include <alloca.h>
#else
#include <malloc.h>
#endif

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <sndfile.h>
/* SDL_Mixer-X for audio code*/
/* sudo64 note: its been fucking 40 minutes i'm trying get this fucking code to find this stupid library. */
#include <al.h>
#include <alc.h>
#include <alext.h>

/* include your game source here */
#include "client/client_main.h"
#include "client/client_render.h"
