#include "GamePad.h"

double GamePad::GetAxis( int axis ){

	if( axis == GamePad::LEFT_X || axis == GamePad::RIGHT_X ){

	    return joystick_->GetRawAxis( axis );

    }
    else{

        return -joystick_->GetRawAxis( axis );

    }

}








