#include "DriveAuton.h"
#include <Math.h>

DriveAuton::DriveAuton( double straightPower, double targetAngle, double targetDist, double timeout ){

	Requires( drive_ );
	
	if( timeout != 0.0 ){
		SetTimeout( timeout );
	}
	
	drive_->autonDriveStraightPower_ = straightPower;
	drive_->autonDrivePid_->SetSetpoint( targetAngle );
	drive_->ResetInitialEncoderValues();
	targetDist_ = targetDist;
	targetAngle_ = targetAngle;
	isPureTurn_ = ( straightPower == 0.0 ) ? true : false;

}

bool DriveAuton::IsFinished(){

	if( isPureTurn_ ){
		
		if( drive_->GetGyroAngle() - targetAngle_ > 0 ){
			
			return ( drive_->GetGyroAngle() - targetAngle_ < 1.0 ) ? true : false;
			
		}
		else{
			
			return ( drive_->GetGyroAngle() - targetAngle_ > -1.0 ) ? true : false;
			
		}
	
	}
	else{
	
		if( targetDist_ > 0 ){
		
			return ( drive_->GetDistMoved() >= targetDist_ ) ? true : false;
		
		}
		else{
		
			return ( drive_->GetDistMoved() <= targetDist_ ) ? true : false;
			
		}
	
	}

}

void DriveAuton::End(){

	drive_->autonDrivePid_->Disable();

}

void DriveAuton::Interrupted(){

	drive_->autonDrivePid_->Disable();

}
