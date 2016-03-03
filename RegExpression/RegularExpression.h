/*
 * RegularExpression.h
 *
 *  Created on: 12.04.2013
 *      Author: Gabriela Roque
 */

#ifndef REGULAREXPRESSION_H_
#define REGULAREXPRESSION_H_
#include <string>
#include "../Automata/AutomataDFA.h"
#include "../Automata/AutomataNFA.h"
#include "../Automata/State.h"
namespace RegEx
{

  /*
   *
   */
  class RegularExpression
  {
  public:
    RegularExpression();
    virtual
    ~RegularExpression();

    void Initialize(std::string Compile);
    bool ValidateString(std::string strText,Automata::Automata_DFA &AutomataDFASim);

    const std::string&
    getPstFixStr() const;

  private:

    std::string              a_StringText;
    std::string              a_PostFixStrRegEx;
    char*                    a_InfixRegEx;
    char                     a_PrsntProccChar;


    void Infix_Posfix();

    int PreProcessLiterals();
    int PreProcessClosure();
    int PrePreprocessConcatenation();
    int PreProcessOr();


  };

} /* namespace RegEx */
#endif /* REGULAREXPRESSION_H_ */
