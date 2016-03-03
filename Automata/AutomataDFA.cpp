/*
 * AutomataFDA.cpp
 *
 *  Created on: 12.04.2013
 *      Author: Gabriela Roque
 */

#include "AutomataDFA.h"

namespace Automata
{



} /* namespace Automata */

Automata::Automata_DFA::Automata_DFA()
{
}

Automata::Automata_DFA::~Automata_DFA()
{
}

void
Automata::Automata_DFA::PrintTable()
{
  std::cout<<"DFA Table"<<std::endl;
  Automata::PrintTable(this->a_DFATable);
}
