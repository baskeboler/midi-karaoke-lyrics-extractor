
#include "lyrics.h"
#include <iostream>
#include <jansson.h>
#include <sstream>
#include <string>
#include <vector>
// #include <MidiFile.h>
// using smf::MidiFile;
#include "lyrics_extractor.h"
#include "lyrics_serializer.h"
#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>

using namespace boost::program_options;
namespace fs = boost::filesystem;

struct inputs {
  std::vector<fs::path> input_files;
  fs::path output_directory;
  inputs(const std::vector<fs::path> &_files, const fs::path &_output_directory)
      : input_files{_files}, output_directory{_output_directory} {}
};

std::shared_ptr<inputs> get_inputs(const variables_map &vm) {
  std::vector<fs::path> files;
  fs::path out_dir = fs::current_path() / "output_dir";

  if (vm.count("input-directory")) {
    fs::recursive_directory_iterator dir{vm["input-directory"].as<fs::path>()};
    // std::cout << "dir contents: " << std::endl;

    for (auto f : dir) {
      if (fs::is_regular_file(f) && fs::extension(f) == ".mid") {

        files.push_back(f);
      }
    }
    std::cout << "files included" << std::endl;
    for (auto f : files) {
      std::cout << f.string() << std::endl;
    }
  }
  if (vm.count("output-directory")) {
    out_dir = vm["output-directory"].as<fs::path>();
    if (out_dir.is_relative()) {
      out_dir = fs::absolute(out_dir);
    }
  }
  if (!fs::exists(out_dir)) {
    std::cout << out_dir << " does not exists, creating" << std::endl;
    fs::create_directory(out_dir);
  }
  return std::make_shared<inputs>(files, out_dir);
}

// namespace po = boost::program_options;
int main(int argc, char **argv) {
  options_description allowed("options");
  allowed.add_options()("input-directory,i", value<fs::path>(),
                        "input directory")(
      "output-directory,o", value<fs::path>(),
      "output directory in which to save json files")("help,h", "show help");
  variables_map vm;
  store(parse_command_line(argc, argv, allowed), vm);
  if (vm.count("help")) {
    std::cout << allowed << std::endl;
    return 1;
  }
  auto ins = get_inputs(vm);

  LyricsExtractor extractor;
  LyricsSerializer serializer;
  if (ins->input_files.empty() == false) {
    for (auto f : ins->input_files) {
      auto output_file =
          ins->output_directory / f.filename().replace_extension(".json");

      std::cout << "processing " << f.string() << std::endl;
      try {
        auto l = extractor.extract_from_midi_file(f.string());
        if (l->get_evts().empty()) {
          std::cout << "Could not extract valid lyrics data from " << f.string()
                    << std::endl;
        } else {
          serializer.save(l, output_file.string());
          std::cout << "Generated " << output_file.string() << std::endl;
        }

      } catch (std::exception &e) {
        std::cout << "There was an error: " << e.what() << std::endl;
      }
    }
  }

  return 0;
}
