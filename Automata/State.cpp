/*
 * State.cpp
 *
 *  Created on: 12.04.2013
 *      Author: Gabriela Roque
 */

#include "State.h"
#include <sstream>
namespace Automata
{

  State::State()
  {
    this->a_nStateID = -1;
    this->a_AcceptingState= false;
    this->a_nGroupID=-1;
    this->a_Marked=false;
  }

  State::State(int nID)
  {
    this->a_nStateID=nID;
    this->a_AcceptingState=false;
    this->a_nGroupID=0;
    this->a_Marked=false;
  }

  State::State(SetStates NFAState, int nID)
  {
    a_NFAStates = NFAState;
    a_nStateID = nID;
    a_AcceptingState = false;
    a_nGroupID = 0;
    this->a_Marked=false;
    SetStatesIterator iter;
    for(iter = NFAState.begin(); iter != NFAState.end(); ++iter)
      {
        if((*iter)->a_AcceptingState) {
            a_AcceptingState = true;
        }
      }
  }

  State::State(const State& Other)
  {
    *this=Other;
  }

  State::~State()
  {
    this->a_NFAStates.clear();
  }

  State&
  State::operator =(const State& other)
  {
    //TODO Operador Igual de Transiciones (Implementado Verificar)
    this->Transitions= other.Transitions;
    this->Transitions= other.Transitions;
    this->a_nStateID        = other.a_nStateID;
    this->a_NFAStates       = other.a_NFAStates;
    return *this;
  }

  bool
  State::IsDeadEnd()
  {
    if(a_AcceptingState)
      {
      return false;
      }
    if(this->Transitions.a_Transitions.empty())
      {
      return true;
      }
    TransitionMap::iterator iter;
    for(iter=this->Transitions.a_Transitions.begin();
        iter!=this->Transitions.a_Transitions.end();
        ++iter)
      {
        State *toState = iter->second;
        if(toState != this)
          {
          return false;
          }
      }
    return true;

  }

  bool
  State::operator ==(const State& other)
  {
    if(a_NFAStates.empty())
      return(a_nStateID == other.a_nStateID);
    else
      return(a_NFAStates == other.a_NFAStates);
  }

  std::set<State*> &State::GetNFAStates()
  {
    return this->a_NFAStates;
  }

  int
  State::getNStateId() const
  {
    return a_nStateID;
  }

  bool
  State::isAcceptingState() const
  {
    return a_AcceptingState;
  }

  bool
  State::isMarked() const
  {
    return a_Marked;
  }

  void
  State::setMarked(bool marked)
  {
    a_Marked = marked;
  }

  int
  State::getNGroupId() const
  {
    return a_nGroupID;
  }

  void
  State::setNGroupId(int nGroupId)
  {
    a_nGroupID = nGroupId;
  }

  void
  State::setAcceptingState(bool acceptingState)
  {
    a_AcceptingState = acceptingState;
  }

  void
  State::setNStateId(int nStateId)
  {
    a_nStateID = nStateId;
  }

  std::string
  State::getStringID()
  {
    std::string result="";
    std::ostringstream convert;   // stream used for the conversion
 if(a_AcceptingState)
      {
        result+="{";
        convert.clear();
        convert << a_nStateID;
        result+= convert.str();
        result+="}";
      }
    else {
        convert.clear();
        convert << a_nStateID;
        result+= convert.str();
        result+="  ";
    }
    return result;
  }

} /* namespace Automata */
