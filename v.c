#include <ncurses.h>
#include <algorithm>
#include <ctype.h>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
int R, C, r, c, y, x, com;
string src = "noname.txt", mod = "n", cnt = "";
vector<vector<int>> b = {};
int main(int argc, char **argv) {
  initscr(); nodelay(stdscr, TRUE); noecho(); raw(); 
  getmaxyx(stdscr, R, C); R--;
  if (argc == 2) src = argv[1];
  try { vector<int> row;
    ifstream ifs(src); string cont((istreambuf_iterator<char>(ifs)),
    (istreambuf_iterator<char>())); for (int i = 0; i < cont.size(); i++) {
    if (cont[i] == '\n') { b.push_back(row); row.clear(); }
    else row.push_back(cont[i]); }
  } catch (exception &e) {}
  while (TRUE) {
    if (r < y) y = r; if (r >= y + R) y = r - R+1;
    if (c < x) x = c; if (c >= x + C) x = c - C+1;
    move(0, 0); for (int row = 0; row < R; row++) {
    int brw = row + y; for (int col = 0; col < C; col++) {
    int bcl = col + x; if (brw < b.size() && bcl < b[brw].size())
    addch(b[brw][bcl]); } clrtoeol(); addstr(brw < b.size() ? "\n" : "\n~"); }
    string stat = mod + " \"" + src + "\" " + to_string(r+1) + "/" + to_string(b.size());
    stat += b.size() ? " --" + to_string((int)((r+1)*100/b.size())) + "%-- " : "";
    stat += "col " + to_string(c+1) + " : " + cnt;
    move(R, 0); for (int i = 0; i < stat.length(); i++) addch(stat[i]);
    clrtoeol(); curs_set(0); move(r - y, c - x); curs_set(1); refresh();
    int ch = -1; while (ch == -1) ch = getch(); string modes = "irR";
    if (isdigit(ch) && ch != '0' && !(modes.find(mod[0]) != string::npos)) cnt += ch;
    if (ch == ('[' & 0x1f)) { mod = 'n'; cnt = ""; continue; } int times = atoi(cnt.c_str());
    for (int i = 0; i < (cnt.length() ? times : 1); i++) {
      if (mod == "n") {
        switch (ch) {
          case 'i': mod == "i"; break;
          case 'h': c ? c -= 1 : c; break;
          case 'j': r < b.size() ? r += 1 : r; break;
          case 'k': r ? r -= 1 : r; break;
          case 'l': c < b[r].size()-1 ? c += 1 : c; break;
        } int rwl = r < b.size() ? b.size() : 0; if (c > rwl -1) c = rwl ? rwl-1 : rwl; 
      } else if (mod == "i") {
      
      }
    }
    if (ch == KEY_RESIZE) { getmaxyx(stdscr, R, C); R -= 1; r = c = 0; refresh(); }
    if (ch == 'q') break;
  }
  endwin();
  b.clear();
  return 0;
}
