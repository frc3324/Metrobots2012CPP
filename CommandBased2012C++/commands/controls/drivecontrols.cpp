#include "DriveControls.h"
#include "../../util/gamepad.h"

DriveControls::DriveControls(){

	Requires( drive_ );

}

void DriveControls::Initialize(){

	drive_->autonDrivePid_->Disable();
	drive_->SetPidControl( false );

}

void DriveControls::Execute(){

	drive_->SetTankDrive( oi_->stick1_->GetAxis( GamePad::LEFT_Y ), oi_->stick1_->GetAxis( GamePad::RIGHT_Y ) );

	if( oi_->stick1_->GetButtonDown( GamePad::START ) ){
		drive_->SetPidControl( true );
	}

	if( oi_->stick1_->GetButtonDown( GamePad::BACK ) ){
		drive_->SetPidControl( false );
	}

}

bool DriveControls::IsFinished(){

	return false;

}


