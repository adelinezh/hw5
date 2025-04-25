#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool recursive(const AvailabilityMatrix& avail, size_t dailyNeed, size_t maxShifts, DailySchedule& sched, std::vector<size_t>& shiftCount, size_t day, size_t position);

// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    sched.resize(avail.size(), std::vector<Worker_T>(dailyNeed, INVALID_ID));
    size_t position = avail[0].size();

    std::vector<size_t> shiftCount(position, 0);

    return recursive(avail, dailyNeed, maxShifts, sched, shiftCount, 0, 0);
}

bool recursive(const AvailabilityMatrix& avail, size_t dailyNeed, size_t maxShifts, DailySchedule& sched, std::vector<size_t>& shiftCount, size_t day, size_t position)
{
  size_t numDays = avail.size();
  size_t numWorkers = avail[0].size();

  if (day == numDays)
  {
      return true;
  }

  if (position == dailyNeed)
  {
    return recursive(avail, dailyNeed, maxShifts, sched, shiftCount, day + 1, 0);
  }

  for (Worker_T i = 0; i < numWorkers; i ++)
  {
    if (avail[day][i] && shiftCount[i]< maxShifts)
    {
      bool alreadyAssigned = false;
      for (size_t j = 0; j < position; j ++)
      {
        if (sched[day][j] == i)
        {
          alreadyAssigned = true;
          break;
        }
      }
      
      if (!alreadyAssigned)
      {
        sched[day][position] = i;
        shiftCount[i] ++;
        
        if (recursive(avail, dailyNeed, maxShifts, sched, shiftCount, day, position + 1))
        {
          return true;
        }
        
        sched[day][position] = INVALID_ID;
        shiftCount[i] --;
      }
    }
  }
  return false;
}

