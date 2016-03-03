/*
 * Transition.h
 *
 *  Created on: 12.04.2013
 *      Author: Gabriela Roque
 */

#ifndef TRANSITION_H_
#define TRANSITION_H_
#include <iostream>
#include <map>
#include <set>
#include <vector>
namespace Automata
{


  class State;
  /*
   *
   */
  class Transition
  {
    typedef std::vector<State*> Table_States;
    typedef std::set<State*>::iterator StatesIterator;
    typedef std::multimap<char, State*> TransitionMap;
  public:
    Transition();
    virtual
    ~Transition();

    TransitionMap a_Transitions;

    void AddTransition(char inputCh, State *pState);
    void RemoveTransition(State* pState);
    void GetTransition(char inputCh, Table_States &States);

    //Operadores:
    bool operator==(const Transition &Other);
    Transition& operator=(const Transition &Other);


  };

} /* namespace Automata */
#endif /* TRANSITION_H_ */
