#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void combinations(int index, std::string current, std::string remainingFloating, const std::set<std::string>& dict, std::set<std::string>& results);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    std::string current = in;
    std::set<std::string> results;
    combinations(0, current, floating, dict, results);
    return results;

}

void combinations(int index, std::string current, std::string remainingFloating, const std::set<std::string>& dict, std::set<std::string>& results)
{
  if (index == current.size())
  {
    if (remainingFloating.empty() && dict.find(current) != dict.end())
    {
      results.insert(current);
    }
    return;
  }
  
  if (current[index] != '-')
  {
    return combinations(index + 1, current, remainingFloating, dict, results);
  }
  else
  {
    for (char c = 'a'; c <= 'z'; c++)
    {
      current[index] = c;
      
      if (remainingFloating.find(c) != std::string::npos)
      {
        std::string newFloating = remainingFloating;
        newFloating.erase(newFloating.find(c), 1);
        combinations(index + 1, current, newFloating, dict, results);
      }
      else
      {
        if (current.size() - index - 1 >= remainingFloating.size())
        {
          return combinations(index + 1, current, remainingFloating, dict, results);
        }
      }
    }
  }
}