#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "WPILib.h"

#define MAX_NUM_BUTTONS 12

class Controller{

	protected: 
		
		Joystick *joystick_;
		
		bool oldBtnStates[ MAX_NUM_BUTTONS ];
    	bool newBtnStates[ MAX_NUM_BUTTONS ];
    	bool upEventStates[ MAX_NUM_BUTTONS ];
    	bool downEventStates[ MAX_NUM_BUTTONS ];

	public:
		Controller( int port );
		void Update();
		virtual double GetAxis( int axis );
		bool GetButton( int button );
		bool GetButtonDown( int button );
		bool GetButtonUp( int button );
		Joystick* GetJoystick();

};
#endif
