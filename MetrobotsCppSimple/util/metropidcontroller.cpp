#include "metropidcontroller.h"

MetroPIDController::MetroPIDController( double p_, double i_, double d_, Modes mode_, bool isIntegratedOutput_, double period_ ){

	p = p_;
	i = i_;
	d = d_;
	
	mode = mode_;
	isIntegratedOutput = isIntegratedOutput_;
	period = period_;
	
	notifier = new Notifier( MetroPIDController::CallRun , this );
		
	source = 0.0;
	result = 0.0;
	output = 0.0;
	setPoint = 0.0;
	
	error = 0.0;
	prevError = 0.0;
	totalError = 0.0;
	feedForwardValue = 0.0;

	isEnabled = false;

	notifier->StartPeriodic( period );

}

void MetroPIDController::CallRun( void *controller ){

	MetroPIDController *control = (MetroPIDController*) controller;
	control->Run();
	
}

void MetroPIDController::Run(){

	Synchronized s(semaphore);
	
	if( isEnabled ){
	
		error = setPoint - source;
		totalError += error;
		
		if ( mode == TAKE_BACK_HALF_PID && ( error * prevError < 0 || error == 0 ) ) {
                
            feedForwardValue = ( feedForwardValue + output ) / 2;
                
        }

        result = ( error * p ) + ( totalError * i ) + ( (error-prevError) * d ) + ( isIntegratedOutput ? output : 0.0 );
            
    	output = result;
            
        if ( mode == FEED_FORWARD_PID || mode == TAKE_BACK_HALF_PID ) {
                
            output += feedForwardValue;
                
        }
            
        if( mode == BANG_BANG ){
                
            output = ( source < setPoint ? 1.0 : 0.0 );
                
        }
		
		prevError = error;
	
	}

}

void MetroPIDController::SetSource( double value ){

	Synchronized s(semaphore);
	source = value;

}

double MetroPIDController::GetOutput(){

	Synchronized s(semaphore);
	return output;

}

void MetroPIDController::SetSetpoint( double value ){

	Synchronized s(semaphore);
	setPoint = value;

}

void MetroPIDController::SetSetpoint( double value, double ffValue ){

	Synchronized s(semaphore);
	setPoint = value;
	feedForwardValue = ffValue;

}

bool MetroPIDController::IsEnabled(){

	Synchronized s(semaphore);
	return isEnabled;

}

void MetroPIDController::Enable(){

	Synchronized s(semaphore);
	isEnabled = true;

}

void MetroPIDController::Disable(){

	Synchronized s(semaphore);
	output = 0.0;
	isEnabled = false;

}

void MetroPIDController::Reset(){

	Synchronized s(semaphore);
	output = 0.0;
	prevError = 0.0;
	totalError = 0.0;
	setPoint = 0.0;
	isEnabled = false;

}
