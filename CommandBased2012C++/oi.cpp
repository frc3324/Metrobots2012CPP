#include "OI.h"

OI::OI( Controller* stick1, Controller* stick2 ){

	stick1_ = stick1;
	stick2_ = stick1;

}

void OI::Update(){

	stick1_->Update();
	stick2_->Update();

}
