#ifndef INPUT_H_INCLUDED
#define INPUT_H_INCLUDED

void I_ProcessKeyDownEvent();
void I_ProcessPauseEvent();
void I_ProcessKeyUpEvent();
int I_ProcessMouseButtonDownEvent(int button);
int I_ProcessMouseButtonUpEvent(int button);
bool I_ProcessInput(int key_code);

struct mouseoffset {

	int x;
	int y;

} extern global_offset;

struct mousemasks_pressed {

	bool mouse_left;
	bool mouse_right;

} extern global_mousemasks_pressed;

struct mousemasks_released {

	bool mouse_left;
	bool mouse_right;

} extern global_mousemasks_released;

mouseoffset I_GetMouseOffsets(int x, int y);

/* EVENT SHIT */
extern SDL_Event e;

/* TEXTBOX WIDGET INPUT BUFFER */
extern std::string textbox_input;

#endif // INPUT_H_INCLUDED 
