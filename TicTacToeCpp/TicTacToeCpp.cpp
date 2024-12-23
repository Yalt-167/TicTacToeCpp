#include <iostream>

#include "Include/Grid.hpp"
#include "Include/Game.hpp"
#include "Include/Tree.hpp"

//#define RUN_TESTS
constexpr auto HUMAN_PLAYER = true;
constexpr auto DO_CLEAR_CONSOLE = true;

int main(int, char**)
{
#ifdef RUN_TESTS
	Node<int> node = Node<int>(1);
	node.AddChild(new Node<int>(3));
	node.AddChild(new Node<int>(2));
	node.Children[0]->AddChild(new Node<int>(4));
	node.Children[0]->AddChild(new Node<int>(5));
	node.Children[1]->AddChild(new Node<int>(7));
	node.Children[1]->AddChild(new Node<int>(6));
	node.DepthFirst();
#else
	Game(HUMAN_PLAYER, !HUMAN_PLAYER, DO_CLEAR_CONSOLE).Run();
#endif
}
