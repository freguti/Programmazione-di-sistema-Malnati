#pragma once
class Job
{
public:
	Job(long id, long start_time, long duration);
	~Job();
private:
	long id;
	long duration;
	long execution_time;
	long start_time;
	long wait_time;
	long completition_time;
};

