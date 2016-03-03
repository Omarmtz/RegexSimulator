/*
 * AutomataNFA.cpp
 *
 *  Created on: 12.04.2013
 *      Author: Gabriela Roque
 */

#include "AutomataNFA.h"

namespace Automata
{

  Automata_NFA::Automata_NFA()
  {
    // TODO Auto-generated constructor stub

  }

  Automata_NFA::~Automata_NFA()
  {
    // TODO Auto-generated destructor stub
  }

  void
  Automata_NFA::PrintTable()
  {
    std::cout<<"NFA Table"<<std::endl;
    Automata::PrintTable(this->a_NFATable);
  }

} /* namespace Automata */
