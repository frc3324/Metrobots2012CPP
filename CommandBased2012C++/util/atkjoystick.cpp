#include "AtkJoystick.h"

double AtkJoystick::GetAxis( int axis ){

	if( axis == AtkJoystick::X ){

            return joystick_->GetRawAxis( axis );

        }
        else{

            return -joystick_->GetRawAxis( axis );

        }  

}
