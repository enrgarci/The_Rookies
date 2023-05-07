#include "Partida.h"
#include "Tablero.h"
#include "Casilla.h"

Partida::Partida(string w_player, string b_player, string init_pos)
{
	T = new Tablero(*this, init_pos);
	m_w_player = w_player;
	m_b_player = b_player;
	positions.push_back(init_pos);
}

Partida::Partida(std::fstream &file)
{
	string raw,w_p, b_p;
	vector<FEN> my_pos;
	cout << "Reading from file..." << endl;
	while (getline(file, raw))
	{
		bool done = false;
		if (raw.find("White") != string::npos) 
		{
			int b, end, len;
			b = raw.find_first_of("\"") + 1;
			end = raw.find_last_of("]") - 1;
			len = end - b;
			w_p = raw.substr(b, end - b);
			done = true;
		}
		else if (raw.find("Black") != string::npos) 
		{
			int b, end, len;
			b = raw.find_first_of("\"") + 1;
			end = raw.find_last_of("]") - 1;
			len = end - b;
			b_p = raw.substr(b, end - b);
			done = true;
		}
		else if(!done) my_pos.push_back(raw);
	}
	file.close();
	m_w_player = w_p;
	m_b_player = b_p;
	positions = my_pos;
	T = new Tablero((*this), positions.at(0));
}

Partida::~Partida()
{
	delete Tablero::s_king, Tablero::s_king = nullptr;
	delete Tablero::s_queen, Tablero::s_queen = nullptr;
	delete Tablero::s_knight, Tablero::s_knight = nullptr;
	delete Tablero::s_rook, Tablero::s_rook = nullptr;
	delete Tablero::s_pawn, Tablero::s_pawn = nullptr;
	delete Tablero::s_bishop,Tablero::s_bishop = nullptr;
	delete Tablero::s_empty, Tablero::s_empty = nullptr;
	delete T;
}

Tablero &Partida::getBoard()
{
	return *T;
}

string Partida::getPlayer(int col)
{
	if (col == 2) return(m_b_player);
	if (col == 1) return(m_w_player);
	return m_w_player + "/" + m_b_player;
}

void Partida::play_back()
{
	if (current_pos >= 1) 
	{
		current_pos--;
		delete T;
		T = new Tablero(*this, positions.at(current_pos));
	}
}

void Partida::play_forward()
{
	if (current_pos < positions.size() - 1) 
	{
		current_pos++;
		delete T;
		T = new Tablero(*this,positions.at(current_pos));
	}
}

void Partida::play_last()
{
	current_pos = positions.size() - 1;
	delete T;
	T = new Tablero(*this,positions.at(current_pos));
}
void Partida::play_first()
{
	current_pos = 0;
	delete T;
	T = new Tablero(*this,positions.at(current_pos));
}

void Partida::add_pos()
{
	if (current_pos != positions.size() - 1) return;
	positions.push_back((*T).get_fen());
	current_pos = positions.size() - 1;
}

void Partida::undoMove()
{
	Tablero *p_T = T;
	if (current_pos != positions.size() - 1) return;
	positions.pop_back();
	current_pos = positions.size() - 1;
	T = new Tablero(*this,positions.back());
	delete p_T;
}

void Partida::save(string directory, string name)
{
	cout << "Saving file..." << directory << name << endl;
	std::ofstream saveFile(directory + name);
	saveFile << "[White \"" << m_w_player << "\"]  " << endl;
	saveFile << "[Black \"" << m_b_player << "\"]  " << endl;
	for (auto s : positions) saveFile << s << endl;
	saveFile.close();
}

int	Partida::perf(Partida &p, int depth)
{
	if (depth == 0) return 1;
	int nodes = 0;
	static int special[4] = {};

	for (int i = 0; i < BOARD_SIZE; i++)
	{
		if (p.T->get_cell(i).getFigura() == Vacio) continue;
		if (p.T->get_cell(i).getColor() != p.T->get_turn()) continue;
		vector<int> T_moves = p.T->get_cell(i).getMoveList();
		for (auto move : T_moves)
		{
			special [p.T->do_move(i, move)]++;
			nodes += perf(p, depth - 1);
			p.undoMove();
		}
	}
	return nodes;
}
