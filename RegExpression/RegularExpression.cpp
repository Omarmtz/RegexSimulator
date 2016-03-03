/*
 * RegularExpression.cpp
 *
 *  Created on: 12.04.2013
 *      Author: Gabriela Roque
 */

#include "RegularExpression.h"
#include <cstring>
#define EPSILON       -1
#define CLOSURE       '*'
#define PLUS_CLOSURE  '+'
#define OPTIONAL      '?'
#define OPEN_PAREN    '('
#define CLOSE_PAREN   ')'
#define OR            '|'
#define CONCATNEXT  '&'

namespace RegEx
{

  RegularExpression::RegularExpression()
  {
    // TODO Auto-generated constructor stub
    this->a_PostFixStrRegEx="";
    this->a_PrsntProccChar=' ';
    this->a_InfixRegEx = NULL;
  }

  RegularExpression::~RegularExpression()
  {
    // TODO Auto-generated destructor stub
  }

  void
  RegularExpression::Initialize(std::string Compile)
  {
    a_InfixRegEx = const_cast<char*>(Compile.c_str());
    Infix_Posfix();
  }

  void
  RegularExpression::Infix_Posfix()
  {
    a_PrsntProccChar = *(a_InfixRegEx++);
    PreProcessOr();
    return ;
  }

  int
  RegularExpression::PreProcessLiterals()
  {
    if (a_PrsntProccChar == '\0')
      return -1;
    if (a_PrsntProccChar == '\\')
      {
        a_PrsntProccChar = *(a_InfixRegEx++);
        if (a_PrsntProccChar == '\0')
          return -1;
        a_PostFixStrRegEx += a_PrsntProccChar;
        a_PrsntProccChar = *(a_InfixRegEx++);
      }
    else if (strchr("()|*+?", a_PrsntProccChar) == NULL)
      {
        if (a_PrsntProccChar == '&')
          a_PostFixStrRegEx += "\\&";
        else
          a_PostFixStrRegEx += a_PrsntProccChar;

        a_PrsntProccChar = *(a_InfixRegEx++);
      }
    else if (a_PrsntProccChar == '(')
      {
        a_PrsntProccChar = *(a_InfixRegEx++);
        PreProcessOr();
        if (a_PrsntProccChar != ')')
          return -1;
        a_PrsntProccChar = *(a_InfixRegEx++);
      }
    else
      return -1;
    return 0;
  }

  int
  RegularExpression::PreProcessClosure()
  {
    PreProcessLiterals();
            while (a_PrsntProccChar != '\0' && strchr("*+?",a_PrsntProccChar) != NULL)
              {
                    a_PostFixStrRegEx += a_PrsntProccChar;
                    a_PrsntProccChar = *(a_InfixRegEx++);
            }
            return 0;
  }

  int
  RegularExpression::PrePreprocessConcatenation()
  {
    PreProcessClosure();
    while (strchr(")|*+?", a_PrsntProccChar) == NULL)
      {
        PreProcessClosure();
        a_PostFixStrRegEx += "&";
      }
    return 0;
  }

  bool
  RegularExpression::ValidateString(std::string strText,
      Automata::Automata_DFA &AutomataDFASim)
  {
    a_StringText = strText;
    Automata::State *pState = AutomataDFASim.a_DFATable[0];
    std::vector<Automata::State*>  Transition;
    for(unsigned int i = 0; i < a_StringText.size(); i++)
      {
        char CurrChar = a_StringText[i];

        pState->Transitions.GetTransition(CurrChar, Transition);
        if ( Transition.empty())
          return false;
          pState = Transition[0];
      }
    if ( pState->isAcceptingState())
                return true;
    return false;
  }


  int
  RegularExpression::PreProcessOr()
  {
    PrePreprocessConcatenation();
    while (a_PrsntProccChar == '|')
      {
        a_PrsntProccChar = *(a_InfixRegEx++);
        PrePreprocessConcatenation();
        a_PostFixStrRegEx += "|";
      }
    return 0;
  }

  const std::string&
  RegularExpression::getPstFixStr() const
  {
    return a_PostFixStrRegEx;
  }



} /* namespace RegEx */
