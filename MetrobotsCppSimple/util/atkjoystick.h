#ifndef ATK_JOYSTICK_H
#define ATK_JOYSTICK_H

#include "controller.h"

class AtkJoystick : public Controller{

	public:
		AtkJoystick( int port ) : Controller::Controller( port ){};
		double GetAxis( int Axis );
		
		static const int X = 1;
		static const int Y = 2;
		static const int THROTTLE = 3;

};

#endif
