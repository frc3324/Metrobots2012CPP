#ifndef OI_H
#define OI_H

#include "util/controller.h"

class OI{

	public:
		Controller *stick1_;
		Controller *stick2_;
		
		OI( Controller* stick1, Controller* stick2 );
		~OI(){};
		void Update();
		
};
#endif
