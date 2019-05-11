#if !defined(LYRICS_EVENT_H)
#define LYRICS_EVENT_H
#include <iostream>
#include <string>
#include <vector>

using std::ostream;
using std::string;
using std::vector;

struct LyricEvent {
  double timestamp;
  string text;
  LyricEvent() = default;
  LyricEvent(const LyricEvent &o) = default;
  LyricEvent(LyricEvent &&o) { *this = std::move(o); };
  LyricEvent &operator=(LyricEvent &&evt) {
    *this = std::move(evt);
    return *this;
  }
  LyricEvent &operator=(const LyricEvent &evt) {
    timestamp = evt.timestamp;
    text = evt.text;
    return *this;
  }

  LyricEvent(const double _t, const string &_s) : timestamp(_t), text(_s) {}

  ~LyricEvent() = default;
};

struct LyricFrame {
  double timestamp;
};
#endif // LYRICS_EVENT_H
