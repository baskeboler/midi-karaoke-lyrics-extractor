#if !defined(LYRICS_EXTRACTOR_H)
#define LYRICS_EXTRACTOR_H
#include "lyrics.h"
#include <memory>
#include <string>

class LyricsExtractor {
public:
  std::shared_ptr<Lyrics> extract_from_midi_file(const std::string &file_path);
};

#endif // LYRICS_EXTRACTOR_H
