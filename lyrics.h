#if !defined(LYRICS_H)
#define LYRICS_H
// #include <boost/archive/basic_archive.hpp>
#include <iostream>
#include <string>
#include <vector>
// #include <boost/property_tree/ptree.hpp>
#include "lyrics_event.h"

using std::ostream;
using std::string;
using std::vector;


class Lyrics {
  double length;
  string name;
  vector<LyricEvent> evts;

public:
  Lyrics(const double _length, const string &_name,
         const vector<LyricEvent> &_evts)
      : length(_length), name{_name}, evts(_evts) {}
  Lyrics() : Lyrics(0, "", {}) {}
  Lyrics(const Lyrics &o) = default;
  Lyrics(Lyrics &&o) = default;

  double get_length() const;
  string get_name() const;
  vector<LyricEvent> get_evts() const;
  void set_length(double length);
  void set_name(string name);
  void set_evts(vector<LyricEvent> evts);
};

#endif // LYRICS_H
