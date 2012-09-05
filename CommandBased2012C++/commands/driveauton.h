#ifndef DRIVE_AUTON_H
#define DRIVE_AUTON_H

#include "commandbase.h"

class DriveAuton : public CommandBase {

	private:
		double targetDist_;
		double targetAngle_;
		bool isPureTurn_;

	public:
		DriveAuton( double straightPower, double targetAngle, double targetDist, double timeout ); 
		~DriveAuton(){};
		void Initialize(); 
		void Execute();
		bool IsFinished(); 
		void End();
		void Interrupted();

};
#endif
