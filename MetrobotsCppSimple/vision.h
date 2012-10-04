#ifndef VISION_H
#define VISION_H

#include "WPILib.h"
#include <Math.h>
#include <nivision.h>
#include <Vision/RGBImage.h>
#include <Vision/AxisCamera.h>

class Vision {
	
	public:
		static Vision *GetInstance();
		void Enable();
		void Disable();
		double GetOutput();
		bool IsEnabled();
		void Process();
		
		static const double PERIOD = 0.2;
		static const double MIN_WAIT = 0.005;
	
	private:		
		Vision();
		static Vision *instance;
		AxisCamera *camera;
		double output;
		bool isEnabled;
				
		void SetOutput( double value );
	
};

#endif
