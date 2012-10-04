#ifndef DRIVE_H
#define DRIVE_H

#include "WPILib.h"
#include <Math.h>
#include "util/metropidcontroller.h"

class Drive {

	public:
		Drive( Victor *flMotor_, Victor *blMotor_, Victor *frMotor_, Victor *brMotor_, 
				Encoder *flEncoder_, Encoder *blEncoder_, Encoder *frEncoder_, Encoder *brEncoder_, 
				Gyro *gyro_ );
		~Drive(){};
		void Actuate();
		void Disable();
		void SetTankDrive( double leftSide, double rightSide );
		void SetArcadeDrive( double straight, double turn );
		void SetMetroDrive( double straight, double turn );
		void SetCheesyDrive( double straight, double turn, bool quickTurn );
		void SetMecanumXYTurn( double x, double y, double turn );
		void SetMecanumRLStrafe( double leftSide, double rightSide, double strafe );
		void SetMecanumFieldOriented( double x, double y, double turn );
		void EnableAutonDrive( double straightPower, double targetAngle );
		void DisableAutonDrive();
		double GetDistMoved();
		void ResetEncoders();
		void ResetGyro();
		double GetGyroAngle();
		void SetPIDControl( bool value );
		bool IsPIDControl();
		void SetReversedFront( bool value );
		bool IsReversedFront();
		bool IsSlowDrive();
		void SetSlowDrive( bool value );
		void SetInvertedMotors( bool fl, bool bl, bool fr, bool br );
		
		static const double PID_P = 1.0;
		static const double PID_I = 0.0;
		static const double PID_D = 1.0;
		static const double VEL_PID_MULTIPLIER = 1600;

		static const double ANGLE_PID_P = 0.0;
		static const double ANGLE_PID_I = 0.0;
		static const double ANGLE_PID_D = 0.0;
		
		static const double SLOW_DRIVE_MULTIPLIER = 0.4;
			
	private:
		void NormalizeMotorSpeeds();
		double SquareAndPreserveSign( double input );
	
		Victor *flMotor, *blMotor, *frMotor, *brMotor;
		Encoder *flEncoder, *blEncoder, *frEncoder, *brEncoder;
		Gyro *gyro;
		MetroPIDController *flPID, *blPID, *frPID, *brPID, *autonPID;
		
		double flSpeed, blSpeed, frSpeed, brSpeed;
		int motorInverters[4];
		double autonDriveStraightPower;
		
		bool isPIDControl;
		bool isSlowDrive;
		bool isReversedFront;
		bool isAutonDrive;

};

#endif
