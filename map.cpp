#include "libs.h"
#include "render.h"
#include "audio.h"
#include "map.h"
#include "main.h"
#include "ui.h"

struct Tile {

	SDL_Rect rect;
	SDL_Rect getBox();

};

FILE *map_file;

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

	if( ( player.pos_y < 0 ) || ( player.pos_y + 16 > game_viewport_height)) {
		//move back
		player.pos_y -= player.vel_y;
		player.collider.y = player.pos_y;
	}

	if( ( player.pos_x < 0 ) || ( player.pos_x + 16 > game_viewport_width)) {
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

	bgtile.rect.x = pos_x * tile_size;
	bgtile.rect.y = pos_y * tile_size;
	bgtile.rect.w = tile_size;
	bgtile.rect.h = tile_size;

	SDL_RenderCopy(renderer, texture_index, NULL, &bgtile.rect); 

	/* COLLISION DETECTION */
	if (map.no_collide == 0) {
		M_PlayerTileCollide(player.collider, bgtile.rect);
	}

}

void M_DrawPortal(int pos_x, int pos_y, int tile_size, char* path) {

	Tile bgtile;

	bgtile.rect.x = pos_x * tile_size;
	bgtile.rect.y = pos_y * tile_size;
	bgtile.rect.w = tile_size;
	bgtile.rect.h = tile_size;

	SDL_RenderCopy(renderer, R_GetMaterial(texturemgr, "glaggle"), NULL, &bgtile.rect); 

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
	/* rectangles of tiled sprites */
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

	/* world text, used for messages and also UI, yes, you can use DS in the UI */
	map.ye = strstr(map.chunk, "/t");
        if (map.ye != NULL) { map.i = 16; return 7; }

	/* auto-dialog */
	map.ye = strstr(map.chunk, "/d");
        if (map.ye != NULL) { map.i = 18; return 8; }


	return 0;

}

int M_InitCMD(FILE* map_file) {

	char *head = strtok(map.chunk, "; ");
	char *initbuf = (char*)malloc(sizeof(char) * 64);
	player.is_alive = false;
	map.is_uielement = false;
	dialog.render_characters = false;
	dialog.current_dialog = NULL;
	UI_dashboard.menu_background = NULL;

	while (head != NULL) {

		if(strstr(head, "MENUMODE") != NULL) { map.is_uielement = true; }
		if(strstr(head, "CREDITMODE") != NULL) { mode = kkui_credit; /* change mode to credits */ }
		if(strstr(head, "RENDERCHARACTERS") != NULL) { dialog.render_characters = true; }
		if(strstr(head, "BACKGROUND:") != NULL) { initbuf = strchr( head, ':' ); initbuf[strcspn(initbuf, "\n")] = 0; UI_dashboard.menu_background = IMG_LoadTexture(renderer, initbuf + 1); printf("%s\n", initbuf + 1); }
		
		if(strstr(head, "MUSIC:") != NULL) { initbuf = strchr( head, ':' ); initbuf[strcspn(initbuf, "\n")] = 0; Mix_HaltMusic(); mixer.music = Mix_LoadMUS(initbuf + 1); printf("%s\n", initbuf + 1); }
		/* NOT VISUAL NOVEL RELATED, NOT USEFUL IN KEKTECH_ZDS */


		//if(strstr(head, "SPAWNPLAYER") != NULL) { player.is_alive = true; }
		//if(strstr(head, "SPAWN_X:") != NULL) { initbuf = strchr( head, ':' ); player.pos_x = atoi(initbuf + 1) * 16; player.collider.x = player.pos_x; }
		//if(strstr(head, "SPAWN_Y:") != NULL) { initbuf = strchr( head, ':' ); player.pos_y = atoi(initbuf + 1) * 16; player.collider.y = player.pos_y; }

		printf("'%s'\n", head);
		head = strtok(NULL, ";");
	}	

	//player.pos_x = file_x * 16;
	//player.pos_y = file_y * 16;
	gamemgr.map_is_initialized = 1;
	free(head);
	return 0;
}

int M_ReadMapFile(const char* map_path, game_texture* texture) {
	currentmgr = texture;
	map_file = fopen(map_path, "r");
	if (map_file == NULL) { snprintf(UI_nsod.crash_logbuffer, 256, "CRITICAL MAP LOADING ERROR\nMAP PATH: %s", map_path); mode = kkui_crash; return 0; }
	map.i = -1;

	/* initialize the char register */
	//char* charrgstr = (char*)malloc(4096 * sizeof(char));
	//char* musptr = (char*)malloc(256 * sizeof(char));

	/* reading the map header */
	if (gamemgr.map_is_initialized == 0) {
		fgets(map.chunk, sizeof(map.chunk), map_file);
		map.ye = strstr(map.chunk, "DSHEADER");
		if (map.ye != NULL ) {
			M_InitCMD(map_file);
		}
	}

	/* check if the player collides with the border of the screen */
	R_DrawBackground();
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
						map.chunk[strcspn(map.chunk, "\n")] = 0;
						M_DrawTile(map.file_x, map.file_y, 16, R_GetMaterial(texturemgr, map.chunk)); 
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
					map.chunk[strcspn(map.chunk, "\n")] = 0;
					M_DrawTileRect(map.file_x, map.file_y, map.rec_x2, map.rec_y2, 16, R_GetMaterial(texturemgr, map.chunk));
					map.i = -1; strcpy(map.ye_rec, "\0"); break;

				/* HELPER NPC SPAWN */
				case 12:
					/* pass on the spritesheet info */
					sscanf(map.chunk, "%d", &map.npc_direct);
					break;
				case 13:
					/* pass on the dialog */
					sscanf(map.chunk, "%s", map.npc_dialog);
					break;
				case 14:
					/* pass on the direction info */
					/* 0 - left
					   1 - right
					   2 - down
					   3 - up */
					map.chunk[strcspn(map.chunk, "\n")] = 0;
					NPC_DrawEntity(R_GetMaterial(texturemgr, map.chunk), map.file_x, map.file_y, map.npc_direct, map.npc_dialog, 0);
					//npc_dialog = NULL;
					map.npc_direct = 0;
//					free(npctex);
					map.i = -1; break;

				/* LEVEL PORTAL */
				case 15:
					sscanf(map.chunk, "%s", map.portptr);
					M_DrawPortal(map.file_x, map.file_y, 16, map.portptr);
					map.i = -1; break;

				/* UI TEXT */
				case 17:
//					sscanf(map.chunk, "%s", charrgstr);
					strcpy(map.charrgstr, map.chunk);
					break;
				case 18:
					ui_rgbcolor textcolor;
					textcolor = UI_RGBColorReturn(map.chunk);
					if (map.is_uielement == false)
						UI_TextLabelEx(map.file_x, map.file_y, textcolor.r, textcolor.g, textcolor.b, map.charrgstr, game_screen_width, false);
					else
						UI_TextLabelEx(map.file_x, map.file_y, textcolor.r, textcolor.g, textcolor.b, map.charrgstr, game_screen_width, true);
					//free(textcolor);
					map.i = -1; break;

				/* AUTO-DIALOG */
				case 19:
					sscanf(map.chunk, "%s", map.npc_dialog);
					if (dialog.current_dialog == NULL)  {
						dialog.current_dialog = map.npc_dialog;
					}
					mode = dialog_mode;
					map.i = -1; break;

			}
			map.i++;
		}
		skip:
			continue;
	}
	//free(map.musptr);
	//free(map.charrgstr);
	fclose(map_file);
	return 0;
}
