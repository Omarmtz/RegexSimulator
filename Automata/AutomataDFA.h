/*
 * AutomataDFA.h
 *
 *  Created on: 12.04.2013
 *      Author: Gabriela Roque
 */

#ifndef AUTOMATADFA_H_
#define AUTOMATADFA_H_

#include "Automata.h"

namespace Automata
{

  /*
   *
   */
  class Automata_DFA : public Automata::Automata
  {
  public:
    Automata_DFA();
    virtual
    ~Automata_DFA();
    virtual
    void PrintTable();


    Table a_DFATable;
  };

} /* namespace Automata */
#endif /* AUTOMATADFA_H_ */
