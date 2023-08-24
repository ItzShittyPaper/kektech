void I_ProcessKeyDownEvent();
void I_ProcessPauseEvent();
void I_ProcessKeyUpEvent();
bool I_ProcessInput(int key_code);

/* EVENT SHIT */
extern SDL_Event e;

/* TEXTBOX WIDGET INPUT BUFFER */
extern std::string textbox_input;

