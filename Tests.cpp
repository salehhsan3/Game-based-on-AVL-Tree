#include "library1.h"
#include <assert.h>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <vector>
#include <random>
#include <chrono>
#include <algorithm>

void TEST_INVALID_INPUT()
{
	void* DS = Init();
	int playerId = 0;
	int numOfPlayers = 0;
	int* players = nullptr;

	(void)playerId;
	(void)numOfPlayers;
	(void)players;

	assert(AddGroup(nullptr, 1) == INVALID_INPUT);
	assert(AddGroup(DS, 0) == INVALID_INPUT);
	assert(AddGroup(DS, -1) == INVALID_INPUT);

	assert(AddPlayer(nullptr, 1, 1, 1) == INVALID_INPUT);
	assert(AddPlayer(DS, 0, 1, 1) == INVALID_INPUT);
	assert(AddPlayer(DS, -1, 1, 1) == INVALID_INPUT);
	assert(AddPlayer(DS, 1, 0, 1) == INVALID_INPUT);
	assert(AddPlayer(DS, 1, -1, 1) == INVALID_INPUT);
	assert(AddPlayer(DS, 1, 1, -1) == INVALID_INPUT);

	assert(RemovePlayer(nullptr, 1) == INVALID_INPUT);
	assert(RemovePlayer(DS, 0) == INVALID_INPUT);
	assert(RemovePlayer(DS, -1) == INVALID_INPUT);

	assert(ReplaceGroup(nullptr, 1, 2) == INVALID_INPUT);
	assert(ReplaceGroup(DS, 0, 2) == INVALID_INPUT);
	assert(ReplaceGroup(DS, -1, 2) == INVALID_INPUT);
	assert(ReplaceGroup(DS, 1, 0) == INVALID_INPUT);
	assert(ReplaceGroup(DS, 1, -1) == INVALID_INPUT);
	assert(ReplaceGroup(DS, 1, 1) == INVALID_INPUT);

	assert(IncreaseLevel(nullptr, 1, 1) == INVALID_INPUT);
	assert(IncreaseLevel(DS, 0, 1) == INVALID_INPUT);
	assert(IncreaseLevel(DS, -1, 1) == INVALID_INPUT);
	assert(IncreaseLevel(DS, 1, 0) == INVALID_INPUT);
	assert(IncreaseLevel(DS, 1, -1) == INVALID_INPUT);

	assert(GetHighestLevel(nullptr, 1, &playerId) == INVALID_INPUT);
	assert(GetHighestLevel(DS, 1, nullptr) == INVALID_INPUT);
	assert(GetHighestLevel(DS, 0, &playerId) == INVALID_INPUT);

	assert(GetAllPlayersByLevel(nullptr, 1, &players, &numOfPlayers) == INVALID_INPUT);
	assert(GetAllPlayersByLevel(DS, 1, nullptr, &numOfPlayers) == INVALID_INPUT);
	assert(GetAllPlayersByLevel(DS, 1, &players, nullptr) == INVALID_INPUT);
	assert(GetAllPlayersByLevel(DS, 0, &players, &numOfPlayers) == INVALID_INPUT);

	assert(GetGroupsHighestLevel(nullptr, 1, &players) == INVALID_INPUT);
	assert(GetGroupsHighestLevel(DS, 1, nullptr) == INVALID_INPUT);
	assert(GetGroupsHighestLevel(DS, 0, &players) == INVALID_INPUT);
	assert(GetGroupsHighestLevel(DS, -1, &players) == INVALID_INPUT);

	Quit(&DS);

	printf("TEST_INVALID_INPUT - SUCCESS\n");
}

void TEST_FAILURE()
{
	void* DS = Init();
	int playerId = 0;
	int numOfPlayers = 0;
	int* players = nullptr;

	(void)playerId;
	(void)numOfPlayers;
	(void)players;

	assert(AddGroup(DS, 1) == SUCCESS);
	assert(AddGroup(DS, 2) == SUCCESS);
	assert(AddGroup(DS, 1) == FAILURE);

	assert(AddPlayer(DS, 1, 1, 1) == SUCCESS);
	assert(AddPlayer(DS, 2, 2, 2) == SUCCESS);
	assert(AddPlayer(DS, 1, 1, 1) == FAILURE);
	assert(AddPlayer(DS, 5, 5, 1) == FAILURE);

	assert(RemovePlayer(DS, 1) == SUCCESS);
	assert(RemovePlayer(DS, 5) == FAILURE);
	assert(RemovePlayer(DS, 1) == FAILURE);

	assert(AddPlayer(DS, 1, 1, 1) == SUCCESS);

	assert(ReplaceGroup(DS, 1, 5) == FAILURE);
	assert(ReplaceGroup(DS, 5, 1) == FAILURE);
	assert(ReplaceGroup(DS, 2, 1) == SUCCESS);

	assert(RemovePlayer(DS, 2) == SUCCESS);
	assert(AddGroup(DS, 2) == SUCCESS);
	assert(AddPlayer(DS, 2, 2, 2) == SUCCESS);

	assert(IncreaseLevel(DS, 5, 1) == FAILURE);
	assert(IncreaseLevel(DS, 2, 1) == SUCCESS);

	assert(GetHighestLevel(DS, 5, &playerId) == FAILURE);
	assert(GetHighestLevel(DS, 2, &playerId) == SUCCESS);

	assert(GetAllPlayersByLevel(DS, 5, &players, &numOfPlayers) == FAILURE);
	assert(GetAllPlayersByLevel(DS, 2, &players, &numOfPlayers) == SUCCESS);

	free(players);

	assert(GetGroupsHighestLevel(DS, 3, &players) == FAILURE);
	assert(GetGroupsHighestLevel(DS, 2, &players) == SUCCESS);

	free(players);
	Quit(&DS);

	printf("TEST_FAILURE - SUCCESS\n");
}

void TEST_SCENARIO_1()
{
	void* DS = Init();
	int playerId = 0;
	int numOfPlayers = 0;
	int* players = nullptr;

	(void)playerId;
	(void)numOfPlayers;
	(void)players;

	assert(AddGroup(DS, 1) == SUCCESS);
	assert(AddPlayer(DS, 1, 1, 1) == SUCCESS);

	assert(AddGroup(DS, 2) == SUCCESS);
	assert(AddPlayer(DS, 2, 2, 4) == SUCCESS);

	assert(GetGroupsHighestLevel(DS, 2, &players) == SUCCESS);
	assert(players[0] == 1);
	assert(players[1] == 2);

	free(players);

	assert(ReplaceGroup(DS, 1, 2) == SUCCESS);

	assert(GetHighestLevel(DS, 2, &playerId) == SUCCESS);
	assert(playerId == 2);

	assert(IncreaseLevel(DS, 1, 5) == SUCCESS);

	assert(GetHighestLevel(DS, 2, &playerId) == SUCCESS);
	assert(playerId == 1);

	assert(GetAllPlayersByLevel(DS, -1, &players, &numOfPlayers) == SUCCESS);
	assert(players[0] == 1);
	assert(players[1] == 2);

	free(players);
	Quit(&DS);

	printf("TEST_SCENARIO_1 - SUCCESS\n");
}

void TEST_SCENARIO_2()
{
	void* DS = Init();
	int playerId = 0;
	int numOfPlayers = 0;
	int* players = nullptr;

	(void)playerId;
	(void)numOfPlayers;
	(void)players;

	assert(AddGroup(DS, 1) == SUCCESS);
	assert(AddGroup(DS, 3) == SUCCESS);
	assert(AddGroup(DS, 4) == SUCCESS);
	assert(AddGroup(DS, 5) == SUCCESS);
	assert(AddPlayer(DS, 111, 2, 9) == FAILURE);
	assert(AddGroup(DS, 2) == SUCCESS);
	//Adding players to group 2
	assert(AddPlayer(DS, 111, 2, 9) == SUCCESS);
	assert(AddPlayer(DS, 1000, 2, 10) == SUCCESS);
	assert(AddPlayer(DS, 1001, 2, 23) == SUCCESS);
	assert(AddPlayer(DS, 1010, 2, 3) == SUCCESS);
	assert(AddPlayer(DS, 1011, 2, 5) == SUCCESS);
	assert(AddPlayer(DS, 1100, 2, 7) == SUCCESS);
	assert(AddPlayer(DS, 1100, 2, 34) == FAILURE);
	//Adding players to group 1
	assert(AddPlayer(DS, 1, 1, 4) == SUCCESS);
	assert(AddPlayer(DS, 10, 1, 6) == SUCCESS);
	assert(AddPlayer(DS, 11, 1, 3) == SUCCESS);
	assert(AddPlayer(DS, 100, 1, 2) == SUCCESS);
	assert(AddPlayer(DS, 101, 1, 5) == SUCCESS);
	assert(AddPlayer(DS, 110, 1, 2) == SUCCESS);
	assert(AddPlayer(DS, 110, 3, 7) == FAILURE);
	//Adding players to group 3
	assert(AddPlayer(DS, 1101, 3, 5) == SUCCESS);
	assert(AddPlayer(DS, 1110, 3, 3) == SUCCESS);
	assert(AddPlayer(DS, 1111, 3, 4) == SUCCESS);
	assert(AddPlayer(DS, 10000, 3, 2) == SUCCESS);
	assert(AddPlayer(DS, 10001, 3, 6) == SUCCESS);
	assert(AddPlayer(DS, 10010, 3, 7) == SUCCESS);
	//Highest check
	assert(GetHighestLevel(DS, 1, &playerId) == SUCCESS);
	assert(playerId == 10);
	//Highest check
	assert(GetHighestLevel(DS, 2, &playerId) == SUCCESS);
	assert(playerId == 1001);
	//Highest check
	assert(GetHighestLevel(DS, 3, &playerId) == SUCCESS);
	assert(playerId == 10010);
	//Highest check
	assert(GetHighestLevel(DS, 4, &playerId) == SUCCESS);
	assert(playerId == -1);
	//Highest check
	assert(GetHighestLevel(DS, -1, &playerId) == SUCCESS);
	assert(playerId == 1001);
	//remove
	assert(RemovePlayer(DS, 10011) == FAILURE);
	assert(RemovePlayer(DS, 10000) == SUCCESS);
	assert(RemovePlayer(DS, 11) == SUCCESS);
	assert(RemovePlayer(DS, 1100) == SUCCESS);
	//Highest check
	assert(GetHighestLevel(DS, -1, &playerId) == SUCCESS);
	assert(playerId == 1001);

	assert(IncreaseLevel(DS, 10000, 1) == FAILURE);
	assert(IncreaseLevel(DS, 1100, 1) == FAILURE);

	//replace
	assert(ReplaceGroup(DS, 6, 1) == FAILURE);
	assert(ReplaceGroup(DS, 2, 1) == SUCCESS);
	//Highest check
	assert(GetHighestLevel(DS, 1, &playerId) == SUCCESS);
	assert(playerId == 1001);

	assert(AddPlayer(DS, 11111, 2, 2) == FAILURE);

	//Increase
	assert(IncreaseLevel(DS, 101, 5) == SUCCESS);
	assert(IncreaseLevel(DS, 101, -5) == INVALID_INPUT);
	assert(IncreaseLevel(NULL, 101, 5) == INVALID_INPUT);
	assert(IncreaseLevel(DS, -101, 5) == INVALID_INPUT);
	assert(IncreaseLevel(DS, 100011, 5) == FAILURE);
	assert(IncreaseLevel(DS, 1010, 7) == SUCCESS);
	assert(IncreaseLevel(DS, 1111, 8) == SUCCESS);

	//Highest check
	assert(GetHighestLevel(DS, 3, &playerId) == SUCCESS);
	assert(playerId == 1111);

	//Get all players by level
	assert(GetAllPlayersByLevel(DS, -1, &players, &numOfPlayers) == SUCCESS);
	assert(numOfPlayers == 15);
	for (int i = 0; i < numOfPlayers; i++)
	{
		printf("%d, ", players[i]);
	}
	printf("\n");
	free(players);
	//Get all players group 1 by level
	assert(GetAllPlayersByLevel(DS, 1, &players, &numOfPlayers) == SUCCESS);
	assert(numOfPlayers == 10);
	for (int i = 0; i < numOfPlayers; i++)
	{
		printf("%d, ", players[i]);
	}
	printf("\n");
	free(players);
	//Get all players group 3 by level
	assert(GetAllPlayersByLevel(DS, 3, &players, &numOfPlayers) == SUCCESS);
	assert(numOfPlayers == 5);
	for (int i = 0; i < numOfPlayers; i++)
	{
		printf("%d, ", players[i]);
	}
	printf("\n");
	free(players);
	assert(GetGroupsHighestLevel(DS, 2, &players) == SUCCESS);
	for (int i = 0; i < 2; i++)
	{
		printf("%d, ", players[i]);
	}
	printf("\n");
	free(players);
	assert(GetGroupsHighestLevel(DS, 3, &players) == FAILURE);
	Quit(&DS);

	printf("TEST_SCENARIO_2 - SUCCESS\n");
}

void TEST_SCENARIO_3()
{
	void* DS = Init();
	int playerId = 0;
	int numOfPlayers = 0;
	int* players = nullptr;

	int maxPlayers = 100;
	unsigned int seed = 5;

	(void)playerId;
	(void)numOfPlayers;
	(void)players;

	assert(AddGroup(DS, 1) == SUCCESS);
	assert(AddPlayer(DS, 1, 1, 37) == SUCCESS);

	for (int i = 2; i <= maxPlayers; i++)
	{
		assert(AddGroup(DS, i) == SUCCESS);
		assert(AddPlayer(DS, i, i, std::ceil(10.0 * (std::sin(i) + 1.0) + 1)) == SUCCESS);
	}

	std::vector<int> vector;

	//seed = std::chrono::system_clock::now().time_since_epoch().count();

	for (int i = 1; i <= maxPlayers / 2; i++)
	{
		vector.push_back(i);
	}

	shuffle(vector.begin(), vector.end(), std::default_random_engine(seed));

	int destGroup = vector[0];

	(void)destGroup;

	for (int i = 1; i < maxPlayers / 2; i++)
	{
		assert(ReplaceGroup(DS, vector[i], destGroup) == SUCCESS);
	}

	vector.clear();

	for (int i = maxPlayers / 2 + 1; i <= maxPlayers; i++)
	{
		vector.push_back(i);
	}

	shuffle(vector.begin(), vector.end(), std::default_random_engine(seed));

	destGroup = vector[0];

	for (int i = 1; i < maxPlayers - (maxPlayers / 2); i++)
	{
		assert(ReplaceGroup(DS, vector[i], destGroup) == SUCCESS);
	}

	assert(GetHighestLevel(DS, -1, &playerId) == SUCCESS);
	assert(playerId == 1);

	assert(GetAllPlayersByLevel(DS, -1, &players, &numOfPlayers) == SUCCESS);
	assert(numOfPlayers == maxPlayers);

	for (int i = 0; i < maxPlayers; i++)
	{
		printf("%d, ", players[i]);
	}
	printf("\n");

	free(players);

	printf("TEST_SCENARIO_3 - SUCCESS\n");

	Quit(&DS);
}

void TEST_SCENARIO_4()
{
	void* DS = Init();
	int playerId = 0;
	int numOfPlayers = 0;
	int* players = nullptr;

	int maxPlayers = 100;
	unsigned int seed = 5;

	(void)playerId;
	(void)numOfPlayers;
	(void)players;

	assert(AddGroup(DS, 1) == SUCCESS);
	assert(AddGroup(DS, 2) == SUCCESS);

	//seed = std::chrono::system_clock::now().time_since_epoch().count();

	for (int i = 1; i <= maxPlayers / 2; i++)
	{
		assert(AddPlayer(DS, i, 1, std::ceil(10.0 * (std::sin(i) + 1.0) + 1)) == SUCCESS);
	}

	for (int i = maxPlayers / 2 + 1; i <= maxPlayers; i++)
	{
		assert(AddPlayer(DS, i, 2, std::ceil(10.0 * (std::sin(i) + 1.0) + 1)) == SUCCESS);
	}

	std::vector<int> vector;

	for (int i = 1; i <= maxPlayers; i++)
	{
		vector.push_back(i);
	}

	shuffle(vector.begin(), vector.end(), std::default_random_engine(seed));

	for (int i = 0; i < vector.size(); i++)
	{
		assert(RemovePlayer(DS, vector[i]) == SUCCESS);
	}

	printf("TEST_SCENARIO_4 - SUCCESS\n");

	Quit(&DS);
}