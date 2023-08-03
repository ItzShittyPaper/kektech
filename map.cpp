#include "libs.h"
#include "render.h"
#include "map.h"
#include "main.h"

struct Tile {

	SDL_Rect rect;

	SDL_Rect getBox();

};

FILE *map_file;

/*

DATADESK (.ds) SPECIFICATION

	- each object has a place on the map
	- everything is being read line by line ig
	- fuck niggers

*/

game_texture* currentmgr;
map_dsdata map;

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

void M_PlayerBorderCollide(SDL_Rect player_collider) {

	if( ( player.pos_y < 0 ) || ( player.pos_y + 16 > game_screen_height / 2)) {
		//move back
		player.pos_y -= player.vel_y;
		player.collider.y = player.pos_y;
	}

	if( ( player.pos_x < 0 ) || ( player.pos_x + 16 > game_screen_width / 2)) {
		//move back
		player.pos_x -= player.vel_x;    
		player.collider.x = player.pos_x;
	}

}

void M_PlayerTileCollide(SDL_Rect player_collider, SDL_Rect tile) {

	if(M_CheckCollision(player_collider, tile)) {
		//move back
		player.pos_y -= player.vel_y;
		player.collider.y = player.pos_y;
	}

	if(M_CheckCollision(player_collider, tile)) {
		//move back
		player.pos_x -= player.vel_x;    
		player.collider.x = player.pos_x;
	}

}

void M_PlayerCollidePortal(SDL_Rect player_collider, SDL_Rect tile, char* path) {

	/* Portal-specific collision function, could do this smarter, but it basically changes the level being loaded if they're colliding with a portal. */
	if(M_CheckCollision(player_collider, tile) ) {
		strcpy(gamemgr.currentmap, path);
		gamemgr.map_is_initialized = 0;
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
	if (map.no_collide == 0) {
		M_PlayerTileCollide(player.collider, bgtile.rect);
	}

}

void M_DrawPortal(int pos_x, int pos_y, int tile_size, char* path) {

	Tile bgtile;

	bgtile.rect.x = pos_x * tile_size * RENDER_SCALE;
	bgtile.rect.y = pos_y * tile_size * RENDER_SCALE;
	bgtile.rect.w = tile_size * RENDER_SCALE;
	bgtile.rect.h = tile_size * RENDER_SCALE;

	SDL_RenderCopy(renderer, glaggle, NULL, &bgtile.rect); 

	M_PlayerCollidePortal(player.collider, bgtile.rect, path);

}


void M_DrawTileRect(int pos_x, int pos_y, int num_x, int num_y, int tile_size, SDL_Texture* texture_index) {

	for (int i0 = 0; i0 < num_y; i0++) {
		for (int i1 = 0; i1 < num_x; i1++) {

			M_DrawTile(pos_x + i1, pos_y + i0, tile_size, texture_index);

		}	
	}
}

int commandcheck() {

	/* these two-liners check for commands like /r */	
	/* rectanngles of tiled sprites */
	map.ye_rec = strstr(map.chunk, "/r");
	if (map.ye_rec != NULL) { map.i = 3; return 1; }

	/* no-collide entity */
	map.ye = strstr(map.chunk, "/n");
        if (map.ye != NULL) { map.no_collide = 1; map.i--; return 4; }	

	/* helper-type npc, you can talk to him. that's it */
	map.ye = strstr(map.chunk, "/h");
        if (map.ye != NULL) { map.no_collide = 1; map.i = 11; return 6; }

	/* level portal */
	map.ye = strstr(map.chunk, "/p");
        if (map.ye != NULL) { map.i = 14; return 2; }

	/* background music set entity */
	map.ye = strstr(map.chunk, "/m");
        if (map.ye != NULL) { map.i = 10; return 5; }

	//map.ye = strstr(map.chunk, "/t");
        //if (map.ye != NULL) { map.i = 10; return 5; }


	return 0;

}

SDL_Texture* M_TextureAssign(char* texture) {

	// sanitize to get rid of \n
	texture[strcspn(texture, "\n")] = 0;

	SDL_Texture* temp_tex{};

	temp_tex = R_GetMaterial(currentmgr, texture);

	//if(strcmp(texture, "glaggle\n") == 0) {temp_tex = glaggle;}
	//if(strcmp(texture, "leadpipe\n") == 0) {temp_tex = leadpipe;}
	//if(strcmp(texture, "branch\n") == 0) {temp_tex = branch;}
	//if(strcmp(texture, "bare_hands\n") == 0) {temp_tex = bare_hands;}

	//if(strcmp(texture, "zlew_sheet\n") == 0) {temp_tex = zlew_sheet;}

	return temp_tex;
}

int M_InitCMD(FILE* map_file) {

	char *head = strtok(map.chunk, "; ");
	char *initbuf = (char*)malloc(sizeof(char) * 64);
	player.is_alive = false;

	while (head != NULL) {

		if(strstr(head, "SPAWN_X:") != NULL) { initbuf = strchr( head, ':' ); player.pos_x = atoi(initbuf + 1) * 16; player.collider.x = player.pos_x; }
		if(strstr(head, "SPAWN_Y:") != NULL) { initbuf = strchr( head, ':' ); player.pos_y = atoi(initbuf + 1) * 16; player.collider.y = player.pos_y; }
		if(strstr(head, "SPAWNPLAYER") != NULL) { player.is_alive = true; }

		printf("'%s'\n", head);
		head = strtok(NULL, ";");
	}	

	//player.pos_x = file_x * 16;
	//player.pos_y = file_y * 16;
	gamemgr.map_is_initialized = 1;
	//free(initbuf);
	return 0;
}

int M_ReadMapFile(const char* map_path, game_texture* texture) {
	currentmgr = texture;
	map_file = fopen(map_path, "r");
	if (map_file == NULL) { printf("fuck\n\nCRITICAL MAP LOADING ERROR\nMAP PATH: %s\n\nFUCK YOU!!!\n\n", map_path); }
	map.i = -1;

	/* reading the map header */

	if (gamemgr.map_is_initialized == 0) {
		fgets(map.chunk, sizeof(map.chunk), map_file);
		map.ye = strstr(map.chunk, "DSHEADER");
		if (map.ye != NULL ) {
			M_InitCMD(map_file);
		}
	}

	/* check if the player collides with the border of the screen */
	M_PlayerBorderCollide(player.collider);

	/* parsing the .ds file */
	while(fgets(map.chunk, sizeof(map.chunk), map_file) != NULL) {

		if (map.chunk[0] != '\n' && gamemgr.map_is_initialized == 1) {
			map.chkrgstr = strstr(map.chunk, "//");
			if (map.chkrgstr != NULL) { goto skip; }


			/* this is the parse routine */
			switch(map.i) {

				default: 

				case 0:
					/* read the x coordinate                           */
					sscanf(map.chunk, "%d", &map.file_x);
					break;
				case 1:
					/* second pass: read the y coordinate              */
					sscanf(map.chunk, "%d", &map.file_y);
					break;
				case 2:

					map.command_index = commandcheck();
					if (map.command_index != 0) {
						break;
					}
        				else {
						M_DrawTile(map.file_x, map.file_y, 16, M_TextureAssign(map.chunk)); 
						map.no_collide = 0;
						map.i = -1; break; 
					}

				/* RECTANGLE DRAWING ROUTINE */
				case 4:
					sscanf(map.chunk, "%d", &map.rec_y2);
					break;
				case 5:
					sscanf(map.chunk, "%d", &map.rec_x2);
					break;
				case 6:
					M_DrawTileRect(map.file_x, map.file_y, map.rec_x2, map.rec_y2, 16, M_TextureAssign(map.chunk));

					map.i = -1; strcpy(map.ye_rec, "\0"); break;

				/* BACKGROUND MUSIC SWITCH / INCLUDE ROUTINE */
				case 11:
					if (mixer.music == NULL) {
						char* musptr = (char*)malloc(256);
						sscanf(map.chunk, "%s", musptr);
						mixer.music = Mix_LoadMUS( musptr);
						//printf(chunk);
						free(musptr);
					}
					map.i = -1;
					break;

				/* HELPER NPC SPAWN */
				case 12:
					/* pass on the spritesheet info */
					sscanf(map.chunk, "%d", &map.npc_direct);
//					puts("1");
					break;
				case 13:
					/* pass on the dialog */
					sscanf(map.chunk, "%s", map.npc_dialog);
					//strcpy(npc_dialog, chunk);
//					puts("2");
					break;
				case 14:
					/* pass on the direction info */
					/* 0 - left
					   1 - right
					   2 - down
					   3 - up */
					//NPC_DrawEntity(zlew_sheet, file_x, file_y, atoi(chunk), "leo/txt/dialog0.txt", 0);
					NPC_DrawEntity(M_TextureAssign(map.chunk), map.file_x, map.file_y, map.npc_direct, map.npc_dialog, 0);

					//npc_dialog = NULL;
					map.npc_direct = 0;
//					puts("5");
//					free(npctex);
					map.i = -1; break;

				/* LEVEL PORTAL */
				case 15:
					sscanf(map.chunk, "%s", map.portptr);
					//printf("%s\n", portptr);
					break;
				case 16:
					M_DrawPortal(map.file_x, map.file_y, 16, map.portptr);
					map.i = -1; break;

			}
			map.i++;
		}
		skip:
			continue;
	}
	fclose(map_file);
	return 0;
}
