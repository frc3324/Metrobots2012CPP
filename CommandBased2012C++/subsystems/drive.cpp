#include "Drive.h"
#include <Math.h>

Drive::Drive( Victor* flMotor, Victor* blMotor, Victor* frMotor, Victor* brMotor, Gyro* gyro, 
				Encoder* flEncoder, Encoder* blEncoder, Encoder* frEncoder, Encoder* brEncoder ) : Subsystem("Drive"){

	flMotor_ = flMotor;
	blMotor_ = blMotor;
	frMotor_ = frMotor;
	brMotor_ = brMotor;
	
	motorInverters_[0] = 1;
	motorInverters_[1] = 1;
	motorInverters_[2] = 1;
	motorInverters_[3] = 1;
	
	gyro_ = gyro;
	gyro_->Reset();
	
	flEncoder_ = flEncoder;
	blEncoder_ = blEncoder;
	frEncoder_ = frEncoder;
	brEncoder_ = brEncoder;
	
	initialEncoderValues_[0] = flEncoder_->Get();
	initialEncoderValues_[1] = blEncoder_->Get();
	initialEncoderValues_[2] = frEncoder_->Get();
	initialEncoderValues_[3] = brEncoder_->Get();
	
	flSpeed_ = 0.0;
	blSpeed_ = 0.0;
	frSpeed_ = 0.0;
	brSpeed_ = 0.0;

	flPid_ = new PIDController( Drive::PID_P, Drive::PID_I, Drive::PID_D, ( new PidSourceEncoderRpm( flEncoder_ ) ), ( new PidIntegratedOutputVictor( flMotor_ ) ) );
	blPid_ = new PIDController( Drive::PID_P, Drive::PID_I, Drive::PID_D, ( new PidSourceEncoderRpm( blEncoder_ ) ), ( new PidIntegratedOutputVictor( blMotor_ ) ) );
	frPid_ = new PIDController( Drive::PID_P, Drive::PID_I, Drive::PID_D, ( new PidSourceEncoderRpm( frEncoder_ ) ), ( new PidIntegratedOutputVictor( frMotor_ ) ) );
	brPid_ = new PIDController( Drive::PID_P, Drive::PID_I, Drive::PID_D, ( new PidSourceEncoderRpm( brEncoder_ ) ), ( new PidIntegratedOutputVictor( brMotor_ ) ) );
	
	autonDrivePid_ = new PIDController( Drive::PID_P, Drive::PID_I, Drive::PID_D, (gyro_), (this) );
	
	flPid_->Disable();
	blPid_->Disable();
	frPid_->Disable();
	brPid_->Disable();
	
	autonDrivePid_->Disable();
	
	autonDriveStraightPower_ = 0.0;

	isPidControl_ = false;

}

void Drive::SetTankDrive( double leftSide, double rightSide ){

	flSpeed_ = leftSide;
	blSpeed_ = leftSide;
	frSpeed_ = rightSide;
	brSpeed_ = rightSide;
	
}

void Drive::SetArcadeDrive( double straight, double turn ){

	flSpeed_ = straight + turn;
	blSpeed_ = straight + turn;
	frSpeed_ = straight - turn;
	brSpeed_ = straight - turn;
	
}

void Drive::SetMecanumXYTurn( double x, double y, double turn ){

	flSpeed_ = y + x + turn;
	blSpeed_ = y - x + turn;
	frSpeed_ = y - x - turn;
	brSpeed_ = y + x - turn;

}

void Drive::SetMecanumRLStrafe( double r, double l, double strafe ){

	flSpeed_ = l + strafe;
	blSpeed_ = l - strafe;
	frSpeed_ = r - strafe;
	brSpeed_ = r + strafe;

}

void Drive::SetMecanumFieldOriented( double x, double y, double turn ){
        
        double joystickAngle = ( atan( y / x ) ) * 180 / 3.14159;
        double radius = sqrt( x * x + y * y );
        
        double angle = ( joystickAngle - GetGyroAngle() ) * 3.14159 / 180;
        
        double outputX = cos( angle ) * radius;
        double outputY = sin( angle ) * radius;
        
        SetMecanumXYTurn( outputX, outputY, turn );
        
}

void Drive::SetPidControl( bool isPidControl ){

	isPidControl_ = isPidControl;

	if( isPidControl_ ){
		flPid_->Enable();
		blPid_->Enable();
		frPid_->Enable();
		brPid_->Enable();
	}
	else{
		flPid_->Disable();
		blPid_->Disable();
		frPid_->Disable();
		brPid_->Disable();
	}

}

bool Drive::IsPidControl(){
	return isPidControl_;
}

void Drive::SetInvertedMotors( bool flInverter, bool blInverter, bool frInverter, bool brInverter ){

	motorInverters_[0] = flInverter ? -1 : 1;
	motorInverters_[1] = blInverter ? -1 : 1;
	motorInverters_[2] = frInverter ? -1 : 1;
	motorInverters_[3] = brInverter ? -1 : 1;

}

void Drive::ResetInitialEncoderValues(){

	initialEncoderValues_[0] = flEncoder_->Get();
	initialEncoderValues_[1] = blEncoder_->Get();
	initialEncoderValues_[2] = frEncoder_->Get();
	initialEncoderValues_[3] = brEncoder_->Get();

}

double Drive::GetDistMoved(){

	double output = flEncoder_->Get() + blEncoder_->Get() + frEncoder_->Get() + brEncoder_->Get();
	
	for( int i = 0; i < 4; i++ ){
		output -= initialEncoderValues_[i];
	}
	
	return output / 4;

}

double Drive::GetGyroAngle(){

	return gyro_->GetAngle();

}

void Drive::Actuate(){

	if( isPidControl_ ){
	
		flPid_->SetSetpoint( flSpeed_ * VEL_PID_MULTIPLIER );
		blPid_->SetSetpoint( blSpeed_ * VEL_PID_MULTIPLIER );
		frPid_->SetSetpoint( frSpeed_ * VEL_PID_MULTIPLIER );
		brPid_->SetSetpoint( brSpeed_ * VEL_PID_MULTIPLIER );
	
	}
	else{
	
		flMotor_->Set( flSpeed_ );
		blMotor_->Set( blSpeed_ );
		frMotor_->Set( frSpeed_ );
		brMotor_->Set( brSpeed_ );
	
	}

}

void Drive::PIDWrite( float output ){

	SetArcadeDrive( autonDriveStraightPower_, output );

}

void Drive::InitDefaultCommand(){
	
	SetDefaultCommand( NULL );
	
}

void Drive::SetNewDefaultCommand( Command* c ){
	
	SetDefaultCommand( c );
	
}
