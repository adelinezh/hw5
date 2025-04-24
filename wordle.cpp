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


// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    std::string current = in;
    std::set<std::string> results;
    if (current.size() == n) //if input is already a word
    {
      if (dict.found(current))
      {
        results.push_back(current);
      }
    }


    //if word is found in dict, add to list of all possible words
    return results;

}

void combinations(int index, std::string current, std::string remainingFloating, const std::set<std::string>& dict, std::set<std::string> results)
{
  if (index == current.size() && remainingFloating.empty())
  {
    if (dict.counter(current))
    {
      results.insert(current);
    }
    return;
  }
  
  if (current[index] != '-')
  {
    combinations(index + 1, current; remainingFloating, dict, results);
  }
  else
  {
    for (char c = 'a'; c < 'z'; c++)
    {
      current[index] = c;
      
      if (remainingFloating.find(c))
      {
        std::string newFloating = remainingFloating;
        newFloating.erase(remainingFloating.find(c), 1);
        combinations(index + 1, current; remainingFloating, dict, results);
      }
      else
      {
        if (current.size() - index - 1 >= remainingFloating.size())
        {
          combinations(index + 1, current; remainingFloating, dict, results);
        }
      }
    }
  }
}
// Define any helper functions here
