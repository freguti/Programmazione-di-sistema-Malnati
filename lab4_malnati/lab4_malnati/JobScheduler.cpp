#include "pch.h"
#include "JobScheduler.h"

JobScheduler::JobScheduler()
{
}


JobScheduler::~JobScheduler()
{
}

void JobScheduler::submit(Job j)
{
	auto pos = this->startingJob.end();
	this->startingJob.insert(pos, j);
	
}
