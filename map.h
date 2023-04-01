#include "libs.h"

/* THE MAP RENDERING CODE FOR THE ENGINE */
#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED

void M_InitTiling();
void M_DrawTile(int pos_x, int pos_y, int tile_size, SDL_Texture* texture_index);
void M_DrawTileLineH(int pos_x, int pos_y, int num_x, int tile_size, SDL_Texture* texture_index);
void M_DrawTileLineV(int pos_x, int pos_y, int num_y, int tile_size, SDL_Texture* texture_index);
void M_DrawTileRect(int pos_x, int pos_y, int num_x, int num_y, int tile_size, SDL_Texture* texture_index);

extern FILE *map_file;

extern int file_x;
extern int file_y;
extern int i2;

extern bool is_lined;
extern int line_number;
extern int list_offset;
extern bool is_bold;
extern bool is_underlined;

extern bool is_comment_check;

extern int rec_y1;
extern int rec_x1;
extern int rec_y2;
extern int rec_x2;
extern int line_length;

extern char chunk[128];
extern int border_y;
extern int border_x;
 
extern char *ye;
extern char *ye2;
extern char *ye_rec;
extern char *ye_list;
extern char *ye_attr;

#endif // MAP_H_INCLUDED 
