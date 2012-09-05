#ifndef METROBOT_H
#define METROBOT_H

#include "WPILib/WPILib.h"

#include "oi.h"

#include "commands/commandbase.h"
#include "commands/driveauton.h"
#include "commands/controls/drivecontrols.h"
#include "commands/donothing/drivedonothing.h"

#include "subsystems/drive.h"

#include "util/controller.h"
#include "util/gamepad.h"
#include "util/atkjoystick.h"
#include "util/pidintegratedoutputvictor.h"
#include "util/pidsourceencoderrpm.h"

class Metrobot : public IterativeRobot{

	public:
		Metrobot();
		~Metrobot(){};
		void RobotInit();
		void AutonomousInit();
		void AutonomousPeriodic();
		void AutonomousContinuous();
		void TeleopInit();
		void TeleopPeriodic();
		void TeleopContinuous();
		void DisabledInit();
		void DisabledPeriodic();
		void DisabledContinuous();
		
		void Actuate();
		void SetDefaultsDoNothing();
		void SetDefaultsControls();
		
		static const int AUTON_SCRIPT_NONE = 0;
		static const int AUTON_SCRIPT_1 = 1;
		static const int AUTON_SCRIPT_2 = 2;
		
	private: 
		Victor *driveFlMotor_, *driveBlMotor_, *driveFrMotor_, *driveBrMotor_;
  		Gyro *driveGyro_;
  		Encoder *driveFlEncoder_, *driveBlEncoder_, *driveFrEncoder_, *driveBrEncoder_;
  		
  		Drive *drive_;
  		
  		Controller *stick1_, *stick2_;
  		OI *oi_;
  		
  		Command *autonCommand_;
  		int autonScript;
  		
  		DriverStationLCD *ds_;

};

#endif
