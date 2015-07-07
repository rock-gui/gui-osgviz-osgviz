/*
 * timing.h
 *
 *  Created on: 10.02.2009
 *      Author: planthaber
 */

#ifndef TIMING_H_
#define TIMING_H_

#include <sys/time.h>
#include <time.h>
#include <stdio.h>

/**
 * @class Timing
 * provides some tools for runtime measurements
 */

class Timing{
private:
	clock_t startticks,stopticks;
	timeval starttime,stoptime,intermediatetime;
	double seconds,mikros_in_secs;
	double lastresult,lastresult_cpu;
	bool started,started_cpu;

public:

	Timing(){
		startticks = clock();
		gettimeofday(&starttime,0);
		started = false;
		started_cpu = false;
		lastresult=0;
	}

	static double timeinms(const struct timeval& time){
		return (time.tv_sec * 1000) + (time.tv_usec / 1000.0);
	}

	static double timeins(const struct timeval& time){
		return (time.tv_sec) + (time.tv_usec / 1000000.0);
	}

	static double diffms(const struct timeval& t1, const struct timeval& t2){
		return timeinms(t2) - timeinms(t1);
	}

	static double diffs(const struct timeval& t1, const struct timeval& t2){
		return timeins(t2) - timeins(t1);
	}

	inline struct timeval& getLastStopTime(){
		return stoptime;
	}

	/**
	 * start a measurements of cpu time occupied by the program i.e. a sleep() command
	 * does not take cpu time, so measuring a sleep results in 0 time taken
	 */
	inline void start_cpu(){
		started_cpu = true;
		startticks = clock();
	}

	/**
	 * Stop a cpu time measurement
	 */
	inline void stop_cpu(){
		stopticks = clock();
		if (started_cpu){
			lastresult_cpu = (stopticks-startticks)/(double)CLOCKS_PER_SEC;
			started_cpu = false;
		}else{
			lastresult_cpu = 0;
		}
	}

	inline void reset_cpu(){
		lastresult_cpu = 0;
	}

	/**
	 * get the
	 */
	inline double get_time_in_secs_cpu(){
		return lastresult_cpu;
	}

	inline void start(){
		started=true;
		gettimeofday(&starttime,0);
	}

	inline void stop(){
		gettimeofday(&stoptime,0);
		if (started){
			lastresult=diffs(starttime,stoptime);
			started=false;
		}else{
			lastresult = 0;
		}
	}

	inline void reset(){
		lastresult = 0;
	}

	inline double get_time_in_secs(){
		return lastresult;
	}

	inline double get_intermediate_time_in_secs(){
		if (started){
			gettimeofday(&intermediatetime,0);
			return diffs(starttime,intermediatetime);
		}
		return 0;
	}

	inline double get_interval_in_secs(){
		stop();
		start();
		return lastresult;
	}

	inline void print_loop_time(){
		stop_cpu();
		stop();
		printf("loop time: %f seconds, used cpu time: %f seconds\n",get_time_in_secs(),get_time_in_secs_cpu());
		fflush(stdout);
		start();
		start_cpu();
	}

	inline void print_vars(){
		printf("%f seconds, %f miks in seconds\n",seconds, mikros_in_secs);
		fflush(stdout);
	}

};


#endif /* STOPWATCH_H_ */
