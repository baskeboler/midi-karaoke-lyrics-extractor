#if !defined(LYRICS_SERIALIZER_H)
#define LYRICS_SERIALIZER_H
#include "lyrics.h"
#include <memory>
#include <string>
#include <exception>

class LyricsSerializer {

public:
  std::shared_ptr<Lyrics> load(const std::string &file_path);
  void save(const std::shared_ptr<Lyrics> lyrics, const std::string &file_path);
};

#endif // LYRICS_SERIALIZER_H
