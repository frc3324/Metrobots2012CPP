#ifndef DRIVE_H
#define DRIVE_H

#include <Math.h>
#include "WPILib.h"
#include "../util/pidintegratedoutputvictor.h"
#include "../util/pidsourceencoderrpm.h"

class Drive : public Subsystem, public PIDOutput {

  	public:
		Drive( Victor* flMotor, Victor* blMotor, Victor* frMotor, Victor* brMotor, Gyro* gyro, 
				Encoder* flEncoder, Encoder* blEncoder, Encoder* frEncoder, Encoder* brEncoder );
		~Drive(){};
		void SetTankDrive( double leftSide, double rightSide );
		void SetArcadeDrive( double straight, double turn );
		void SetMecanumXYTurn( double x, double y, double turn );
		void SetMecanumRLStrafe( double r, double l, double strafe );
		void SetMecanumFieldOriented( double x, double y, double turn );
		
		void SetPidControl( bool isPidControl );
		bool IsPidControl();
		
		void SetInvertedMotors( bool flInverter, bool blInverter, bool frInverter, bool brInverter );
		void ResetInitialEncoderValues();
		double GetDistMoved();
		double GetGyroAngle();
		
		void Actuate();
		void PIDWrite( float output );
		
		void InitDefaultCommand();
		void SetNewDefaultCommand( Command* c );
		
		double autonDriveStraightPower_;
		PIDController *autonDrivePid_;
		
		static const double PID_P = 1.0;
		static const double PID_I = 0.0;
		static const double PID_D = 1.0;
		static const double VEL_PID_MULTIPLIER = 1600;
		
		static const double ANGLE_PID_P = 0.0;
		static const double ANGLE_PID_I = 0.0;
		static const double ANGLE_PID_D = 0.0;
		
  private:
  
  	Victor *flMotor_, *blMotor_, *frMotor_, *brMotor_;
  	Gyro *gyro_;
  	Encoder *flEncoder_, *blEncoder_, *frEncoder_, *brEncoder_;
  	
  	PIDController *flPid_, *blPid_, *frPid_, *brPid_;
  	
  	double flSpeed_, blSpeed_, frSpeed_, brSpeed_;
  	
  	int motorInverters_ [4];
  	int initialEncoderValues_ [4];
  	
  	bool isPidControl_;

};

#endif
