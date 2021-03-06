#include "../include/unistd.h"
#include "../include/time.h"

#ifdef __is_libk
#include "../../include/cmos.h"
#endif
unsigned int sleep(unsigned int seconds){
  struct tm * currTime = getCurrentTime();
  struct tm endTime = *currTime;
  endTime.tm_sec += (int)seconds;

  while(currTime->tm_sec != endTime.tm_sec){
    currTime = getCurrentTime();
  }

  return 0;
}
