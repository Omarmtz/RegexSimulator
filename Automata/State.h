/*
 * State.h
 *
 *  Created on: 12.04.2013
 *      Author: Gabriela Roque
 */

#ifndef STATE_H_
#define STATE_H_
#include "Transition.h"
#include <map>
#include <string>
namespace Automata
{

  /*
   *
   */
  class State
  {
    typedef std::set<State*> SetStates;
    typedef std::set<State*>::iterator SetStatesIterator;
    typedef std::multimap<char, State*> TransitionMap;
  public:
    //Tipos de Constructores
    State();
    State(int nID);
    State(SetStates NFAState, int nID);
    State(const State &Other);
    //Destructor
    virtual
    ~State();
    //Tabla Transiciones
    Transition Transitions;
    //Leer Estados NFA
    std::set<State*> & GetNFAStates();
    //Estado Pozo
    bool IsDeadEnd();
    //Operadores Implementados
    State &operator=(const State& other);
    bool operator==(const State& other);
    //Obtener Info
    std::string getStringID();

    int
    getNStateId() const;
    void
    setNStateId(int nStateId);
    bool
    isAcceptingState() const;
    void
    setAcceptingState(bool acceptingState);
    bool
    isMarked() const;
    void
    setMarked(bool marked);
    int
    getNGroupId() const;
    void
    setNGroupId(int nGroupId);

  private:

    int a_nStateID;
    int  a_nGroupID;
    bool a_AcceptingState;
    bool a_Marked;

    SetStates a_NFAStates;

  };

} /* namespace Automata */
#endif /* STATE_H_ */
