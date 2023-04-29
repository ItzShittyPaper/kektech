#include "libs.h"
#include "render.h"
#include "map.h"

struct Tile {

	SDL_Rect rect;
	SDL_Rect getBox();

};

FILE *map_file;

int file_x;
int file_y;
int i2 = 0;

bool is_lined = false;
int line_number = 1;
int list_offset = 0;
bool is_bold = false;
bool is_underlined = false;

bool is_comment_check = false;

int rec_y1;
int rec_x1;
int rec_y2;
int rec_x2;
int line_length;

char chunk[128];
int border_y;
int border_x;
 
char *ye;
char *ye2;
char *ye_rec;
char *ye_list;
char *ye_attr;

void M_DrawTile(int pos_x, int pos_y, int tile_size, SDL_Texture* texture_index) {

	Tile bgtile;

	bgtile.rect.x = pos_x * tile_size * RENDER_SCALE;
	bgtile.rect.y = pos_y * tile_size * RENDER_SCALE;
	bgtile.rect.w = tile_size * RENDER_SCALE;
	bgtile.rect.h = tile_size * RENDER_SCALE;
	
	SDL_RenderCopy(renderer, texture_index, NULL, &bgtile.rect); 

}

void M_DrawTileHLine(int pos_x, int pos_y, int num_x, int tile_size, SDL_Texture* texture_index) {

	for (int i1 = 0; i1 < num_x; i1++) {

		M_DrawTile(pos_x + i1, pos_y, tile_size, texture_index);

	}	
}

void M_DrawTileVLine(int pos_x, int pos_y, int num_y, int tile_size, SDL_Texture* texture_index) {

	for (int i1 = 0; i1 < num_y; i1++) {

		M_DrawTile(pos_x, pos_y + i1, tile_size, texture_index);

	}	
}

void M_DrawTileRect(int pos_x, int pos_y, int num_x, int num_y, int tile_size, SDL_Texture* texture_index) {

	for (int i0 = 0; i0 < num_y; i0++) {
		for (int i1 = 0; i1 < num_x; i1++) {

			M_DrawTile(pos_x + i1, pos_y + i0, tile_size, texture_index);

		}	
	}
}

void commentcheck(int i) {

  ye = strstr(chunk, "/*");
  if (ye != NULL) { is_comment_check = true; }

  ye = strstr(chunk, "*/");
  if (ye != NULL && is_comment_check == true) { is_comment_check = false; i--; }

}

SDL_Texture* M_TextureAssign(const char* texture) {

	SDL_Texture* temp_tex;

	if(strcmp(texture, "glaggle\n") == 0) {temp_tex = glaggle;}
	if(strcmp(texture, "leadpipe\n") == 0) {temp_tex = leadpipe;}
	if(strcmp(texture, "branch\n") == 0) {temp_tex = branch;}
	if(strcmp(texture, "bare_hands\n") == 0) {temp_tex = bare_hands;}

	return temp_tex;
	SDL_DestroyTexture(temp_tex);

}

int M_ReadMapFile(const char* map) {

  map_file = fopen(map, "r");
  int i = -3;

  /* parsing the .ds file */
  while(fgets(chunk, sizeof(chunk), map_file) != NULL) {

    commentcheck(i);

    /* this is the parse routine */
    switch(i) {

      default:
        break;

      case -3:
        sscanf(chunk, "%d", &file_y);
        break;
      case -2:
        sscanf(chunk, "%d", &file_x);
        break;
      case -1:
//        if (checktermsize(file_y, file_x) == 1) { fclose(fp); endwin(); return 0; }
        border_y = file_y;
        border_x = file_x;

      case 0:
        /* read the y coordinate                           */
        if (ye_rec == NULL) { sscanf(chunk, "%d", &file_y); }
        break;
      case 1:
        /* second pass: read the x coordinate              */
        sscanf(chunk, "%d", &file_x);
        break;
      case 2:

        /* these commands check for commands like /r */
        ye_rec = strstr(chunk, "/r");
        if (ye_rec != NULL) { i = 3; break; }


        /* lines, horizontal and vertical */
        ye = strstr(chunk, "/h");
        if (ye != NULL) { i = 6; break; }

        ye = strstr(chunk, "/v");
        if (ye != NULL) { i = 8; break; }

        else {

		M_DrawTile(file_y, file_x, 32, M_TextureAssign(chunk)); 

		i = -1; break; 

	}

      /* RECTANGLE DRAWING ROUTINE */
      case 4:
        sscanf(chunk, "%d", &rec_y2);
        break;
      case 5:
        sscanf(chunk, "%d", &rec_x2);
        break;
      case 6:
        ye_rec = strstr(chunk, "/e");
        M_DrawTileRect(file_y, file_x, rec_y2, rec_x2, 32, glaggle);

        if (ye_rec != NULL) { i = -1; ye_rec = NULL; break; }

      /* HORIZONTAL LINE DRAWING ROUTINE */
      case 7:
        sscanf(chunk, "%d", &line_length);
        M_DrawTileHLine(file_y, file_x, line_length, 32, glaggle);
        break;
      case 8:
        i = -1;
        break;

      /* VERTICAL LINE DRAWING ROUTINE */
      case 9:
        sscanf(chunk, "%d", &line_length);
        M_DrawTileVLine(file_y, file_x, line_length, 32, glaggle);
        break;
      case 10:
        i = -1;
        break;
    }
    i++;
  }
  fclose(map_file);
}
