/*
 * Transition.cpp
 *
 *  Created on: 12.04.2013
 *      Author: Gabriela Roque
 */

#include "Transition.h"

namespace Automata
{

  Transition::Transition()
  {
    // TODO Auto-generated constructor stub

  }

  Transition::~Transition()
  {
    // TODO Auto-generated destructor stub
  }

  bool
  Transition::operator ==(const Transition& Other)
  {
    return(this->a_Transitions == Other.a_Transitions);
  }

  void
  Transition::AddTransition(char inputCh, State* pState)
  {
    a_Transitions.insert(std::make_pair(inputCh, pState));
  }

  void
  Transition::RemoveTransition(State* pState)
  {
    TransitionMap::iterator iter;
    for(iter = a_Transitions.begin(); iter != a_Transitions.end();)
      {
        State *toState = iter->second;
        if(toState == pState)
          a_Transitions.erase(iter++);
        else
          ++iter;
      }
  }

  void
  Transition::GetTransition(char inputCh, Table_States& States)
  {
    States.clear();
    TransitionMap::iterator iter;
    for(iter = a_Transitions.lower_bound(inputCh);
        iter != a_Transitions.upper_bound(inputCh);
        ++iter)
      {
        State *pState = iter->second;
        States.push_back(pState);
      }
  }

  Transition&
  Transition::operator =(const Transition& Other)
  {
    this->a_Transitions=Other.a_Transitions;
    return *this;
  }

} /* namespace Automata */
