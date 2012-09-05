#ifndef DRIVE_CONTROLS_H
#define DRIVE_CONTROLS_H

#include "../commandbase.h"

class DriveControls : public CommandBase {

	public:
		DriveControls();
		~DriveControls();
		void Initialize(); 
		void Execute();
		bool IsFinished(); 
		void End();
		void Interrupted();

};
#endif
