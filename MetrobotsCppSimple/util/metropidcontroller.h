#ifndef METRO_PID_CONTROLLER_H
#define METRO_PID_CONTROLLER_H

#include "WPILib.h"

class MetroPIDController {

	public:
		enum Modes {
			PID,
			FEED_FORWARD_PID,
			TAKE_BACK_HALF_PID,
			BANG_BANG
		};
		MetroPIDController( double p_, double i_, double d_, Modes mode_, bool isIntegratedOutput_ = false, double period_ = 0.05 );
		~MetroPIDController(){};
		void SetSource( double value );
		double GetOutput();
		void SetSetpoint( double value );
		void SetSetpoint( double value, double ffValue );
		void Enable();
		void Disable();
		bool IsEnabled();
		void Reset();
		
	private:
		void Init( double p_, double i_, double d_, Modes mode_, bool isIntegratedOutput_, double period_ );
		void Run();
		static void CallRun( void *controller );
		
		MetroPIDController::Modes mode;
		bool isIntegratedOutput;
		
		double p;
		double i;
		double d;
		
		double period;
		bool isEnabled;
		
		double source;
		double output;
		double setPoint;
		
		double error;
		double prevError;
		double totalError;
		
		double feedForwardValue;
		
		Notifier *notifier;

};

#endif
