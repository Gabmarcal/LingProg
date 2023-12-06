#include "MenuLogado.h"

#include <iostream>

using namespace std;

MenuLogado::MenuLogado(string nomeBancoDeDados, string nomeSchema) : Menu(nomeBancoDeDados, nomeSchema) {}

MenuLogado::~MenuLogado() {}

void MenuLogado::printarOpcoes() {}

bool MenuLogado::executarEscolha( int escolha ) {return true;}