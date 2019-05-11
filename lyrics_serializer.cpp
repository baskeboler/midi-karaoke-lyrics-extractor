#include "lyrics_serializer.h"
#include <jansson.h>

std::shared_ptr<Lyrics> LyricsSerializer::load(const std::string &file_path) {
  json_error_t error;
  json_t *json = json_load_file(file_path.c_str(), 0, &error);

  double length = json_real_value(json_object_get(json, "length"));
  const std::string name =
      std::string(json_string_value(json_object_get(json, "name")));
  std::vector<LyricEvent> events;
  json_t *value = nullptr;
  int index = 0;
  json_array_foreach(json_object_get(json, "events"), index, value) {
    double offset = json_real_value(json_object_get(value, "offset"));
    const std::string text(json_string_value(json_object_get(value, "text")));
    events.push_back(LyricEvent{offset, text});
  }
  return std::make_shared<Lyrics>(length, name, events);
}
void LyricsSerializer::save(const std::shared_ptr<Lyrics> lyrics,
                            const std::string &file_path) {
  json_t *json = json_object();

  json_object_set(json, "name", json_string(lyrics->get_name().c_str()));
  json_object_set(json, "length", json_real(lyrics->get_length()));
  json_t *evts = json_array();
  for (auto event : lyrics->get_evts()) {
    // if (midifile[0][i].isLyricText()) {
    //   string content = midifile[0][i].getMetaContent();
    //   double offset = midifile[0][i].seconds;
    //   std::cout << offset << " -- " << content << std::endl;

    json_t *e = json_object();
    json_object_set(e, "text", json_string(event.text.c_str()));
    json_object_set(e, "offset", json_real(event.timestamp));

    json_object_set(e, "char_count", json_integer(event.text.length()));
    json_array_append(evts, e);
    // }
  }
  json_object_set(json, "events", evts);

#ifdef _DEBUG

  json_dump_file(json, file_path.c_str(), JSON_INDENT(2));
#else
  json_dump_file(json, file_path.c_str(), 0);
#endif // _DEBUG

  json_decrefp(&json);
}
