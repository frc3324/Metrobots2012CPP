#include "vision.h"

int ProcessingLoop();
Task processingTask( "processingTask", (FUNCPTR) ProcessingLoop );

Vision::Vision(){
	
	camera = &AxisCamera::GetInstance("10.33.24.11");
	camera->WriteResolution(AxisCamera::kResolution_320x240);
	camera->WriteMaxFPS(6);
	
	isEnabled = false;
	
	processingTask.Stop();
		
}

Vision* Vision::GetInstance(){
	
	if( Vision::instance == NULL ){
		
		Vision::instance = new Vision();
		
	}
	
	return Vision::instance;
	
}

double Vision::GetOutput(){
	
	Synchronized s(semaphore);
	return output;
	
}

void Vision::SetOutput( double value ){
	
	Synchronized s(semaphore);
	output = value;
	
}

bool Vision::IsEnabled(){
	
	Synchronized s(semaphore);
	return isEnabled;
	
}

void Vision::Enable(){
	
	Synchronized s(semaphore);
	isEnabled = true;
	processingTask.Start();
	
}

void Vision::Disable(){
	
	Synchronized s(semaphore);
	isEnabled = false;
	processingTask.Stop();
	
}

void Vision::Process(){
	
	if( camera->IsFreshImage() ){
		
		/*
		 * Put image processing code here
		 */
		
	}

}

int ProcessingLoop(){
	
	Timer *timer;
	timer->Start();
	
	Vision *vision = Vision::GetInstance();
	
	while( true ){
		
		timer->Reset();
		vision->Process();
		Wait( max( Vision::PERIOD - timer->Get(), Vision::MIN_WAIT ) );
		
	}
	return 0;
	
}
