#include <ncurses.h> //                                                                                                            111111111111111111111111111111111111111111111111111
#include <string>
#include <vector>
#include <fstream>
using namespace std;
int R, C, r, c, y, x; 
vector<vector<int>> b = {};
int main(int argc, char **argv) {
  initscr(); nodelay(stdscr, TRUE); noecho(); raw(); 
  getmaxyx(stdscr, R, C); R--; string src = "noname.txt";
  if (argc == 2) src = argv[1];
  try { vector<int> row;
    ifstream ifs(src); string cont((istreambuf_iterator<char>(ifs)),
    (istreambuf_iterator<char>())); for (int i = 0; i < cont.length(); i++)
    { if (cont[i] == '\n') { b.push_back(row); row.clear(); }
      else row.push_back(cont[i]); }
  } catch (exception &e) {}
  int ch = -1; while (TRUE) {
    if (r < y) y = r; if (r >= y + R) y = r - R+1;
    if (c < x) x = c; if (c >= x + C) x = c - C+1;
    move(0, 0); for (int row = 0; row < R; row++) {
    int brw = row + y; for (int col = 0; col < C; col++) {
    int bcl = col + x;
   
    if (brw < b.size() && bcl < b[row].size()) mvaddch(row, col, b[brw][bcl]); 
    //try { if (brw < b.size() && bcl < b[row].size()) mvaddch(row, col, b[brw][bcl]); }
    //catch (exception &e) {}
    
    }}
    //} printw("%d/%d\n\r", brw, b.size());}
    while (ch == -1) ch = getch();    
    if (ch == ('q' & 0x1f)) break;
  }
  endwin();
  return 0;
}












//
//
//
//
