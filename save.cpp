#include "libs.h"

#include "save.h"

int SAVE_InitSaveOperation() {

	return 0;

}

int SAVE_WriteKeyToFile(const char* identifier, const char* value) {

	save_file SAVE_file;

	// Open a file in writing mode
	SAVE_file.save_ptr = fopen("save/save1.ds", "w");

	// Write some text to the file
	fprintf(SAVE_file.save_ptr, "%s:%s;\n", identifier, value);

	// Close the file
	fclose(SAVE_file.save_ptr);

	//free(SAVE_file);
	return 0;

}

char* SAVE_ReadKeyFromFile() {

	save_file SAVE_file;

	// Open a file in writing mode
	SAVE_file.save_ptr = fopen("save/save1.ds", "r");
	SAVE_file.charrgstr = (char*)malloc(sizeof(char) * 32);
	char charbuf[128] = "\0";

	while(fgets(SAVE_file.charrgstr, 32, SAVE_file.save_ptr) != NULL) {

		printf("KEKTECH SAVE FILE READ TEST: %s\n", SAVE_file.charrgstr);

		char *head = strtok(SAVE_file.charrgstr, ":;");

		while (head != NULL) {
			printf("%s\n", head);
			head = strtok(NULL, ":;");
		}	

		strcat(charbuf, SAVE_file.charrgstr);

	}


	printf("KEKTECH SAVE FILE READ TEST FINALE LOLOLO: %s\n", charbuf);
	// Close the file
	fclose(SAVE_file.save_ptr);
	free(SAVE_file.charrgstr);

	return charbuf;

}
