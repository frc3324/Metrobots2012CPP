#ifndef PID_SOURCE_ENCODER_RPM_H
#define PID_SOURCE_ENCODER_RPM_H

#include "WPILib.h"

class PidSourceEncoderRpm : public PIDSource {

	public:
		PidSourceEncoderRpm( Encoder* encoder );
		double PIDGet();
		
	private:
		Encoder *encoder_;

};

#endif
