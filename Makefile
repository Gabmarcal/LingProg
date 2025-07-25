# Variáveis para os comandos de compilação e flags
CXX = g++
CXXFLAGS = -Wall
CLIBS = -lssl -lsqlite3 -lcrypto

# Nome do executável
TARGET = main

# Pasta para os arquivos fonte
SRCDIR = src/

# Pasta para os arquivos objeto
OBJDIR = obj/

# Arquivos fonte
SRC = $(SRCDIR)main.cpp $(SRCDIR)Projeto/Projeto.cpp $(SRCDIR)Usuario/Usuario.cpp $(SRCDIR)BancoDeDados/BancoDeDados.cpp $(SRCDIR)Tarefa/Tarefa.cpp $(SRCDIR)Usuario/Senha.cpp $(SRCDIR)Menu/Menu.cpp $(SRCDIR)Menu/MenuNaoLogado.cpp $(SRCDIR)Menu/MenuLogado.cpp $(SRCDIR)Menu/MenuProjetos.cpp

# Arquivos objeto
OBJ = $(OBJDIR)main.o $(OBJDIR)Projeto.o $(OBJDIR)Usuario.o $(OBJDIR)BancoDeDados.o $(OBJDIR)Tarefa.o $(OBJDIR)Senha.o $(OBJDIR)Menu.o $(OBJDIR)MenuNaoLogado.o $(OBJDIR)MenuLogado.o $(OBJDIR)MenuProjetos.o

# Regra padrão
all: $(TARGET)

# Como construir o executável final
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ) $(CLIBS)

# Regras para construir os arquivos objeto
$(OBJDIR)main.o: $(SRCDIR)main.cpp
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)main.cpp -o $(OBJDIR)main.o $(CLIBS)

$(OBJDIR)Projeto.o: $(SRCDIR)Projeto/Projeto.cpp
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)Projeto/Projeto.cpp -o $(OBJDIR)Projeto.o $(CLIBS)

$(OBJDIR)Usuario.o: $(SRCDIR)Usuario/Usuario.cpp
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)Usuario/Usuario.cpp -o $(OBJDIR)Usuario.o $(CLIBS)

$(OBJDIR)BancoDeDados.o: $(SRCDIR)BancoDeDados/BancoDeDados.cpp
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)BancoDeDados/BancoDeDados.cpp -o $(OBJDIR)BancoDeDados.o $(CLIBS)

$(OBJDIR)Tarefa.o: $(SRCDIR)Tarefa/Tarefa.cpp
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)Tarefa/Tarefa.cpp -o $(OBJDIR)Tarefa.o $(CLIBS)

$(OBJDIR)Senha.o: $(SRCDIR)Usuario/Senha.cpp
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)Usuario/Senha.cpp -o $(OBJDIR)Senha.o $(CLIBS)

$(OBJDIR)Menu.o: $(SRCDIR)Menu/Menu.cpp
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)Menu/Menu.cpp -o $(OBJDIR)Menu.o $(CLIBS)

$(OBJDIR)MenuNaoLogado.o: $(SRCDIR)Menu/MenuNaoLogado.cpp
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)Menu/MenuNaoLogado.cpp -o $(OBJDIR)MenuNaoLogado.o $(CLIBS)

$(OBJDIR)MenuLogado.o: $(SRCDIR)Menu/MenuLogado.cpp
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)Menu/MenuLogado.cpp -o $(OBJDIR)MenuLogado.o $(CLIBS)

$(OBJDIR)MenuProjetos.o: $(SRCDIR)Menu/MenuProjetos.cpp
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)Menu/MenuProjetos.cpp -o $(OBJDIR)MenuProjetos.o $(CLIBS)


# Regra para limpar os arquivos compilados
clean:
	rm -f $(OBJDIR)*.o $(TARGET)

# Regra para executar o programa
run: all
	./$(TARGET)

# Regra para limpar e executar o programa
rerun: clean
	clear
	make run