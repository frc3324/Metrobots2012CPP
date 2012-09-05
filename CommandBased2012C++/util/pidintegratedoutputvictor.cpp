#include "pidintegratedoutputvictor.h"

PidIntegratedOutputVictor::PidIntegratedOutputVictor( Victor *motor ){

	motor_ = motor;

}

void PidIntegratedOutputVictor::PIDWrite( float output ){

	motor_->Set( motor_->Get() + output );

}
