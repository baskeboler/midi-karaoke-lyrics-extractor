#include "lyrics_extractor.h"
#include "lyrics_event.h"
#include <MidiFile.h>
#include <numeric>

using smf::MidiFile;

std::shared_ptr<Lyrics>
LyricsExtractor::extract_from_midi_file(const std::string &file_path) {
  MidiFile midifile;
  midifile.read(file_path);
  if (!midifile.status()) {
    std::cerr << "Problem reading MIDI file" << std::endl;
    throw std::invalid_argument("failed to read midi file");
    ;
  }
  midifile.joinTracks();
  midifile.doTimeAnalysis();
  std::vector<LyricEvent> events;
  auto pos1 = file_path.find_last_of('/');

  std::string name = file_path;
  name = name.erase(0, pos1);
  double length = midifile.getFileDurationInSeconds();
  for (int i = 0; i < midifile[0].getEventCount(); i++) {
    if (midifile[0][i].isLyricText()) {
      string content = midifile[0][i].getMetaContent();
      double offset = midifile[0][i].seconds;

      auto evt = new LyricEvent{offset, content};
      events.push_back(*evt);
    }
  }
  // std::reduce(events.begin(), events.end(), std::_Identity);
  return std::make_shared<Lyrics>(length, name, events);
}
