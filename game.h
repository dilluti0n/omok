#ifndef GAME_H
#define GAME_H

struct game_context {
	int pind;
	int xpos;
	int ypos;
	unsigned int flag;
};

#define GC_FLAG_CANNOT_PLACE 1
#define GC_FLAG_ISMOVED 2

#define GC_CANNOT_PLACE(gcflag) ((gcflag) & GC_FLAG_CANNOT_PLACE)
#define GC_ISMOVED(gcflag) ((gcflag) & GC_FLAG_ISMOVED)

void game_init();
void game_start();
void game_turn();
int game_iswin(struct game_context *context);
void game_win(struct game_context *context);
void game_finish(int exitcode);

#endif
