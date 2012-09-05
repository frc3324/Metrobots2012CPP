#ifndef GAME_PAD_H
#define GAME_PAD_H

#include "controller.h"

class GamePad : public Controller{

	public:
		GamePad( int port ) : Controller::Controller( port ){};
		double GetAxis( int axis );

		static const int A = 1;
		static const int B = 2;
		static const int X = 3;
		static const int Y = 4;
		static const int LB = 5;
		static const int RB = 6;
		static const int BACK = 7;
		static const int START = 8;
		static const int LEFT_JS = 9;
		static const int RIGHT_JS = 10;
		
		static const int LEFT_X = 1;
		static const int LEFT_Y = 2;
		static const int TRIGGER = 3;
		static const int RIGHT_X = 4;
		static const int RIGHT_Y = 5;
		static const int DPAD_X = 6;
		static const int DPAD_Y = 7;

};

#endif
