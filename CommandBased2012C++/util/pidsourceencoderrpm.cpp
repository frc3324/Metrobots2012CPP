#include "PidSourceEncoderRpm.h"

PidSourceEncoderRpm::PidSourceEncoderRpm( Encoder *encoder ){

	encoder_ = encoder;

}

double PidSourceEncoderRpm::PIDGet(){

	return 1 / encoder_->GetPeriod();

}
