#ifndef PID_INTEGRATED_OUTPUT_VICTOR_H
#define PID_INTEGRATED_OUTPUT_VICTOR_H

#include "WPILib.h"

class PidIntegratedOutputVictor : public PIDOutput {

	public:
		PidIntegratedOutputVictor( Victor *motor );
		void PIDWrite( float output );
		
	private:
		Victor *motor_;

};
#endif
