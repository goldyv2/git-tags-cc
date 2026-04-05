#include <string>
#include <optional>
#include <iostream>
#include <algorithm>

enum Platform {
    GITHUB,
};

class GitTag {
    public:
        std::string owner;
        std::optional<std::string> repo;
        Platform platform;
};

std::optional<Platform> parse_platform_tag(std::string platform_tag_string) {
    platform_tag_string.erase(
        remove_if(platform_tag_string.begin(), platform_tag_string.end(), isspace),
        platform_tag_string.end()
    );

    if (platform_tag_string == "gh") return Platform::GITHUB;

    return std::nullopt;
}

std::optional<GitTag> parse_git_tag_string(std::string git_tag_string) {
    int at_position = git_tag_string.find("@");

    if (at_position == std::string::npos) {
        return std::nullopt;
    }

    std::string platform_tag = git_tag_string.substr(at_position + 1);

    std::optional<Platform> platform = parse_platform_tag(platform_tag);

    if (platform == std::nullopt) {
        std::cerr << "Failed to parse platform tag!" << std::endl;
        return std::nullopt;
    }

    int owner_repo_split_position = git_tag_string.find("/");

    std::optional<std::string> repo = std::nullopt;
    std::string owner = git_tag_string.substr(0, at_position - 1);

    if (owner_repo_split_position != std::string::npos) {
        repo = git_tag_string.substr(owner_repo_split_position + 1, (at_position - owner_repo_split_position) - 1);
        owner = git_tag_string.substr(0, owner_repo_split_position);
    }

    owner.erase(remove_if(owner.begin(), owner.end(), isspace), owner.end());

    if (repo != std::nullopt) {
        std::string repo_ptr = *repo;
        repo_ptr.erase(remove_if(repo_ptr.begin(), repo_ptr.end(), isspace), repo_ptr.end());
    }

    GitTag git_tag = {owner, repo, Platform::GITHUB};

    return git_tag;
}