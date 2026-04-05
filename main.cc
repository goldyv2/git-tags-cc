#include <string>
#include <optional>
#include <iostream>

#include "main.hh"

int main(int argc, char const *argv[])
{
    std::string git_user_test_tag = "THEGOLDENPRO @ gh";
    std::string git_user_repo_test_tag = "THEGOLDENPRO/aghpb-api @ gh";
    std::string git_org_repo_test_tag = "cloudy-org/roseate @ gh";

    std::optional<GitTag> git_tag = parse_git_tag_string(git_user_repo_test_tag);

    if (git_tag == std::nullopt) {
        std::cout << "Failed!" << std::endl;
        return 1;
    }

    std::cout << "Owner: " << git_tag->owner << std::endl;

    std::string repo_string = "no repo";

    if (git_tag->repo != std::nullopt) {
        repo_string = *git_tag->repo;
    }

    std::cout << "Repo: " << repo_string << std::endl;
    std::cout << "Platform: " << git_tag->platform << std::endl;

    return 0;
}