#include "lyrics.h"

double Lyrics::get_length() const { return length; }
string Lyrics::get_name() const { return name; }
vector<LyricEvent> Lyrics::get_evts() const { return evts; }
void Lyrics::set_length(double _length) { length = _length; }
void Lyrics::set_name(string _name) { name = _name; }
void Lyrics::set_evts(vector<LyricEvent> _evts) { evts = _evts; }
