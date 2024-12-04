#include <cassert>
#include <filesystem>
#include <format>
#include <fstream>
#include <functional>
#include <print>
#include <ranges>
#include <tuple>
#include <vector>

class AoC {
  using Data = std::vector<std::string>;

public:
  explicit AoC(const std::filesystem::path &inputFile) {
    std::ifstream is(inputFile);
    if (!is.is_open()) {
      throw std::runtime_error(std::format("Failed to open file {}", inputFile.string()));
    }

    // read line by line
    std::string line;
    while (std::getline(is, line)) {
      input_.push_back(line);
    }

    height_ = input_.size();
    if (height_ > 0) {
      width_ = input_.front().size();
    }
  }

  long findString(const int x, const int y, const std::string_view s) const {
    // go east, south, south-east, and north-east
    // mirrored cases will be handled by calling this twice, once with the mirrored string
    assert(s.size() > 0);

    // creates all the indices we need to visit to check for the string
    auto createPoints = [s](const auto &pointFunc) {
      std::vector<std::pair<int, int>> points;
      points.reserve(s.size());
      for (int i = 0; i < s.size(); i++) {
        points.emplace_back(pointFunc(i));
      }
      return points;
    };

    // create points for all directions
    const auto directionPoints = {
        // east
        createPoints([x, y](const int i) { return std::pair{x + i, y}; }),
        // south
        createPoints([x, y](const int i) { return std::pair{x, y + i}; }),
        // south-east
        createPoints([x, y](const int i) { return std::pair{x + i, y + i}; }),
        // north-east
        createPoints([x, y](const int i) { return std::pair{x + i, y - i}; }),
    };

    // try all directions
    long count{0};
    for (const auto &dir: directionPoints) {
      assert(directionPoints.size() == s.size());
      int k{0};
      for (const auto [x, y] : dir) {
        // skip out of bounds
        if (x < 0 || x >= width_ || y < 0 || y >= height_) {
          goto notFound;
        }
        // skip letter mismatch
        if (input_.at(y).at(x) != s.at(k)) {
          goto notFound;
        }
        k++;
      }
      count++;
      notFound: {}
    }

    return count;
  }

  long findXMAS(const int x, const int y) const {
    static constexpr std::string_view XMAS = "XMAS";
    static constexpr std::string_view SAMX = "SAMX";

    return findString(x, y, XMAS) + findString(x, y, SAMX);
  }

  long partOne() const {
    long count{0};

    // for each character of the input, try to find 'XMAS' in all directions
    for (int y = 0; y < input_.size(); y++) {
      for (int x = 0; x < input_.at(y).size(); x++) {
        count += findXMAS(x, y);
      }
    }

    return count;
  }

private:
  Data input_;
  size_t height_;
  size_t width_;
};

int main(const int argc, char *argv[]) {
  if (argc < 2) {
    std::println(stderr, "No path to input file provided");
    return 1;
  }

  const AoC aoc{argv[1]};
  std::println("Answer 1: {}", aoc.partOne());

  return 0;
}
