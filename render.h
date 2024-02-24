#ifndef RENDER_H_INCLUDED
#define RENDER_H_INCLUDED

#include "libs.h"
#include <vector>

#define RENDER_SCALE 2
#define TARGET_FPS 60

#define PROJECTION_PERSPECTIVE 0
#define PROJECTION_ORTHO 1

extern int animplayer_character;

struct gl_texture {

	GLuint TextureID = 0;
	ILuint imgID = 0;

	GLuint TextureWidth = 0;
	GLuint TextureHeight = 0;
	float alpha;

};

struct gl_textureclip {

	float pos_x;
	float pos_y;
	float width;
	float height;

};

struct gl_shaderprogram {

	GLuint ID;

	GLuint vertex_shader;
	GLuint fragment_shader;

};

struct gl_character {
    GLuint ID; // ID handle of the glyph texture
    glm::ivec2   size;      // Size of glyph
    glm::ivec2   bearing;   // Offset from baseline to left/top of glyph
    GLuint advance;   // Horizontal offset to advance to next glyph
};
extern std::map<GLchar, gl_character> gl_charactermap;
extern FT_Face face;
extern unsigned int fontVAO, fontVBO;

// additional stuff add here and modify parser.
extern struct MaterialDefinition
{
	std::string materialName;
	std::string textureName;

	gl_texture cache;
	
} materialdefinition;

struct kVector;

struct game_texture {
	std::vector<MaterialDefinition*> cachedMaterials;
} extern *texturemgr;

/* TEXTURE DEFINITIONS */

/* Pointers to our window, renderer, texture, and font */
extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern SDL_Surface* gamesurface;
extern SDL_Texture *textarget;
extern SDL_GLContext context;
extern TTF_Font* font;
extern FT_Library ft;
extern game_texture* texturemgr;

extern gl_texture background;
extern std::string background_texname;

/* OpenGL Graphics resources */
extern GLuint gProgramID;
extern GLint gVertexPos3DLocation;
extern GLuint gVAO;
extern GLuint gVBO;
extern GLuint gIBO;
extern GLuint gEBO;
extern GLuint vertexShader;
extern GLuint fragmentShader;

extern gl_shaderprogram texturequadshader;
extern gl_shaderprogram colorquadshader;
extern gl_shaderprogram fontshader;

extern glm::mat4 model;
extern glm::mat4 view;
extern glm::mat4 projection;

void ToggleFullscreen(SDL_Window* Window);
void R_RenderBackground();
void R_FadeOutBackground();

void R_InitTextures(game_texture* manager);
void R_FreeMaterial(game_texture* manager);
void R_AddMaterial(game_texture* manager, MaterialDefinition* definition);
void R_ClearMaterials(game_texture* manager);
void R_RemoveMaterial(game_texture* manager, MaterialDefinition* definition);
void R_LoadMaterials(game_texture* manager, char* path);
gl_texture R_GetMaterial(game_texture* manager, const char* material);

GLuint R_LoadShader(const char* path, GLenum shader_type);
void R_ShaderSetup(gl_shaderprogram shaderprogram, const char* vertexpath, const char* fragmentpath);
void R_SetupTexture(gl_texture texture, const char* path);
void R_GLShaderInit();
void R_SetTextureParameters();
bool R_Clear();
void R_SwitchProjection(int projection_id, gl_shaderprogram shader);
bool R_LoadIMG(gl_texture texture, const char* path);
void R_RenderTextureQuad(glm::vec3 position, float rotation, glm::vec3 scale, gl_textureclip *clip, gl_texture texture, gl_texture* decal, float mixratio, gl_shaderprogram shader);
void R_RenderUIQuad(glm::vec3 position, float rotation, glm::vec3 scale, glm::vec4 color, gl_shaderprogram shader);
std::array<GLfloat, 32> R_setQuadColorCoords(glm::vec4 color);
std::array<GLfloat, 32> R_setQuadSpritesheetCoords(float xpos, float ypos, float spritewidth, float spriteheight, gl_texture texture);
void R_RenderTexture(gl_texture texture, GLfloat x, GLfloat y);
int R_LoadFont(const char* font_path, int size);
void R_RenderText(gl_shaderprogram shader, std::string text, float x, float y, float scale, glm::vec3 color);
#endif // RENDER_H_INCLUDED 
