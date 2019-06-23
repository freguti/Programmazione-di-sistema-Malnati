#pragma once
#include <list>
#include <vector>
#include "Job.h"
#include <thread>
#include <mutex>

class JobScheduler
{
public:
	JobScheduler();
	~JobScheduler();
private:
	std::list<Job>	 startingJob;
	std::list<Job>	 executionJob;
	std::vector<Job> finishedJob;

	void submit(Job j);
	void start();
};

