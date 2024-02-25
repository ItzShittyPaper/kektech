#include "libs.h"
#include "render.h"
#include "map.h"
#include "ui.h"
#include "main.h"
#include "vector.h"

/* Initializing rendering resources */
SDL_Window* window;
SDL_Renderer* renderer;
SDL_Surface* gamesurface;
SDL_Texture *textarget = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, game_screen_width, game_screen_height);
SDL_GLContext context;
TTF_Font* font;
FT_Library ft;
game_texture* texturemgr;

gl_texture background;
std::string background_texname;

GLuint gProgramID = 0;
GLint gVertexPos3DLocation = -1;
GLuint gVAO = 0;
GLuint gVBO = 0;
GLuint gIBO = 0;
GLuint gTCBO = 0;
GLuint gEBO = 0;
GLuint vertexShader;
GLuint fragmentShader;

glm::mat4 model = glm::mat4(1.0f);
glm::mat4 view = glm::mat4(1.0f);
glm::mat4 projection = glm::mat4(1.0f);

gl_shaderprogram texturequadshader;
gl_shaderprogram colorquadshader;
gl_shaderprogram fontshader;
std::map<GLchar, gl_character> charactermap;
FT_Face face;
unsigned int fontVAO, fontVBO;


/* ---------------------- */

//IBO data
GLuint indexData[] = {
		0, 1, 3,
		1, 2, 3
};

void R_ShaderSetup(gl_shaderprogram shaderprogram, const char* vertexpath, const char* fragmentpath) {

	// Create vertex shader
	shaderprogram.vertex_shader = R_LoadShader(vertexpath, GL_VERTEX_SHADER);
	
	//Create fragment shader
	shaderprogram.fragment_shader = R_LoadShader(fragmentpath, GL_FRAGMENT_SHADER);

	//Attach vertex shader to program
	glAttachShader(shaderprogram.ID, shaderprogram.vertex_shader);
	
	//Attach fragment shader to program
	glAttachShader(shaderprogram.ID, shaderprogram.fragment_shader);

	//Link program
	glLinkProgram(shaderprogram.ID);

	// delete the shaders as they're linked into our program now and no longer necessary
	glDeleteShader(shaderprogram.vertex_shader);
	glDeleteShader(shaderprogram.fragment_shader);

}

bool R_LoadIMG(gl_texture texture, const char* path) {

     	ilGenImages( 1, &texture.imgID );
    	ilBindImage( texture.imgID );

       	//Load image
    	ILboolean success = ilLoadImage(path);
	if (success) {

		glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_BPP), ilGetInteger(IL_IMAGE_WIDTH),
                 ilGetInteger(IL_IMAGE_HEIGHT), 0, ilGetInteger(IL_IMAGE_FORMAT), GL_UNSIGNED_BYTE,
                 ilGetData());
		glGenerateMipmap(GL_TEXTURE_2D);

		texture.TextureWidth = ilGetInteger(IL_IMAGE_WIDTH);
		texture.TextureHeight = ilGetInteger(IL_IMAGE_HEIGHT);

	}

    	ilBindImage(0);
	ilDeleteImage(texture.imgID);

	return true;
}

void R_SetupTexture(gl_texture texture, const char* path) {

	glGenTextures(1, &texture.TextureID);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture.TextureID);
	R_SetTextureParameters();
	R_LoadIMG(texture, path);
	glBindTexture(GL_TEXTURE_2D, 0);

}

void R_FreeMaterial(game_texture* manager)
{
	R_ClearMaterials(manager);
	delete manager;
}

void R_AddMaterial(game_texture* manager, MaterialDefinition* definition)
{
	
	/* TODO: generate a texture buffer in the cache*/

	glGenTextures(1, &definition->cache.TextureID);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, definition->cache.TextureID);
	R_SetTextureParameters();
	R_LoadIMG(definition->cache, definition->textureName.c_str());
	glBindTexture(GL_TEXTURE_2D, 0);

	printf(definition->materialName.c_str());
	printf(definition->textureName.c_str());
	manager->cachedMaterials.push_back(definition);

	if (!definition->cache.TextureID)
	{
		printf("\nError adding material\n");
	}
}

void R_ClearMaterials(game_texture* manager)
{
	for (int i = 0; i < manager->cachedMaterials.size(); i++)
	{
		MaterialDefinition* def = manager->cachedMaterials[i];	
		if (&def->cache)
		{
			glDeleteTextures(1, &def->cache.TextureID);
			//SDL_DestroyTexture(def->cache);
		}
	}

	manager->cachedMaterials.clear();
}

void R_RemoveMaterial(game_texture* manager, MaterialDefinition* definition)
{
	for (int i = 0; i < manager->cachedMaterials.size(); i++)
	{
		MaterialDefinition* def = manager->cachedMaterials[i];
		if (def == definition)
		{
			glDeleteTextures(1, &def->cache.TextureID);
			manager->cachedMaterials.erase(manager->cachedMaterials.begin() + i);
			return;
		}
	}
}

void R_LoadMaterials(game_texture* manager, char* path)
{
	FILE* file = fopen(path, "r");
	if (file == NULL) { snprintf(UI_nsod.crash_logbuffer, 256, "ERROR LOADING MATERIAL DEFINITIONS, FILE DOES NOT EXIST / PERMISSION DENIED\nMAT PATH: %s\n"); mode = kkui_crash; return; }

	char matChunk[LINE_BUF];
	/* parse line by line */
	while (fgets(matChunk, sizeof(matChunk), file) != NULL) {

		MaterialDefinition* def = new MaterialDefinition();
		def->materialName = std::string();
		def->textureName = std::string();

		// this should be material name.
		char* tok = strtok(matChunk, ";");
		def->materialName = tok;
		printf("%s, ", tok);

		// this should be texture name
		tok = strtok(NULL, ";");	
		def->textureName = tok;
		printf("%s, ", tok);

		R_AddMaterial(manager, def);
	}
}

gl_texture R_GetMaterial(game_texture* manager, const char* material)
{

	/* this could be a hashmap, potential optimization here */
	for (int i = 0; i < manager->cachedMaterials.size(); i++)
	{
		MaterialDefinition* definition = manager->cachedMaterials[i];
		if (strcmp(definition->materialName.c_str(), material) == 0)
		{
			return definition->cache;
		}
	}
	/* in the future make this return an error texture (something like the source checkerboard) if this func doesnt find any material) */
	//return nullptr;
}

void R_InitTextures(game_texture* manager) {
	R_LoadMaterials(manager, "data/mat/game.mat");
}

bool R_Clear() {

	// Clear the window to black
	SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear( GL_COLOR_BUFFER_BIT );
	SDL_RenderClear( renderer );		
	return true;

};

void R_SwitchProjection(int projection_id, gl_shaderprogram shader) {

	glm::mat4 view = glm::mat4(1.0f);
	// note that we're translating the scene in the reverse direction of where we want to move
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

	switch(projection_id) {
		case 0:
			projection = glm::perspective(glm::radians(45.0f), (float)game_screen_width / (float)game_screen_height, 0.1f, 100.0f);
			break;

		case 1:
			projection = glm::ortho(0.0f, (float)game_screen_width, 0.0f, (float)game_screen_height);
			break;

		default: break;
	}

	int modelLoc = glGetUniformLocation(shader.ID, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	int viewLoc = glGetUniformLocation(shader.ID, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	int projectionLoc = glGetUniformLocation(shader.ID, "projection");
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

}

GLuint R_LoadShader( const char* path, GLenum shader_type) {
	GLuint shaderID = 0;
	std::string shaderString;
	std::ifstream sourceFile( path );

	if( sourceFile ) {

		shaderString.assign( ( std::istreambuf_iterator< char >( sourceFile ) ), std::istreambuf_iterator< char >() );
		shaderID = glCreateShader( shader_type );

		const GLchar* shaderSource = shaderString.c_str();
		glShaderSource( shaderID, 1, (const GLchar**)&shaderSource, NULL );

		glCompileShader( shaderID );

		GLint shaderCompiled = GL_FALSE;
		glGetShaderiv( shaderID, GL_COMPILE_STATUS, &shaderCompiled );

		if( shaderCompiled != GL_TRUE ) {

			printf( "Unable to compile shader %d!\n\nSource:\n%s\n", shaderID, shaderSource );
			glDeleteShader( shaderID );
			shaderID = 0;

		}
	} else {

		printf( "Unable to open file %s\n", path );

	}
	return shaderID ;
}

void R_SetTextureParameters() {

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

}

void R_GLShaderInit() {

	texturequadshader.ID = glCreateProgram();
	R_ShaderSetup(texturequadshader, "shader/texturequad.vert", "shader/texturequad.frag");
	GLint programSuccess = GL_TRUE;
	glGetProgramiv( texturequadshader.ID, GL_LINK_STATUS, &programSuccess );

	colorquadshader.ID = glCreateProgram();
	R_ShaderSetup(colorquadshader, "shader/colorquad.vert", "shader/colorquad.frag");
	programSuccess = GL_TRUE;
	glGetProgramiv( colorquadshader.ID, GL_LINK_STATUS, &programSuccess );

	fontshader.ID = glCreateProgram();
	R_ShaderSetup(fontshader, "shader/ft.vert", "shader/ft.frag");
	programSuccess = GL_TRUE;
	glGetProgramiv( fontshader.ID, GL_LINK_STATUS, &programSuccess );

}

void R_RenderTextureQuad(glm::vec3 position, float rotation, glm::vec3 scale, gl_textureclip* clip, gl_texture texture, gl_texture* decal, float mixratio, gl_shaderprogram shader) {

	glUseProgram(shader.ID);

	R_SwitchProjection(PROJECTION_PERSPECTIVE, shader);
	std::array<GLfloat, 32> NormalizedquadVertices;

	glBindVertexArray(gVAO);
	glBindBuffer( GL_ARRAY_BUFFER, gVBO );
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, gIBO );
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof(indexData), indexData, GL_STATIC_DRAW );

	if (clip != NULL) { NormalizedquadVertices = R_setQuadSpritesheetCoords(clip->pos_x, clip->pos_y, clip->width, clip->height, texture); }
	else { NormalizedquadVertices = R_setQuadSpritesheetCoords(0, 0, 1.0f, 1.0f, texture); }
	glBufferData( GL_ARRAY_BUFFER, sizeof(NormalizedquadVertices), (void*)&NormalizedquadVertices[0], GL_STATIC_DRAW );

	/* Transformation data */
	glm::mat4 trans = glm::mat4(1.0f);
	trans = glm::translate(trans, position);
	trans = glm::rotate(trans, rotation, glm::vec3(0.0, 0.0, 1.0));
	trans = glm::scale(trans, scale);

	/* alpha data */
	if (mixratio != NULL) {
		texture.alpha = mixratio;
	}

	unsigned int transformLoc = glGetUniformLocation(shader.ID, "TransformMatrix");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

	unsigned int mixratioLoc = glGetUniformLocation(shader.ID, "MixRatio");
	glUniform1f(mixratioLoc, texture.alpha);

	// position attribute
    	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    	glEnableVertexAttribArray(0);
    	// color attribute
    	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    	glEnableVertexAttribArray(1);
    	// texture coord attribute
    	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    	glEnableVertexAttribArray(2);

    	//Set index data and render
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture.TextureID);
	if (decal != NULL) {
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, decal->TextureID);
	}
       	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	//Disable vertex position
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);
	if (decal != NULL) {
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
	glBindBuffer( GL_ARRAY_BUFFER, 0 );
	glUseProgram(0);

}

void R_RenderUIQuad(glm::vec3 position, float rotation, glm::vec3 scale, glm::vec4 color, gl_shaderprogram shader) {

	glUseProgram(shader.ID);

	R_SwitchProjection(PROJECTION_ORTHO, shader);
	std::array<GLfloat, 32> NormalizedquadVertices;

	glBindVertexArray(gVAO);
	glBindBuffer( GL_ARRAY_BUFFER, gVBO );
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, gIBO );
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof(indexData), indexData, GL_DYNAMIC_DRAW );

	NormalizedquadVertices = R_setQuadColorCoords(color);
	glBufferData( GL_ARRAY_BUFFER, sizeof(NormalizedquadVertices), (void*)&NormalizedquadVertices[0], GL_DYNAMIC_DRAW );

	/* Transformation data */
	glm::mat4 trans = glm::mat4(1.0f);
	trans = glm::translate(trans, position);
	trans = glm::rotate(trans, rotation, glm::vec3(0.0, 0.0, -1.0));
	trans = glm::scale(trans, scale);

	//projection = glm::ortho(0.0f, (float)game_screen_width, 0.0f, (float)game_screen_height);
	unsigned int transformLoc = glGetUniformLocation(shader.ID, "TransformMatrix");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
	unsigned int alphaLoc = glGetUniformLocation(shader.ID, "alpha");
	glUniform1f(alphaLoc, color.w);

	// position attribute
    	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    	glEnableVertexAttribArray(0);
    	// color attribute
    	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    	glEnableVertexAttribArray(1);
    	// texture coord attribute
    	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    	glEnableVertexAttribArray(2);

    	//Set index data and render
       	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	//Disable vertex position
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
	glBindBuffer( GL_ARRAY_BUFFER, 0 );
	glUseProgram(0);

}

std::array<GLfloat, 32> R_setQuadColorCoords(glm::vec4 color) {

	std::array<GLfloat, 32> quadVertices = {
        	// positions          // colors		          // texture coords
        	 1.0f,  1.0f, 0.0f,   color.x, color.y, color.z,  1.0f, 0.0f,
        	 1.0f, -1.0f, 0.0f,   color.x, color.y, color.z,  1.0f, 1.0f,
        	-1.0f, -1.0f, 0.0f,   color.x, color.y, color.z,  0.0f, 1.0f,
        	-1.0f,  1.0f, 0.0f,   color.x, color.y, color.z,  0.0f, 0.0f
	}; 

	return quadVertices;

}

std::array<GLfloat, 32> R_setQuadSpritesheetCoords(float xpos, float ypos, float spritewidth, float spriteheight, gl_texture texture) {

	float tw = spritewidth / texture.TextureWidth;
	float th = spriteheight / texture.TextureHeight;

	std::array<GLfloat, 32> quadVertices = {
        	// positions          // colors		 // texture coords
        	 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,  xpos + spritewidth, ypos,
        	 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,  xpos + spritewidth, ypos + spriteheight,
        	-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,  xpos, ypos + spriteheight,
        	-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,  xpos, ypos
	}; 

	return quadVertices;

}

void R_RenderBackground() {

	if (UI_dashboard.animplayer > 0.0) {
		/* render the map background */
//		SDL_SetTextureAlphaMod(UI_dashboard.menu_background, UI_dashboard.animplayer);
		UI_dashboard.animplayer -= 0.05;
		if (UI_dashboard.animplayer <= 0.0) { UI_dashboard.animplayer = 0.0; }
	}
	R_RenderTextureQuad(glm::vec3(0.0f, 0.0f, 0.0f), glm::radians(0.0f), glm::vec3(3.2f, 1.8f, 1.0f), NULL, R_GetMaterial(texturemgr, background_texname.c_str()), NULL, UI_dashboard.animplayer, texturequadshader);
}

void R_FadeOutBackground() {

	if (UI_dashboard.animplayer > 0) {
		/* render the map background */
	//	SDL_SetTextureAlphaMod(UI_dashboard.menu_background, UI_dashboard.animplayer);
		UI_dashboard.animplayer -= 8;
	}
	//SDL_RenderCopy(renderer, UI_dashboard.menu_background, NULL, NULL);

}

int R_LoadFont(const char* font_path, int size) {

	// load font as face
	FT_Face face;
	if (FT_New_Face(ft, font_path, 0, &face)) {
		std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
		return -1;
	}
	else {
		// set size to load glyphs as
		FT_Set_Pixel_Sizes(face, 0, 48);

		// disable byte-alignment restriction
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		// load first 128 characters of ASCII set
		for (unsigned char c = 0; c < 128; c++) {
			// Load character glyph 
			if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
				std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
				continue;
			}
			// generate texture
			unsigned int texture;
			glGenTextures(1, &texture);
			glBindTexture(GL_TEXTURE_2D, texture);
			glTexImage2D(
				GL_TEXTURE_2D, 
				0,
				GL_RED,
				face->glyph->bitmap.width,
				face->glyph->bitmap.rows,
				0,
				GL_RED,
				GL_UNSIGNED_BYTE,
				face->glyph->bitmap.buffer
			);
			// set texture options
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			// now store character for later use
			gl_character character = {
				texture,
				glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
				glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
				static_cast<unsigned int>(face->glyph->advance.x)
			};
			charactermap.insert(std::pair<char, gl_character>(c, character));
		}
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	// destroy FreeType once we're finished
	FT_Done_Face(face);
	FT_Done_FreeType(ft);

	// configure VAO/VBO for texture quads
	// -----------------------------------
	glGenVertexArrays(1, &fontVAO);
	glGenBuffers(1, &fontVBO);
	glBindVertexArray(fontVAO);
	glBindBuffer(GL_ARRAY_BUFFER, fontVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	return 0;
}

// render line of text
// -------------------
void R_RenderText(gl_shaderprogram shader, std::string text, float x, float y, float scale, glm::vec3 color)
{
	// activate corresponding render state	
	glUseProgram(shader.ID);
	R_SwitchProjection(1, shader);
	glUniform3f(glGetUniformLocation(shader.ID, "textColor"), color.x, color.y, color.z);
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(fontVAO);

	// iterate through all characters
	std::string::const_iterator c;
	for (c = text.begin(); c != text.end(); c++)  {

		gl_character ch = charactermap[*c];

		float xpos = x + ch.bearing.x * scale;
		float ypos = y - (ch.size.y - ch.bearing.y) * scale;

		float w = ch.size.x * scale;
		float h = ch.size.y * scale;
		// update VBO for each character
		float vertices[6][4] = {
			{ xpos,     ypos + h,   0.0f, 0.0f },            
			{ xpos,     ypos,       0.0f, 1.0f },
			{ xpos + w, ypos,       1.0f, 1.0f },
			{ xpos,     ypos + h,   0.0f, 0.0f },
			{ xpos + w, ypos,       1.0f, 1.0f },
			{ xpos + w, ypos + h,   1.0f, 0.0f }           
		};
		// render glyph texture over quad
		glBindTexture(GL_TEXTURE_2D, ch.ID);
		// update content of VBO memory
		glBindBuffer(GL_ARRAY_BUFFER, fontVBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // be sure to use glBufferSubData and not glBufferData

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		// render quad
		glDrawArrays(GL_TRIANGLES, 0, 6);
		// now advance cursors for next glyph (note that advance is number of 1/64 pixels)
		x += (ch.advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void ToggleFullscreen(SDL_Window* Window) {

	Uint32 FullscreenFlag = SDL_WINDOW_FULLSCREEN;
	bool IsFullscreen = SDL_GetWindowFlags(Window) & FullscreenFlag;
	SDL_SetWindowFullscreen(Window, IsFullscreen ? 0 : FullscreenFlag);

};
