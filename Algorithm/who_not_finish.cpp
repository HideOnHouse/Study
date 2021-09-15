#include <string>
#include <vector>
#include <unordered_map>

std::string solution(std::vector<std::string> participant, std::vector<std::string> completion) {
    std::unordered_map<std::string, int> hash_map;
    std::string answer;
    for (const auto &item : participant) {
        auto iter = hash_map.find(item);
        if (iter != hash_map.end()) {
            iter->second += 1;
        } else {
            hash_map.insert(std::unordered_map<std::string, int>::value_type(item, 1));
        }
    }
    for (const auto &item : completion) {
        auto iter = hash_map.find(item);
        if (iter != hash_map.end()) {
            iter->second -= 1;
        }
    }
    for (const auto &item : hash_map) {
        if (item.second != 0) {
            answer = item.first;
            break;
        }
    }
    return answer;
}