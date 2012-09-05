#include "DriveDoNothing.h"

DriveDoNothing::DriveDoNothing(){

	Requires( drive_ );

}

void DriveDoNothing::Initialize(){

	drive_->SetPidControl( false );
	drive_->autonDrivePid_->Disable();
	
	drive_->SetTankDrive( 0.0, 0.0 );

}

bool DriveDoNothing::IsFinished(){

	return false;

}
