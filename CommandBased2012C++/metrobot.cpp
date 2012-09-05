#include "Metrobot.h"

/*
 *All hardware initialization goes here (anything with at port number)
 *Victors, Jaguars, sensors, joysticks, etc
 *
 *Wiring ports can be changed here and will be affected throughout the program
 */
Metrobot::Metrobot(){

	driveFlMotor_ = new Victor( 1 );
	driveFrMotor_ = new Victor( 3 );
	driveBrMotor_ = new Victor( 4 );
	
	driveGyro_ = new Gyro( 1 );
		
	driveFlEncoder_ = new Encoder( 1, 2 );
	driveBlEncoder_ = new Encoder( 3, 4 );
	driveFrEncoder_ = new Encoder( 5, 6 );
	driveBrEncoder_ = new Encoder( 7, 8 );
		
	stick1_ = new GamePad( 1 );
	stick2_ = new AtkJoystick( 2 );
		
}
	
void Metrobot::RobotInit(){
	
	ds_ = DriverStationLCD::GetInstance();
	
	drive_ = new Drive( driveFlMotor_,  driveBlMotor_,  driveFrMotor_,  driveBrMotor_, driveGyro_, 
							driveFlEncoder_, driveBlEncoder_, driveFrEncoder_, driveBrEncoder_ );
	oi_ = new OI( stick1_, stick2_ );

	CommandBase::Init( drive_, oi_ );
	
	autonScript = Metrobot::AUTON_SCRIPT_NONE;
	
}
	
void Metrobot::AutonomousInit(){
	
	SetDefaultsDoNothing();
	
	CommandGroup *group = new CommandGroup();
	
	switch ( autonScript ){
	
		case AUTON_SCRIPT_NONE:
			break;
			
		case AUTON_SCRIPT_1:
			/*Insert code here.  Example: */
			group->AddSequential( new DriveAuton( 0.4, 0.0, 200, 2.0 ) );
			group->AddSequential( new DriveAuton( 0.0, 90.0, 0.0, 2.0 ) );
			group->AddSequential( new DriveAuton( -0.4, 0.0, -200, 2.0 ) );
			break;
			
		case AUTON_SCRIPT_2:
			break;
	
	}
	
	autonCommand_ = group;
	autonCommand_->Start();
	
}
	
void Metrobot::AutonomousPeriodic(){
	
	Scheduler::GetInstance()->Run();
	Actuate();
	
	ds_->Clear();
	ds_->Printf(DriverStationLCD::kUser_Line1, 1, "Autonomous" );
	ds_->Printf(DriverStationLCD::kUser_Line2, 1, "Script: %s", autonScript == Metrobot::AUTON_SCRIPT_NONE ? "None" : ( autonScript == AUTON_SCRIPT_1 ? "script1" : "script2" ) );
	ds_->Printf(DriverStationLCD::kUser_Line3, 1, "" );
	ds_->Printf(DriverStationLCD::kUser_Line4, 1, "" );
	ds_->Printf(DriverStationLCD::kUser_Line5, 1, "" );
	ds_->Printf(DriverStationLCD::kUser_Line6, 1, "" );
	ds_->UpdateLCD();

}
	
	
void Metrobot::TeleopInit(){
	
	autonCommand_->Cancel();
	SetDefaultsControls();
	
}
	
void Metrobot::TeleopPeriodic(){
	
	Scheduler::GetInstance()->Run();
	Actuate();
	
	ds_->Clear();
	ds_->Printf(DriverStationLCD::kUser_Line1, 1, "Tele-op" );
	ds_->Printf(DriverStationLCD::kUser_Line2, 1, "" );
	ds_->Printf(DriverStationLCD::kUser_Line3, 1, "" );
	ds_->Printf(DriverStationLCD::kUser_Line4, 1, "" );
	ds_->Printf(DriverStationLCD::kUser_Line5, 1, "" );
	ds_->Printf(DriverStationLCD::kUser_Line6, 1, "" );
	ds_->UpdateLCD();
	
}
	
	
void Metrobot::DisabledInit(){
	
	autonCommand_->Cancel();
	SetDefaultsDoNothing();

}
	
void Metrobot::DisabledPeriodic(){
	
	Scheduler::GetInstance()->Run();	
	oi_->Update();
	
	//Sets autonScript
	if( oi_->stick1_->GetButton( 4 ) ){
		autonScript = AUTON_SCRIPT_NONE;
	}
	if( oi_->stick1_->GetButton( 2 ) ){
		autonScript = AUTON_SCRIPT_1;
	}
	if( oi_->stick1_->GetButton( 5 ) ){
		autonScript = AUTON_SCRIPT_2;
	}
	
	ds_->Clear();
	ds_->Printf(DriverStationLCD::kUser_Line1, 1, "Disabled" );
	ds_->Printf(DriverStationLCD::kUser_Line2, 1, "autonScript: %s", autonScript == AUTON_SCRIPT_NONE ? "None" : ( autonScript == AUTON_SCRIPT_1 ? "script1" : "script2" ) );
	ds_->Printf(DriverStationLCD::kUser_Line3, 1, "" );
	ds_->Printf(DriverStationLCD::kUser_Line4, 1, "" );
	ds_->Printf(DriverStationLCD::kUser_Line5, 1, "" );
	ds_->Printf(DriverStationLCD::kUser_Line6, 1, "" );
	ds_->UpdateLCD();
	
}
	
void Metrobot::AutonomousContinuous(){ Wait( 0.020 ); }
void Metrobot::TeleopContinuous(){ Wait( 0.020 ); }
void Metrobot::DisabledContinuous(){ Wait( 0.020 ); }
	
void Metrobot::Actuate(){
	
	drive_->Actuate();
	oi_->Update();
	
}
	
void Metrobot::SetDefaultsDoNothing(){
	
	drive_->SetNewDefaultCommand( new DriveDoNothing() );
	
}
	
void Metrobot::SetDefaultsControls(){
	
	drive_->SetNewDefaultCommand( new DriveControls() );
	
}

START_ROBOT_CLASS( Metrobot );
