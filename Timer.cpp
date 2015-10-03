#ifndef TIMER_CPP
#define TIMER_CPP

// Header Files //////////////////////////////////////////////////
#include "Timer.h"

// Member Function Implementations //////////////////////////
Timer::Timer() : m_timer(false), timerWasStarted(false), duration(-1){}
Timer::Timer(bool timer) : m_timer(timer), timerWasStarted(false), duration(-1){}

void Timer::setTimer(bool timer){
  this->m_timer = timer;
}
void Timer::start() throw (runtime_error){
  if(!this->m_timer){
    return;
  }
  if(!gettimeofday(&beginTime, NULL)){
    timerWasStarted = true;
  }
  else{
    throw runtime_error("gettimeofday() returned 0. Serious problem. Can't run timer.");
  }
}

void Timer::stop() throw (logic_error){
	timeval endTime;

  if(!this->m_timer){
    return;
  }

  if( !timerWasStarted ){
    throw logic_error("Timer was never started.");
  }
  else{
    gettimeofday(&endTime, NULL);
    duration = endTime.tv_sec * 1000000 + endTime.tv_usec;
    duration -= beginTime.tv_sec * 1000000 + beginTime.tv_usec;
    duration /= 1000000;
  }
}

double Timer::getElapsedTime() const throw (logic_error){
  if(!this->m_timer){
    return -1;
  }

	if(timerWasStarted && duration != -1){
    return duration;
  }
  else{
    throw logic_error("Timer was never started.");
  }
}

#endif	//#ifndef TIMER_CPP
