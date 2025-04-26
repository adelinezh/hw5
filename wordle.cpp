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
set<string> combinations(int index, std::string current, std::string floating);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    std::set<std::string> words = combinations(0, in, floating);
    std::set<std::string> results;
    
    for(set<string>::iterator it = words.begin(); it != words.end(); it++)
    {
      if (dict.find(*it) != dict.end())
      {
        results.insert(*it);
      }
    }
    return results;
}

set<string> combinations(int index, std::string current, std::string floating)
{
  set<string> combos;
  if (current.length() == 0)
  {
    return combos;
  }
  
  int blankCount = 0;
  for (int i = 0; i < current.length(); i ++)
  {
    if (current[i] == '-')
    {
      blankCount ++;
    }
  }

  if (blankCount == 0) //completed word
  {
    combos.insert(current);
    return combos;
  }

  if (current[index] == '-') //blanks
  {
    //check floating characters
    for(unsigned int i = 0; i < floating.length(); i++)
    {
      char character = floating[i];
      current[index] = character;
      string newFloating = floating.substr(0, i) + floating.substr(i + 1);
      set<string> temp = combinations(index + 1, current, newFloating);
      combos.insert(temp.begin(), temp.end());
      current[index] = '-';
    }

    if ((int)floating.length() < blankCount) //no letters left in floating
    {
      for (char c = 'a'; c <= 'z'; c++)
      {
        current[index] = c;
        set<string> temp = combinations(index + 1, current, floating);
        combos.insert(temp.begin(), temp.end());
        current[index] = '-';
      }
    }
  }
  else //no blanks
  {
    set<string> temp = combinations(index + 1, current, floating);
    combos.insert(temp.begin(), temp.end());
  }
  return combos;
}