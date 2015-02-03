#ifndef __HDR_IO_DEVICE__
#define __HDR_IO_DEVICE__


#include "Config.h"


class IODevice
{
public:
	IODevice() {};
	virtual ~IODevice() {};

	virtual char *getName()=0;
	virtual void setName(char *)=0;
	virtual int  getPin()=0;
	virtual void setPin(int)=0;

	virtual void Timer1ms()=0;
	virtual void Timer1sec()=0;
};
#endif
