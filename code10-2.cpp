#include <iostream>
#include <stack>
using namespace std;
#include <stdbool.h>

void check(string Word);
void print_stack(stack<string> Orginal);

int main() {
  cout << "-----------------------------------------------------------" << '\n';
  cout << "     Name      : AJ Albrecht" << '\n';
  cout << "     Assignment: No.10 #2" << '\n';
  cout << "     Due Date  : 11/18" << '\n';
  cout << "Purpose: Use a parsing table method to check given strings." << '\n';
  cout << "------------------------------------------------------------" << '\n';

  check("a=(a+a)*a$");
  check("a=a*(a-a)$");
  check("a=a(a+a)a$");
  return 0;
}

void check(string Word) {
  string Table[8][10] = {{"X","a","+","-","*","/","(",")","$","="},
                        {"S","aW","X","X","X","X","X","X","X","X"},
                        {"W","X","X","X","X","X","X","X","X","=E"},
                        {"E","TQ","X","X","X","X","TQ","X","X","X"},
                        {"Q","X","+TQ","-TQ","X","X","X","L","L","X"},
                        {"T","FR","X","X","X","X","FR","X","X","X"},
                        {"R","X","L","L","*FR","/FR","X","L","L","X"},
                        {"F","a","X","X","X","X","(E)","X","X","X"}};
  stack<string> Stack;
  bool Continue;
  bool valid = 1;
  string Push_String;
  string Temp_String;
  string Current_Char;
  int Char_Number = -1;
  int Char_Table_Pos;
  string Current_State;
  int State_Number;
  int State_Table_Pos;

  // push intial stack values
  Stack.push("$");
  Stack.push("S");
  std::cout << "Tracing " << Word << '\n';

  // as long as the word is good, check each charcter
  for (size_t i = 0; i < Word.length(); i++) {
    if (valid == false) {
      std::cout << "This expression is not included in the gramar" ;
      break;
    }

    Current_Char = Word[++Char_Number];
    // get input row number
    for (size_t i = 1; i < 11; i++) {if (Table[0][i] == Current_Char) {Char_Table_Pos = i;}}

    // While the charcter has not been found, keep looking
    Continue = true;
    while (Continue == true) {
      Current_State = Stack.top();
      std::cout << "Pop: " << Current_State;
      Stack.pop();

      if (Current_State == "L") {
        Stack.pop(); // If Lamda is read, pop an extra character of the stack
      } else if (Current_State == "X") {
        std::cout << "    Fallied to find-> " << Current_Char <<'\n';
        valid = false;  // An empty box was read. The gramar is incorect.
        break;
      } else if (Current_State == Current_Char){
        std::cout << "      Match-> " << Current_State << '\n'; // match was found
        break;
      } else {//added

        // get state row number
        for (size_t i = 1; i < 9; i++) {if (Table[i][0] == Current_State) {State_Table_Pos = i;}}

        // push the contents of the box in revers order into the stack
        Push_String = Table[State_Table_Pos][Char_Table_Pos];
        std::cout << "      Go to: [" << Current_State << "," << Current_Char << "] = " << Push_String;
        std::cout << "      Push: " ;
        for (size_t i = Push_String.length()-1; i !=-1 ; i--) {
          Temp_String = Push_String[i];
          if (Temp_String != "L") {
            Stack.push(Temp_String);
            std::cout << Temp_String;
          } else {
            std::cout << "nothing";
          }
        }
        print_stack(Stack);
        std::cout << "" << '\n';
      }
    }
  }
  std::cout << '\n';
}

void print_stack(stack<string> Original) {
  stack<string> Print_Stack;
  // Create a new stack with the orginal stack contents backwords
  // This will allow the print mesage to be in the right order
  std::cout << "      ";
  while (Original.empty() == false) {
    Print_Stack.push(Original.top());
    Original.pop();
  }
  std::cout << "Stack-> " ;
  while (Print_Stack.empty() == false) {
    std::cout << Print_Stack.top();
    Print_Stack.pop();
  }
}
