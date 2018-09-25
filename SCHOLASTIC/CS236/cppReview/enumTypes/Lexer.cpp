#include "Lexer.h"
#include "Token.h"

Lexer::Lexer() { /*std::cout << "Creating LEXER object" << std::endl;*/ };
Lexer::~Lexer() { /*std::cout << "Deleting LEXER object" << std::endl;*/ };

void Lexer::PrintVec(std::vector<std::string> inVec){
  for(std::vector<std::string>::iterator it = inVec.begin(); it != inVec.end(); ++it)
    std::cout << ' ' << *it << std::endl;
}

//FIXME: CANNOT PRINT VECTOR OF TOKENS
void Lexer::PrintVec(std::vector<Token> tokenVec) {
  int vecSize = tokenVec.size();
  std::cout << vecSize << std::endl;
}

void Lexer::MapVec(int vecSize, std::vector<std::string> inVec) {
  for(unsigned int i = 0; i != vecSize; i++) {
    for(unsigned int y = 0; y != inVec[i].length(); y++) {
      if(inVec[i][y] == ',') { Comma(inVec, i, y); }
      else if(inVec[i][y] == '.') { Period(inVec, i, y); }
      else if(inVec[i][y] == '?') { Question(inVec, i, y); } 
      else if(inVec[i][y] == '(') { LeftParen(inVec, i, y); }   
      else if(inVec[i][y] == ')') { RightParen(inVec, i, y); }
      else if(inVec[i][y] == ':') { ColonCheck(inVec, i, y); }
      else if(inVec[i][y] == '*') { Multiply(inVec, i, y); }
      else if(inVec[i][y] == '+') { Add(inVec, i, y); }
      else if(inVec[i][y] == 'S') { SchemeCheck(inVec, i, y); }
      else if(inVec[i][y] == 'F') { FactCheck(inVec, i, y); }
      else if(inVec[i][y] == 'R') { RulesCheck(inVec, i, y); }
      else if(inVec[i][y] == 'Q') { QueriesCheck(inVec, i, y); }
      else if(inVec[i][y] == '\'') { StringCheck(inVec, i, y); }
      else if(inVec[i][y] == '#') { CommentCheck(inVec, i, y); }
      //else { Undefined(inVec, i, y); }
      //else { IDCheck(inVec, i, y); }
    }
  }
  EndOfFile(vecSize);
  std::cout << "Total Tokens = " << tokenVec.size() << std::endl;
}

void Lexer::EndOfFile(int vecSize) {
  Token tok("", vecSize - 1, ENDOFILE);
  tokenVec.push_back(tok);
  tok.FormatPrint();
}
// SINGLE CHAR HANDLING FIXME: NOT VERY DRY, MUCH REPEATABLE CODE
void Lexer::Comma(std::vector<std::string> inVec, int x, int y) {
  Token tok(inVec[x][y], x + 1, COMMA);
  tokenVec.push_back(tok);
  tok.FormatCharPrint();  
}
void Lexer::Period(std::vector<std::string> inVec, int x, int y) {
  Token tok(inVec[x][y], x + 1, PERIOD);
  tokenVec.push_back(tok);
  tok.FormatCharPrint();
}
void Lexer::Question(std::vector<std::string> inVec, int x, int y) {
  Token tok(inVec[x][y], x + 1, Q_MARK);
  tokenVec.push_back(tok);
  tok.FormatCharPrint();  
}
void Lexer::LeftParen(std::vector<std::string> inVec, int x, int y) {
  Token tok(inVec[x][y], x + 1, LEFT_PAREN);
  tokenVec.push_back(tok);
  tok.FormatCharPrint();  
}
void Lexer::RightParen(std::vector<std::string> inVec, int x, int y) {
  Token tok(inVec[x][y], x + 1, RIGHT_PAREN);
  tokenVec.push_back(tok);
  tok.FormatCharPrint();  
}
void Lexer::Multiply(std::vector<std::string> inVec, int x, int y) {
  Token tok(inVec[x][y], x + 1, MULTIPLY);
  tokenVec.push_back(tok);
  tok.FormatCharPrint();  
}
void Lexer::Add(std::vector<std::string> inVec, int x, int y) {
  Token tok(inVec[x][y], x + 1, ADD);
  tokenVec.push_back(tok);
  tok.FormatCharPrint();  
}

// SIMPLE CHECKS (:-, SCHEMES, FACTS, RULES, QUERIES)
void Lexer::ColonCheck(std::vector<std::string> inVec, int x, int y) {
  std::stringstream ss;
  if(inVec[x][y + 1] == '-') {
    ss << inVec[x][y] << inVec[x][y + 1];
    Token tok(ss.str(), x + 1, COLON_DASH);
    tokenVec.push_back(tok);
    tok.FormatPrint();
  }
  else {
    Token tok(inVec[x][y], x + 1, COLON);
    tokenVec.push_back(tok);
    tok.FormatCharPrint();
  }
}
void Lexer::SchemeCheck(std::vector<std::string> inVec, int x, int y) {
  std::stringstream ss;
  if(!std::isprint(inVec[x][y-1]) && inVec[x][y] == 'S' && inVec[x][y + 1] == 'c' &&
     inVec[x][y + 2] == 'h' && inVec[x][y + 3] == 'e' && inVec[x][y + 4] == 'm' &&
     inVec[x][y + 5] == 'e' && inVec[x][y + 6] == 's') {
    
    ss << inVec[x][y] << inVec[x][y + 1]; // Sc
    ss << inVec[x][y + 2] << inVec[x][y + 3]; //he
    ss << inVec[x][y + 4] << inVec[x][y + 5]; //me
    ss << inVec[x][y + 6]; //s
    Token tok(ss.str(), x + 1, SCHEMES);
    tokenVec.push_back(tok);
    tok.FormatPrint();
  }
}
void Lexer::FactCheck(std::vector<std::string> inVec, int x, int y) {
  std::stringstream ss;
  if(!std::isprint(inVec[x][y-1]) && inVec[x][y] == 'F' && inVec[x][y+1] == 'a' &&
     inVec[x][y+2] == 'c' && inVec[x][y+3] == 't' && inVec[x][y+4] == 's' && !std::isalnum(inVec[x][y + 5])) {
    
    ss << inVec[x][y] << inVec[x][y + 1] << inVec[x][y + 2] << inVec[x][y + 3] << inVec[x][y + 4];
    Token tok(ss.str(), x + 1, FACTS);
    tokenVec.push_back(tok);
    tok.FormatPrint();
  }
}
void Lexer::RulesCheck(std::vector<std::string> inVec, int x, int y) {
  std::stringstream ss;
  if(!std::isprint(inVec[x][y-1]) && inVec[x][y] == 'R' && inVec[x][y + 1] == 'u' &&
     inVec[x][y + 2] == 'l' && inVec[x][y + 3] == 'e' && inVec[x][y + 4] == 's' && !std::isalnum(inVec[x][y + 5])) {
    
    ss << inVec[x][y] << inVec[x][y + 1] << inVec[x][y + 2] << inVec[x][y + 3] << inVec[x][y + 4];
    Token tok(ss.str(), x + 1, RULES);
    tokenVec.push_back(tok);
    tok.FormatPrint();
  }
}
void Lexer::QueriesCheck(std::vector<std::string> inVec, int x, int y) {
  std::stringstream ss;
  if(!std::isprint(inVec[x][y - 1]) && inVec[x][y] == 'Q' && inVec[x][y + 1] == 'u' &&
     inVec[x][y + 2] == 'e' && inVec[x][y + 3] == 'r' && inVec[x][y + 4] == 'i' &&
     inVec[x][y + 5] == 'e' && inVec[x][y + 6] == 's' && !std::isalnum(inVec[x][y + 5])) {
    
    ss << inVec[x][y] << inVec[x][y + 1] << inVec[x][y + 2] << inVec[x][y + 3] << inVec[x][y + 4] <<
      inVec[x][y + 5] << inVec[x][y + 6];
    Token tok(ss.str(), x + 1, QUERIES);
    tokenVec.push_back(tok);
    tok.FormatPrint();
  }
}

// COMPLEX CASES

void Lexer::StringCheck(std::vector<std::string> inVec, int x, int y) {
  int charCount(1);  
  std::stringstream ss;
  
  ss << "'";
  for(int i = 1; i < inVec[x].length(); i++) {
    if(inVec[x][y + i] != '\''){
      charCount = 1;
    }
    else { charCount = 2; }
  }
  if(charCount == 2) {
    int z(1);
    while(inVec[x][y + z] != '\'') {
      ss << inVec[x][y + z];
      z++;
    }
    ss << "'";
    Token tok(ss.str(), x + 1, STRING);
    tokenVec.push_back(tok);
    tok.FormatPrint();
  }
}

void Lexer::CommentCheck(std::vector<std::string> inVec, int x, int y) {
  std::stringstream ss;
  int i(1);
  
  ss << '#';
  while(!(std::iscntrl(inVec[x][y + i])) /*inVec[x][y + i] != '\n'*/ ) {
    ss << inVec[x][y + i];
    i++;
  }

  Token tok(ss.str(), x + 1, COMMENT);
  tokenVec.push_back(tok);
  tok.FormatPrint();
}

/*void Lexer::IDCheck(std::vector<std::string> inVec, int x, int y) {
  std::stringstream ss;
  int i(0);
  
  while(!(std::iscntrl(inVec[x][y + i]))) {
    ss << inVec[x][y + i];
    i++;
    }
  Token tok(ss.str(), x + 1, ID);
  tokenVec.push_back(tok);
  tok.FormatPrint();
}*/
