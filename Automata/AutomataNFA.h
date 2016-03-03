/*
 * AutomataNFA.h
 *
 *  Created on: 12.04.2013
 *      Author: Gabriela Roque
 */

#ifndef AUTOMATANFA_H_
#define AUTOMATANFA_H_

#include "Automata.h"

namespace Automata
{

  /*
   *
   */
  class Automata_NFA : public Automata::Automata
  {
  public:
    Automata_NFA();

    virtual
    ~Automata_NFA();
    virtual
    void PrintTable();


    Table a_NFATable;

  };

} /* namespace Automata */
#endif /* AUTOMATANFA_H_ */
