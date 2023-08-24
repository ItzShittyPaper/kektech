/* THE SAVE SYSTEM SHARED VARIABLES */
#ifndef SAVE_H_INCLUDED
#define SAVE_H_INCLUDED

struct save_file {

	FILE* save_ptr;
	char* charrgstr;

};

int SAVE_InitSaveOperation();
int SAVE_WriteKeyToFile(const char* identifier, const char* value);
char* SAVE_ReadKeyFromFile();

#endif // SAVE_H_INCLUDED 
