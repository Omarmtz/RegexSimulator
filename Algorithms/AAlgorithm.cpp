/*
 * AAlgorithm.cpp
 *
 *  Created on: 12.04.2013
 *      Author: Gabriela Roque
 */

#include "AAlgorithm.h"
#include "../Automata/Automata.h"
#include "../Automata/State.h"
#include "../Automata/Transition.h"
using namespace Automata;


#define EPSILON       -1
#define CLOSURE       '*'
#define PLUS_CLOSURE  '+'
#define OPTIONAL      '?'
#define OPEN_PAREN    '('
#define CLOSE_PAREN   ')'
#define OR            '|'
#define CONCATNEXT  '&'

namespace AutomataAlgorithm
{

  AAlgorithm::AAlgorithm()
  {
    a_NextStateID=0;
  }

  AAlgorithm::~AAlgorithm()
  {
    while(!a_ProcessingStack.empty())
      {
        a_ProcessingStack.pop();
      }

  }

  void
  AAlgorithm::MinimizeDFA(Automata_DFA& AutomataAFD)
  {
    StatesSet PitSet;

    for(int i = 0; i < (int)AutomataAFD.a_DFATable.size(); ++i)
      {
        if(AutomataAFD.a_DFATable[i]->IsDeadEnd())
          {
            PitSet.insert(AutomataAFD.a_DFATable[i]);
          }
      }
    if(PitSet.empty())
      return;
    StateIterator iter;
    for(iter = PitSet.begin(); iter != PitSet.end(); ++iter) 
      {
        for(int i = 0; i < (int)AutomataAFD.a_DFATable.size(); ++i)
          AutomataAFD.a_DFATable[i]->Transitions.RemoveTransition(*iter);

        Table::iterator Iterator;
        for(Iterator = AutomataAFD.a_DFATable.begin(); Iterator != AutomataAFD.a_DFATable.end(); ++Iterator)
          {
            if(*Iterator == *iter) {
                break;
            }
          }
        AutomataAFD.a_DFATable.erase(Iterator);
        delete *iter;
      }
  }

  void
  AAlgorithm::TerminateAFNTable(Automata_NFA& Reference)
  {
    PopTable(Reference.a_NFATable);
    Reference.a_NFATable[Reference.a_NFATable.size() - 1]->setAcceptingState(
        true);
  }

  void
  AAlgorithm::RegExpToThompson(std::string allocator,Automata_NFA &Reference)
  {
    //Verificar la cadena caracter por caracter y armar el AFN Thompson Equivalente
    a_StrPostFijRegEx=allocator;
    for(int i = 0; i < (int)a_StrPostFijRegEx.size(); ++i)
      {
        char curChar = a_StrPostFijRegEx[i];
        if ( IsInput( curChar ))
          {
            //Caracter union.
            PushOnProcessingStack(curChar,Reference);
          }
        else if ( IsMetaChar( curChar ) )
          {
            //Verificar por tipos.
            switch ( curChar )
            {
            case CLOSURE:
              Closure();
              break;
            case PLUS_CLOSURE:
              ClosurePlus();
              break;
            case OPTIONAL:
              ClosureOptional();
              break;
            case OR:
              Or();
              break;
            case CONCATNEXT:
              Concatenate();
              break;
            }
          }
      }
    TerminateAFNTable(Reference);
  }

  bool
  AAlgorithm::IsInput(char inputCh)
  {
    return(!IsMetaChar(inputCh));
  }

  bool
  AAlgorithm::IsMetaChar(char inputCh)
  {
    return(( inputCh == CLOSURE )      ||
        ( inputCh == OR )           ||
        ( inputCh == OPEN_PAREN )   ||
        ( inputCh == CLOSE_PAREN )  ||
        ( inputCh == PLUS_CLOSURE ) ||
        ( inputCh == CONCATNEXT ) ||
        ( inputCh == OPTIONAL ));
  }

  bool
  AAlgorithm::Closure()
  {
    Table PrevTable;
    //Obtener Tabla de Estados anteriores preprocesados
    if(!PopTable(PrevTable))
      return false;
    //Crear Estados
    State *LeftTable  = new State(a_NextStateID++);
    State *RightTable = new State(a_NextStateID++);
    //Conectar Estados
    LeftTable->Transitions.AddTransition(EPSILON, RightTable);
    LeftTable->Transitions.AddTransition(EPSILON, (*(PrevTable.begin())));
    //Asignar (Conectar Tabla Estados)
    (*(PrevTable.rbegin()))->Transitions.AddTransition(EPSILON, RightTable);
    (*(PrevTable.rbegin()))->Transitions.AddTransition(EPSILON, (*(PrevTable.begin())));
    //Fusionar Tablas a Vector y agregarlas a Pila.
    PrevTable.insert( PrevTable.begin(), LeftTable );
    PrevTable.push_back ( RightTable);
    //Insertar en Pila Lista Estados Preprocesados.
    a_ProcessingStack.push(PrevTable);
    return true;
  }

  void
  AAlgorithm::PushOnProcessingStack(char chInput,Automata_NFA &Reference)
  {
    //Creacion Estados para Unir
    State *s0 = new State(a_NextStateID++);
    State *s1 = new State(a_NextStateID++);
    //Agregar Transiciones a Estados.
    s0->Transitions.AddTransition(chInput, s1);
    //SubTabla Enlace
    Table NewSubTable;
    NewSubTable.push_back(s0);
    NewSubTable.push_back(s1);
    //Agregacion Estados a pila para procesos siguientes.
    a_ProcessingStack.push(NewSubTable);
    //Reference.AutomataAFN.m_InputSet.insert(chInput);
    Reference.a_CharactersSet.insert(chInput);
  }

  bool
  AAlgorithm::Concatenate()
  {
    //Uso de tablas para su procesamiento
    Table  LeftTable, RightTable;
    //Obtener Tablas Referentes Preprocesadas
    if(!PopTable(RightTable) || !PopTable(LeftTable))
      return false;
    //Unir Tablas de concatenacion.
    (*(LeftTable.rbegin()))->Transitions.AddTransition(EPSILON, *(RightTable.begin()));
    //Copiar y fusionar Tablas.
    LeftTable.insert(LeftTable.end(), RightTable.begin(), RightTable.end());
    //Insertar Tablas en la pila de procesamiento.
    a_ProcessingStack.push(LeftTable);
    return true;
  }

  bool
  AAlgorithm::ClosureOptional()
  {
    Table PrevTable;
    //Obtener Tabla Preprocesamiento
    if(!PopTable(PrevTable))
      return false;
    //Creacion de Estados para Armado de tabla.
    State *LeftTable  = new State(a_NextStateID++);
    State *RightTable = new State(a_NextStateID++);
    //Union de tablas
    LeftTable->Transitions.AddTransition(EPSILON, RightTable);
    LeftTable->Transitions.AddTransition(EPSILON, ((*(PrevTable.begin()))));
    (*(PrevTable.rbegin()))->Transitions.AddTransition(EPSILON, RightTable);
    //Fusion de tablas.
    PrevTable.insert( PrevTable.begin(), LeftTable );
    PrevTable.push_back ( RightTable);
    //Insercion de Tablas
    a_ProcessingStack.push(PrevTable);

    return true;
  }

  bool
  AAlgorithm::ClosurePlus()
  {
    Table PrevTable;
    if(!PopTable(PrevTable))
      return false;

    State *LeftTable  = new State(a_NextStateID++);
    State *RightTable = new State(a_NextStateID++);

    LeftTable->Transitions.AddTransition(EPSILON, *(PrevTable.begin()));
    (*(PrevTable.rbegin()))->Transitions.AddTransition(EPSILON, RightTable);
    (*(PrevTable.rbegin()))->Transitions.AddTransition(EPSILON, *(PrevTable.begin()));

    PrevTable.insert( PrevTable.begin(), LeftTable );
    PrevTable.push_back ( RightTable);

    a_ProcessingStack.push(PrevTable);

    return true;
  }

  bool
  AAlgorithm::Or()
  {
    Table  UpperTable, LowerTable;

    if(!PopTable(LowerTable) || !PopTable(UpperTable))
      return false;

    State *LeftTable   = new State(a_NextStateID++);
    State *RightTable  = new State(a_NextStateID++);

    LeftTable->Transitions.AddTransition(EPSILON, *(UpperTable.begin()));
    LeftTable->Transitions.AddTransition(EPSILON, *(LowerTable.begin()));
    (*(UpperTable.rbegin()))->Transitions.AddTransition(EPSILON, RightTable);
    (*(LowerTable.rbegin()))->Transitions.AddTransition(EPSILON, RightTable);

    LowerTable.push_back(RightTable);
    UpperTable.insert(UpperTable.begin(),LeftTable);
    UpperTable.insert(UpperTable.end(), LowerTable.begin(), LowerTable.end());

    a_ProcessingStack.push(UpperTable);
    return true;
  }



  bool
  AAlgorithm::PopTable(Table& NFATable)
  {
    //Verificar si la tabla de estados contiene algun elemento.
    if(a_ProcessingStack.size()>0)
      {
        //Sacar Elemento y cargarlo al apuntador de memoria NFA TABLE
        NFATable = a_ProcessingStack.top();
        //Quitar y regresar verdadero.
        a_ProcessingStack.pop();
        return true;
      }
    return false;
  }

  void
  AAlgorithm::CleanAFDTable(Automata_DFA& AutomataAFD)
  {
    for (int i = 0; i < (int) (AutomataAFD.a_DFATable.size()); ++i)
      delete AutomataAFD.a_DFATable[i];
    AutomataAFD.a_DFATable.clear();
  }

  void
  AAlgorithm::ConvertNFAtoDFA(Automata_NFA& AutomataAFN,
      Automata_DFA& AutomataAFD)
  {

    CleanAFDTable(AutomataAFD);
    if(AutomataAFN.a_NFATable.size() == 0)
      return;
    StatesSet NFAStartStateSet;
    NFAStartStateSet.insert(AutomataAFN.a_NFATable[0]);

    StatesSet DFAStartStateSet;
    EpsilonClosure(NFAStartStateSet, DFAStartStateSet);

    a_NextStateID = 0;
    State *DFAStartState = new State(DFAStartStateSet, a_NextStateID++);

    AutomataAFD.a_DFATable.push_back(DFAStartState);

    Table UnVisitedStates;
    UnVisitedStates.push_back(DFAStartState);

    while(!UnVisitedStates.empty())
      {
        State* CurDFAState = UnVisitedStates[UnVisitedStates.size()-1];
        UnVisitedStates.pop_back();

        std::set<char>::iterator iter;
        for(iter = AutomataAFN.a_CharactersSet.begin(); iter != AutomataAFN.a_CharactersSet.end(); ++iter)
          {
            StatesSet MoveRes, EpsilonClosureRes;

            Move(*iter, CurDFAState->GetNFAStates(), MoveRes);
            EpsilonClosure(MoveRes, EpsilonClosureRes);

            StateIterator MoveResItr;
            StateIterator EpsilonClosureResItr;

            bool bFound = false;
            State *s   = NULL;
            for(int i = 0; i < (int)AutomataAFD.a_DFATable.size(); ++i) {
                s = AutomataAFD.a_DFATable[i];
                if(s->GetNFAStates() == EpsilonClosureRes) {
                    bFound = true;
                    break;
                }
            }
            if(!bFound) {
                State* SetW = new State(EpsilonClosureRes, a_NextStateID++);
                UnVisitedStates.push_back(SetW);
                AutomataAFD.a_DFATable.push_back(SetW);
                CurDFAState->Transitions.AddTransition(*iter, SetW);
            }
            else
              {
                CurDFAState->Transitions.AddTransition(*iter, s);
              }
          }
    }
    AutomataAFD.a_CharactersSet=AutomataAFN.a_CharactersSet;

    MinimizeDFA(AutomataAFD);

  }

  void
  AAlgorithm::EpsilonClosure(StatesSet InitialSet, StatesSet& ResulSet)
  {
    std::stack<State*> UnVisitedStates;
    ResulSet.clear();
    ResulSet = InitialSet;
    StateIterator iter;
    for(iter = InitialSet.begin(); iter != InitialSet.end(); ++iter)
      {
        UnVisitedStates.push(*iter);
      }

    while(!UnVisitedStates.empty())
      {
        State* curState = UnVisitedStates.top();
        UnVisitedStates.pop();

        Table epsilonStates;
        curState->Transitions.GetTransition(EPSILON, epsilonStates);

        Table::iterator epsilonItr;

        for ( epsilonItr = epsilonStates.begin(); epsilonItr != epsilonStates.end(); ++epsilonItr )
          {
            if(ResulSet.find((*epsilonItr)) == ResulSet.end()) {
                ResulSet.insert((*epsilonItr));
                UnVisitedStates.push((*epsilonItr));
            }
          }
      }
  }

  void
  AAlgorithm::Move(char chInput, StatesSet PresentStates, StatesSet& Res)
  {
    Res.clear();
    StateIterator iter;
    for(iter = PresentStates.begin(); iter != PresentStates.end(); ++iter)
      {
        Table States;
        (*iter)->Transitions.GetTransition(chInput, States);
        for(unsigned int index = 0; index <States.size(); ++index)
          {
            Res.insert(States[index]);
          }
      }
  }

} /* namespace AutomataAlgorithm */
