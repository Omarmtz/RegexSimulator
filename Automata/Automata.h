/*
 * Automata.h
 *
 *  Created on: 12.04.2013
 *      Author: Gabriela Roque
 */

#ifndef AUTOMATA_H_
#define AUTOMATA_H_
#include <vector>
#include <set>
#include "State.h"
namespace Automata
{

  /*
   *
   */
  class Automata
  {

  public:
    typedef std::vector<State*> Table;
    std::set<char>     a_CharactersSet;

    Automata();
    virtual
    ~Automata();
    virtual
    void PrintTable(Table &table);

  protected:


  };

} /* namespace Automata */
#endif /* AUTOMATA_H_ */
