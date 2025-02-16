#include <iostream>
#include <vector>

void PrintArray(const std::vector<int>& arr) {
    for (const auto element : arr) {
        std::cout << element << " ";
    }
    std::cout << "\n";
}

void ResetState(std::vector<int>& state) {
    for (int i = 0; i < state.size(); i++) {
        state[i] = i;
    }
}

bool NextCombinations(std::vector<int>& state, size_t dim) {
    size_t current = state.size() - 1;
    const size_t stateSize = state.size();

    while (state[current] == dim - stateSize + current) {   
        if (current == 0) {
            return false;
        }
        current--;
    }    

    state[current]++;

    for (int i = current + 1; i < stateSize; i++) {
        state[i] = state[i - 1] + 1;
    }

    return true;
}

bool CheckGroup(const std::vector<int>& state, const std::vector<int>& requiredSkills,
    const std::vector<std::vector<int>>& persons) {
    std::vector<int> groupSkills(requiredSkills.size(), 0);

    for (const auto personIndex : state) {
        for (const auto personSkill : persons[personIndex]) {
            if (personSkill >= groupSkills.size()) {
                continue;
            }
            groupSkills[personSkill] = 1;
        }
    }

    return groupSkills == requiredSkills;
}

bool IsGroupSkillsEnough(const std::vector<int>& requiredSkills, std::vector<int>& state,
    const std::vector<std::vector<int>>& persons) {
    bool found = false;
    do {
        if (CheckGroup(state, requiredSkills, persons)) {
            found = true;
            std::cout << "Indexes of persons who have enough skills to complete the task: ";
            PrintArray(state);
        }
    } while (NextCombinations(state, persons.size()));

    return found;
}

void FindMinGroup(const std::vector<int>& requiredSkills, const std::vector<std::vector<int>>& persons) {
    std::vector<int> state;

    for (int i = 0; i < persons.size(); i++) {
        state.push_back(i);
        ResetState(state);
        if (IsGroupSkillsEnough(requiredSkills, state, persons)) {
            std::cout << "The minimum number required to complete the task is " << state.size() << "\n";
            return;
        }
    }

    std::cout << "No people to complete the task\n";
}

int main() {
    int skillsNum = 8;
    std::vector<int> requiredSkills;
    {
        for (int i = 0; i < skillsNum; i++) {
            requiredSkills.push_back(1);
        }
    }

    std::vector<int> person1 = { 0, 1, 2 };
    std::vector<int> person2 = { 3, 4, 5 };
    std::vector<int> person3 = { 6, 7 };
    std::vector<int> person4 = { 0, 1, 2, 6, 7 };
    std::vector<int> person5 = { 3, 4 };
    std::vector<int> person6 = { 3, 4, 5, 6 };

    // std::vector<int> person1 = {0, 1, 2};
    // std::vector<int> person2 = {3};
    // std::vector<int> person3 = {5};
    // std::vector<int> person4 = {6};
    // std::vector<int> person5 = {4};
    // std::vector<int> person6 = {9};

    std::vector<std::vector<int>> persons = { person1, person2, person3, person4, person5, person6 };

    FindMinGroup(requiredSkills, persons);
    return 0;
}