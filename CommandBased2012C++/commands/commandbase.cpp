#include "CommandBase.h"

CommandBase::CommandBase() : Command(){}

CommandBase::CommandBase( const char *name ) : Command( name ){}

Drive* CommandBase::drive_ = NULL;
OI* CommandBase::oi_ = NULL;

void CommandBase::Init( Drive* drive, OI* oi ){

	drive_ = drive;
	oi_ = oi;

}
