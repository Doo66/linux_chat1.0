#include "window.h"
#include "udp_data.h"
#include <pthread.h>
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
chat_window::chat_window()
{
	header = NULL;
	output = NULL;
	list   = NULL;
	input  = NULL;
//	WINDOW* win=newwin(50, 40, 1, 1);
//	box(win, '+', '-');
//	wrefresh(win);
}

void chat_window::init()
{
	initscr();
}

WINDOW *chat_window::create_win(int hei, int wth, int y, int x)
{
	pthread_mutex_lock(&mutex);
	WINDOW *_win = newwin(hei, wth, y, x);
	pthread_mutex_unlock(&mutex);
	return _win;
}

void chat_window::put_str_to_win(WINDOW *_win, int _y, int _x, const std::string &_str)
{
	pthread_mutex_lock(&mutex);
	mvwaddstr(_win, _y, _x, _str.c_str());
	pthread_mutex_unlock(&mutex);
}

void chat_window::get_str_to_win(WINDOW *_win, std::string &_msg)
{
	char buf[BUF_SIZE];
	memset(buf, '\0', sizeof(buf));
	wgetnstr(_win, buf, sizeof(buf));
	_msg = buf;
}

void chat_window::draw_header()
{
	//COLS/LINES
	int hei = LINES/5;
	int wth = COLS;
	int y   = 0;
	int x   = 0;
	this->header = create_win(hei, wth, y, x);
}

void chat_window::win_refresh(WINDOW* _win)
{
	pthread_mutex_lock(&mutex);
	box(_win, 0, 0);
	wrefresh(_win);
	pthread_mutex_unlock(&mutex);
}

void chat_window::clear_win_line(WINDOW *_win, int begin, int num)
{
	pthread_mutex_lock(&mutex);
	while( num-- > 0 ){
		wmove(_win, begin++, 0);
		wclrtoeol(_win);
	}
	pthread_mutex_unlock(&mutex);
}

void chat_window::draw_output()
{
	//COLS/LINES
	int hei = (LINES*3)/5;
	int wth = (COLS*3)/4;

	int y   = LINES/5;
	int x   = 0;
	this->output = create_win(hei, wth, y, x);
}

void chat_window::draw_list()
{
	//COLS/LINES
	int hei = LINES*3/5;
	int wth = COLS/4;

	int y   = LINES/5;
	int x   = COLS*3/4;
	this->list = create_win(hei, wth, y, x);
}

void chat_window::draw_input()
{
	//COLS/LINES
	int hei = LINES/5;
	int wth = COLS;
	int y   = 4*LINES/5;
	int x   = 0;
	this->input = create_win(hei, wth, y, x);
}

chat_window::~chat_window()
{
	delwin(this->header);
	delwin(this->output);
	delwin(this->list);
	delwin(this->input);
	endwin();
}

