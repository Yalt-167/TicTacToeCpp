#include <iostream>
#include <cstdlib>
#include<functional>
#include <thread>
#include <chrono>


#include "../Include/Game.hpp"
#include "../Include/Player.hpp"
#include "../Include/HumanPlayer.hpp"
#include "../Include/CPUPlayer.hpp"

Game::Game(bool playerOneIsHuman, bool playerTwoIsHuman, bool doClearConsole_)
{
	players[0] = playerOneIsHuman ? (Player*)new HumanPlayer('X') : (Player*)new CPUPlayer('X');
	players[1] = playerTwoIsHuman ? (Player*)new HumanPlayer('O') : (Player*)new CPUPlayer('O');

	twoAIs = !(playerOneIsHuman || playerTwoIsHuman);
	inputValidationPredicate = std::bind(&Game::InputIsInvalid, this, std::placeholders::_1);

	doClearConsole = doClearConsole_;
}

Game::~Game()
{
	delete[] players;
}

void Game::Run()
{
	while (playing)
	{
		GatherInput();
		Render();
		VerifyWin();
	}
}

void Game::GatherInput()
{
	grid.Place(players[(int)currentPlayerIsO]->GatherInput(inputValidationPredicate, grid), currentPlayerIsO);
	turns++;
}

bool Game::InputIsInvalid(int input)
{
	if (input < 1)
	{
		std::cout << "This input is too small" << std::endl;
		return true;
	}

	if (input > 9)
	{
		std::cout << "This input is too big" << std::endl;
		return true;
	}

	if (!grid.IsSlotEmpty(input - 1))
	{
		std::cout << "There is a symbol in this slot already" << std::endl;
		return true;
	}

	return false;
}

void Game::VerifyWin()
{
	if (grid.VerifyWin())
	{
		std::cout << (currentPlayerIsO ? 'O' : 'X') << " has won" << std::endl;
		Reset();
	}

	if (turns == 9)
	{
		std::cout << "Its a Draw" << std::endl;
		Reset();
	}
		
	currentPlayerIsO = !currentPlayerIsO;

	if (twoAIs)
	{
		std::this_thread::sleep_for(std::chrono::seconds(1)); // so we can actually see what happens
	}
}

void Game::Render() const
{
	if (doClearConsole)
	{
		system("cls");
	}

	grid.Render();
}

void Game::Reset()
{
	turns = 0;

	grid.Clear();

	for (int i = 0; i < 2; i++)
	{
		players[i]->Reset();
	}
}
