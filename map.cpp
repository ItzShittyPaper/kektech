#include "libs.h"
#include "render.h"
#include "map.h"
#include "main.h"

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
int no_collide = 0;

bool is_comment_check = false;

int rec_y1;
int rec_x1;
int rec_y2;
int rec_x2;
int line_length;

char chunk[128];
 
char *ye;
char *ye2;
char *ye_rec;
char *ye_list;
char *ye_attr;

bool M_CheckCollision(SDL_Rect a, SDL_Rect b) {

	//The sides of the rectangles
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	//Calculate the sides of rect A
	leftA = a.x;
	rightA = a.x + a.w;
	topA = a.y;
	bottomA = a.y + a.h;

	//Calculate the sides of rect B
	leftB = b.x;
	rightB = b.x + b.w;
	topB = b.y;
	bottomB = b.y + b.h;

	//If any of the sides from A are outside of B
	if( bottomA <= topB ) { return false; }
	if( topA >= bottomB ) { return false; }
	if( rightA <= leftB ) { return false; }
	if( leftA >= rightB ) { return false; }

	//If none of the sides from A are outside B
	return true;
}

void M_PlayerCollide(SDL_Rect player_collider, SDL_Rect tile) {

	/* "640" is the width of the screen, i'll have to fix it */
	if( ( player.pos_x < 0 ) || ( player.pos_x + 16 > 512 / 2) || M_CheckCollision(player_collider, tile) ) {
		//move back
		player.pos_x -= player.vel_x;    
		player.collider.x = player.pos_x;
	}

	/* "576" is the width of the screen, i'll have to fix it */
	if( ( player.pos_y < 0 ) || ( player.pos_y + 16 > 448 / 2) || M_CheckCollision(player_collider, tile) ) {
		//move back
		player.pos_y -= player.vel_y;
		player.collider.y = player.pos_y;
	}
}

void M_DrawTile(int pos_x, int pos_y, int tile_size, SDL_Texture* texture_index) {

	Tile bgtile;

	bgtile.rect.x = pos_x * tile_size * RENDER_SCALE;
	bgtile.rect.y = pos_y * tile_size * RENDER_SCALE;
	bgtile.rect.w = tile_size * RENDER_SCALE;
	bgtile.rect.h = tile_size * RENDER_SCALE;

	SDL_RenderCopy(renderer, texture_index, NULL, &bgtile.rect); 

	/* COLLISION DETECTION */
	if (no_collide == 0) {
		M_PlayerCollide(player.collider, bgtile.rect);
	}
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

 		if (chunk[0] != '\n') {
			commentcheck(i);

			/* this is the parse routine */
			switch(i) {

				default:
					break;
	
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

					ye = strstr(chunk, "/n");
        				if (ye != NULL) { no_collide = 1; i--; break; }
	
        				else {
						M_DrawTile(file_y, file_x, 16, M_TextureAssign(chunk)); 
						no_collide = 0;
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
					M_DrawTileRect(file_y, file_x, rec_y2, rec_x2, 16, M_TextureAssign(chunk));

					if (ye_rec != NULL) { i = -1; ye_rec = NULL; break; }

				/* HORIZONTAL LINE DRAWING ROUTINE */
				case 7:
					sscanf(chunk, "%d", &line_length);
					M_DrawTileHLine(file_y, file_x, line_length, 16, M_TextureAssign(chunk));
					break;
				case 8:
					i = -1;
					break;

				/* VERTICAL LINE DRAWING ROUTINE */
				case 9:
					sscanf(chunk, "%d", &line_length);
					M_DrawTileVLine(file_y, file_x, line_length, 16, M_TextureAssign(chunk));
					break;
				case 10:
					i = -1;
					break;
			}
			i++;
		}
	}
	fclose(map_file);
}
