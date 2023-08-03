
/* THE MAP RENDERING CODE FOR THE ENGINE */
#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED
#include "libs.h"

#define LINE_BUF 128

void M_InitTiling();

bool M_CheckCollision(SDL_Rect a, SDL_Rect b);
void M_PlayerTileCollide(SDL_Rect player_collider, SDL_Rect tile);

void M_DrawTile(int pos_x, int pos_y, int tile_size, SDL_Texture* texture_index);
void M_DrawTileLineH(int pos_x, int pos_y, int num_x, int tile_size, SDL_Texture* texture_index);
void M_DrawTileLineV(int pos_x, int pos_y, int num_y, int tile_size, SDL_Texture* texture_index);
void M_DrawTileRect(int pos_x, int pos_y, int num_x, int num_y, int tile_size, SDL_Texture* texture_index);

class game_texture;
int M_ReadMapFile(const char* map_path, game_texture* texture);

//extern FILE *map_file;

struct map_dsdata {

	int file_x;
	int file_y;

	int i = -3;

	bool is_lined = false;
	int line_number = 1;
	int no_collide = 0;

	int command_index = 0;

	int rec_y1;
	int rec_x1;
	int rec_y2;
	int rec_x2;
	int line_length;

	char chunk[LINE_BUF];

	/* i know the ye thing is confusing, it's just a register name in DS22 */
	char *chkrgstr;

	char *ye;
	char *ye2;
	char *ye_rec;
	char *ye_list;

	/* separate argument buffers */
	char npc_texarg[255];
	char npc_dialog[255];
	int   npc_direct;	
	char portptr[255];


} extern map;

#endif // MAP_H_INCLUDED 
