#ifndef COMMAND_BASE_H
#define COMMAND_BASE_H

#include "WPILib.h"
#include "../oi.h"
#include "../subsystems/drive.h"

class CommandBase : public Command {
  public:
	CommandBase(const char *name);
	CommandBase();
	~CommandBase();
	
	static Drive *drive_;
	static OI *oi_;
	
	static void Init( Drive* drive, OI* oi );
	
};
#endif
