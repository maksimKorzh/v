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
  getmaxyx(stdscr, R, C); R--; vector<int> row;
  if (argc == 2) src = argv[1]; else b.push_back(row);
  try { vector<int> row;
    ifstream ifs(src); string cont((istreambuf_iterator<char>(ifs)),
    (istreambuf_iterator<char>()));
    
    for (int i = 0; i < cont.size(); i++) {
      if (cont[i] == '\n') { b.push_back(row); row.clear(); }
      else row.push_back(cont[i]); 
    }
    if (row.size()) b.push_back(row);
  ifs.close(); 
  } catch (exception &e) {}
    
  if (src != "noname.txt" && b.size() == 0) b.push_back(row);
  while (TRUE) {
    if (r < y) y = r; if (r >= y + R) y = r - R+1;
    if (c < x) x = c; if (c >= x + C) x = c - C+1;
    move(0, 0); for (int row = 0; row < R; row++) {
    int brw = row + y; for (int col = 0; col < C; col++) {
    int bcl = col + x; if (brw < b.size() && bcl < b[brw].size())
    addch(b[brw][bcl]); } clrtoeol(); addstr(brw < b.size()-1 ? "\n" : "\n~"); }
    string stat = mod + " \"" + src + "\" " + to_string(r+1) + "/" + to_string(b.size());
    stat += b.size() ? " --" + to_string((int)((r+1)*100/b.size())) + "%-- " : "";
    stat += "col " + to_string(c+1) + " --x" + (cnt.length() ? cnt : "1") + "--";
    move(R, 0); for (int i = 0; i < stat.length(); i++) addch(stat[i]);
    clrtoeol(); curs_set(0); move(r - y, c - x); curs_set(1); refresh();
    int ch = -1; while (ch == -1) ch = getch(); string modes = "irR";
    if (isdigit(ch) && !(modes.find(mod[0]) != string::npos)) cnt += ch;
    if (ch == ('[' & 0x1f)) { mod = 'n'; cnt = ""; continue; } int times = atoi(cnt.c_str());
    if (mod == "n") {
      if (ch == 'i') { mod = "i"; continue; }
      else if (ch == 'q') break; else if (ch == 'w') {
        ofstream ofs(src, ofstream::out); string cont = "";
        for (int row = 0; row < b.size(); row++) {
          string line = "";
          for (int col = 0; col < b[r].size(); col++) {
            char c = b[row][col];
            line += "x";
          }
          cont += line + "\n";
        }
        ofs << cont;
        ofs.close();
      } else {
        switch (ch) {
          case 'h': c ? c-- : c; break;
          case 'j': r < b.size()-1 ? r++ : r; break;
          case 'k': r ? r-- : r; break;
          case 'l': c < b[r].size()-1 ? c++ : c; break;
        }
        int rwl = r < b.size() ? b[r].size() : 0; if (c > rwl -1) c = rwl ? rwl-1 : rwl;
        if (c == 0 || c == b[r].size()-1 || r == 0 || r == b.size()-1) cnt = "";
      }
    } else if (mod == "i") {
      if (ch == '\n') {
        vector<int> right(b[r].size() - c); vector<int> left(c);
        copy(b[r].begin() + c, b[r].begin() + b[r].size(), right.begin());
        copy(b[r].begin(), b[r].begin() + c, left.begin()); b[r].clear();
        b[r] = left; r++; c = 0; b.insert(b.begin() + r, right); left.clear(); right.clear();
      } else if (ch == KEY_BACKSPACE || ch == '\b' || ch == 127) {
        if (c) { c--; b[r].erase(b[r].begin() + c); }
        else if (r) {
          vector<int> right(b[r].size() - c); vector<int> left(c);
          copy(b[r].begin() + c, b[r].begin() + b[r].size(), right.begin());
          copy(b[r].begin(), b[r].begin() + c, left.begin()); b.erase(b.begin() + r);
          r--; c = b[r].size(); b[r].insert(b[r].end(), right.begin(), right.end());
          left.clear(); right.clear();
        }
      } else if (ch != (ch & 0x1f) && ch < 128) { b[r].insert(b[r].begin() + c, ch); c++; }
    }
    
    if (ch == KEY_RESIZE) { getmaxyx(stdscr, R, C); R--; r = c = 0; refresh(); }
  }
  endwin();
  b.clear();
  return 0;
}
