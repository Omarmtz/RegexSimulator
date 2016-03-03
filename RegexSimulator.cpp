//============================================================================
// Name        : ExpresionesRegulares.cpp
// Author      : Gabriela Roque
// Version     : 1.0
// Copyright   : Copyrights ESCOM
// Description : Regular Expression Automata and their Algorithms
//============================================================================

#include <iostream>
#include <string>
#include "RegExpression/RegularExpression.h"
#include "Algorithms/AAlgorithm.h"
#include "Automata/AutomataDFA.h"
#include "Automata/AutomataNFA.h"

using namespace std;

void
Mensaje()
{
  cout << "\n\tChoices\t";
  cout
  << "\n\n\tPlease choose an option:\n\n1.-Build Expression.\n2.-Convert NFA to DFA.\n3.-Test String\n4.-Exit\tOption: "
  << endl;
}

void
Simular(RegEx::RegularExpression &RegularExpression1,
    Automata::Automata_DFA &DFAAutomata1)
{
  std::string Cadena;
  Cadena.clear();
  cout << "Input Test String: " << "\n";
  cin >> Cadena;
  if (RegularExpression1.ValidateString(Cadena, DFAAutomata1))
    {
      cout << "String Match\n";
    }
  else
    {
      cout << "String didn't match\n";
    }
}

void
GenerarRegExp(RegEx::RegularExpression &RegularExpression1,
    AutomataAlgorithm::AAlgorithm &Algorithm1,
    Automata::Automata_NFA &NFAAutomata1)
{
  string ProcessingExp;
  std::cin >> ProcessingExp;
  RegularExpression1.Initialize(ProcessingExp);
  Algorithm1.RegExpToThompson(RegularExpression1.getPstFixStr(), NFAAutomata1);
}

int main() {
  RegEx::RegularExpression RegularExpression1;
  Automata::Automata_NFA NFAAutomata1;
  Automata::Automata_DFA DFAAutomata1;
  AutomataAlgorithm::AAlgorithm Algorithm1;
  int opt,band=1,active=1;

  do {
      Mensaje();
      cin>>opt;
      switch (opt)
      {
      case (1):{
        GenerarRegExp(RegularExpression1, Algorithm1, NFAAutomata1);
        NFAAutomata1.PrintTable();
        active=2;

        break;
      }
      case (2):{
        if(active==2)
          {
            Algorithm1.ConvertNFAtoDFA(NFAAutomata1, DFAAutomata1);
            DFAAutomata1.PrintTable();
            active=3;
          }
        else
          {
            cout<<"Must Introduce an Expression First."<<endl;
          }

        break;
      }
      case (3):{
        if(active==3)
          {
            Simular(RegularExpression1, DFAAutomata1);
          }
        else
          {
            cout<<"Before proceeding to simulate please convert NFA to DFA"<<endl;
          }
        break;
      }
      case (4):{
        band =0;
        return 0;
        break;
      }
      default:{
        cout<<"Please select a valid option."<<endl;
        break;
      }
      }
  }while (band != 0);


  return 0;
}
