#ifndef DRIVE_DO_NOTHING_H
#define DRIVE_DO_NOTHING_H

#include "../commandbase.h"

class DriveDoNothing : public CommandBase {

	public:
		DriveDoNothing(); 
		~DriveDoNothing(){};
		void Initialize(); 
		void Execute();
		bool IsFinished(); 
		void End();
		void Interrupted();

};

#endif
