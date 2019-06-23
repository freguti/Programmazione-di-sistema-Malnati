#include "pch.h"
#include "Job.h"


Job::Job(long id, long start_time, long duration)
{
	this->id = id;
	this->start_time = start_time;
	this->duration = duration;
}


Job::~Job()
{
}
