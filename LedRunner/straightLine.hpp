#ifndef LINE_HPP
#define LINE_HPP

#include "Screen.hpp"
#include "vector.hpp"

class straightLine {
public:
   straightLine( Screen & w, vector start, vector end, int color ):
      w( w ),
      start( start ),
      end( end ),
	  color (color)
   {}
   void print();
   void setColor(uint32_t c){
	   color = c;
   }
   
   
private:
	Screen &w;
	vector start;
	vector end;
	uint32_t color;
};

#endif // LINE_HPP
