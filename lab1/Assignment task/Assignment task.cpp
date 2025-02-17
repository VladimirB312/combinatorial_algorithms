#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

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

	for (size_t i = current + 1; i < stateSize; i++) {
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
	do {
		if (CheckGroup(state, requiredSkills, persons)) {
			return true;
		}
	} while (NextCombinations(state, persons.size()));

	return false;
}

void FindMinGroup(const std::vector<int>& requiredSkills, const std::vector<std::vector<int>>& persons) {
	std::vector<int> state;

	for (int i = 0; i < persons.size(); i++) {
		state.push_back(i);
		ResetState(state);
		if (IsGroupSkillsEnough(requiredSkills, state, persons)) {
			std::cout << "Minimum number of people needed to complete the task = " << state.size() << "\n";
			return;
		}
	}

	std::cout << "No people to complete the task\n";
}

std::vector<std::vector<int>> ParsePersons(const std::string& fileName)
{
	std::ifstream inputFile(fileName);
	if (!inputFile.is_open())
	{
		throw std::invalid_argument("Failed to open file: " + fileName + "\n");
	}

	std::vector<std::vector<int>> persons;
	std::string line;
	while (std::getline(inputFile, line))
	{
		std::vector<int> person;
		std::stringstream skills(line);
		int skillNum;
		while (skills >> skillNum)
		{
			if (skills.fail())
			{
				throw std::runtime_error("Invalid format skills\n");
			}
			person.push_back(skillNum);
		}
		persons.push_back(person);
	}

	return persons;
}

std::vector<int> GetSkillsArray(int skillsNum)
{
	std::vector<int> requiredSkills;
	for (int i = 0; i < skillsNum; i++) {
		requiredSkills.push_back(1);
	}

	return requiredSkills;
}

int main() {
	int skillsNum = 8;
	std::vector<int> requiredSkills = GetSkillsArray(skillsNum);

	try {
		std::vector<std::vector<int>> persons = ParsePersons("Persons2.txt");
		FindMinGroup(requiredSkills, persons);
	}
	catch (std::exception& ex) {
		std::cout << ex.what() << "\n";
		return 1;
	}

	return 0;
}