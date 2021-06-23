#ifndef IsE_Hacker
#define IsE_Hacker
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "SFML_input_controls.hpp"

//!-----------------------------------------------------------------
//! Reads buffers from com file and outs pssword to out
//!
//! @param [in] filename - name of com file
//!
//! @param [in] firstBuffBegin  - number of beginning byte of first  buffer
//! @param [in] secondBuffBegin - number of beginning byte of second buffer
//! @param [in] thirdBuffBegin  - number of beginning byte of third  buffer
//!
//! @param [in] number of nops to write
//!-----------------------------------------------------------------

unsigned char* ReadAndSolvePassword (const char* filename, const int firstBuffBegin, const int secondBuffBegin, const int thirdBuffbegin, const int buffSize);

//!-----------------------------------------------------------------
//! Counts required symbol of code
//!
//! @param [in] oursymb - the previous symbol of password 
//! @param [in] theirSymb - the symbol we want to get
//! @param [in] current - symbol we checks for
//!
//! @return symbol that was counted
//!-----------------------------------------------------------------

unsigned char CalcSymb (unsigned char ourSymb, unsigned char theirSymb, unsigned char current);

//!-----------------------------------------------------------------
//! Counts required symbols of code
//!
//! @param [in] previous - the previous symbol of password
//! @param [in] passSymbPrevious - the previous symbol of password
//! @param [in] passSynbCurrent  - the current symbol of password
//!-----------------------------------------------------------------

unsigned char SolvePassword (unsigned char previous, unsigned char passSymbPrevious, unsigned char passSymbCurrent);

//!-----------------------------------------------------------------
//! rewrites com file
//!
//! @param [in] filename - the name of com file
//! @param [in] weekAddress - number of beginning of checcings
//! @param [in] nNops - number of nops
//!-----------------------------------------------------------------

void crushCode (char* fileName, int weekAddress, int nNops);

//!-----------------------------------------------------------------
//! ROR - equivalent of ror in asm
//! 
//! @param [in] a - what will be ror
//! @param [in] b - on how much bits will be ror
//!
//! @return result of ror
//!-----------------------------------------------------------------

unsigned char ROR (unsigned char a, unsigned char b);

//!-----------------------------------------------------------------
//! ROR - equivalent of ror in asm
//! 
//! @param [in] a - what will be rol
//! @param [in] b - on how much bits will be rol
//!
//! @return result of rol
//!-----------------------------------------------------------------

unsigned char ROL (unsigned char a, unsigned char b);

int launchCracker ();

void CoockieSet (InteractiveObject* buffer, const int SizeOfBuffer,sf :: RenderWindow& window, const sf :: Time& delta, sf :: Event& event);
int CheckCoockieClicked (InteractiveObject* buffer, const int SizeOfBuffer,sf :: RenderWindow& window, const sf :: Time& delta, sf :: Event& event, sf :: Sprite& sprite1,  sf :: Sprite& sprite2);
void respawncoockie (InteractiveObject* coockie, const sf :: Window& window);


#endif