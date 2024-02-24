/* THE LIBS SHARED VARIABLES */
#ifndef LIBS_H_INCLUDED
#define LIBS_H_INCLUDED

#include <iostream>
#include <fstream>
#include <cfloat>
#include <cstdlib>
#include <cassert>
#include <climits>
#include <time.h>
#include <array>
#include <algorithm>
#include <map>
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

/* sudo64 note: its been fucking 40 minutes i'm trying get this fucking code to find this stupid library. */
#include <al.h>
#include <alc.h>
#include <alext.h>

#include "GL/glew.h"
#include <SDL_opengl.h>
#include "GL/glu.h"

#include <ft2build.h>
#include FT_FREETYPE_H

#include <glm/glm.hpp>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale
#include <glm/ext/matrix_clip_space.hpp> // glm::perspective
#include <glm/ext/scalar_constants.hpp> // glm::pi
#include <glm/gtc/type_ptr.hpp>

#include <IL/il.h>

/* include your game source here */
#include "client/client_main.h"
#include "client/client_render.h"

#endif // LIBS_H_INCLUDED 
