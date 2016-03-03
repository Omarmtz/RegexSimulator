/*
 * Automata.cpp
 *
 *  Created on: 12.04.2013
 *      Author: Gabriela Roque
 */
#include <sstream>
#include "Automata.h"

#define EPSILON       -1
namespace Automata
{

  Automata::Automata()
  {
    // TODO Auto-generated constructor stub

  }

  Automata::~Automata()
  {
    // TODO Auto-generated destructor stub
  }

} /* namespace Automata */

void
Automata::Automata::PrintTable(Table &table)
{
  std::string TableString;
  TableString = "Por orden de Recorrido en Automata:\n";
  for(int i = 0; i < (int)table.size(); ++i)
    {
      State *pState = table[i];
      if(pState->isAcceptingState())
        {
          TableString += "\t" + pState->getStringID() + "\t\n";
        }
    }
  TableString += "\n";

  for( int i = 0; i < (int)table.size(); ++i)
    {
      State *pState = table[i];
      std::vector<State*> State;
      pState->Transitions.GetTransition(EPSILON, State);
      for(int j = 0; j < (int)State.size(); ++j)
        {
          TableString += "\t" + pState->getStringID() + " -> " + State[j]->getStringID();
          TableString += "\t[Etiqueta = \"Epsilon\"]\n";
        }
      std::set<char>::iterator iter;
      for(iter = a_CharactersSet.begin(); iter != a_CharactersSet.end(); ++iter)
        {
          pState->Transitions.GetTransition(*iter, State);
          for(int j = 0; j < (int)State.size(); ++j)
            {
              TableString += "\t" + pState->getStringID() + " -> " + State[j]->getStringID();
              std::stringstream out;
              out << *iter;
              TableString += "\t[Etiqueta = \"" + out.str() + "\"]\n";
            }
        }
    }
  std::cout << TableString;

}
