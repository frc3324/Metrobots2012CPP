#include "Controller.h"

Controller::Controller( int port ){

	joystick_ = new Joystick( port );
	
	for( int i = 0; i < MAX_NUM_BUTTONS; i++ ){
            
        oldBtnStates[i] = false;
        newBtnStates[i] = false;

        upEventStates[i] = false;
        downEventStates[i] = false;
            
    }

}

void Controller::Update(){

	for( int i = 1; i < MAX_NUM_BUTTONS + 1; i++ ){
            
        newBtnStates[i] = joystick_->GetRawButton(i);
            
        upEventStates[i] = newBtnStates[i] && !oldBtnStates[i];
            
        downEventStates[i] = !newBtnStates[i] && !oldBtnStates[i];
        
        oldBtnStates[i] = newBtnStates[i];

            
    }

}

double Controller::GetAxis( int axis ){

	    return joystick_->GetRawAxis( axis );

}

bool Controller::GetButton( int button ){

	return newBtnStates[ button ];

}

bool Controller::GetButtonDown( int button ){

	return downEventStates[ button ];

}

bool Controller::GetButtonUp( int button ){

	return upEventStates[ button ];

}

Joystick* Controller::GetJoystick(){

	return joystick_;

}








