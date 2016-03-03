/*
 * AAlgorithm.h
 *
 *  Created on: 12.04.2013
 *      Author: Gabriela Roque
 */

#ifndef AALGORITHM_H_
#define AALGORITHM_H_
#include <string>
#include <stack>
#include <set>
#include "../Automata/State.h"
#include "../Automata/AutomataNFA.h"
#include "../Automata/AutomataDFA.h"
namespace AutomataAlgorithm
{

  /*
   *
   */
  class AAlgorithm
  {
    typedef std::vector<Automata::State*> Table;
    typedef std::set<Automata::State*> StatesSet;
    typedef std::set<Automata::State*>::iterator StateIterator;
  public:
    AAlgorithm();
    virtual
    ~AAlgorithm();
    void RegExpToThompson(std::string,Automata::Automata_NFA &Reference);
    void ConvertNFAtoDFA(Automata::Automata_NFA &AutomataAFN,Automata::Automata_DFA &AutomataAFD);


  private:
    std::string              a_StrPostFijRegEx;
    int                      a_NextStateID;
    std::stack<Table>        a_ProcessingStack;

    //Identificacion de Tipo de dato en Postfija.
    bool IsInput(char inputCh);
    bool IsMetaChar(char inputCh);
    //Tipos de construcciones.
    bool Concatenate();
    bool Closure();
    bool ClosureOptional();
    bool ClosurePlus();
    bool Or();
    //Pila de estados creados de acuerdo a la cláusula de Thompson.
    void PushOnProcessingStack(char chInput,Automata::Automata_NFA &Reference);
    bool PopTable(Table  &NFATable);
    //Conversion de AFN a AFD
    void EpsilonClosure(StatesSet T,StatesSet &Res);
    void Move(char chInput,StatesSet T,StatesSet &Res);
    void MinimizeDFA(Automata::Automata_DFA &AutomataAFD);
    void CleanUp();
    //Utilerias
    void TerminateAFNTable(Automata::Automata_NFA& Reference);
    void CleanAFDTable(Automata::Automata_DFA& AutomataAFD);
  };

} /* namespace AutomataAlgorithm */
#endif /* AALGORITHM_H_ */
