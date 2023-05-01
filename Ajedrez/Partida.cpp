#include "Partida.h"
#include "Tablero.h"

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
		if (raw.find("White") != string::npos) 
		{
				id_t b, end, len;
				b = raw.find_first_of("\"") + 1;
				end = raw.find_last_of("]") - 1;
				len = end - b;
				w_p = raw.substr(b, end - b);
		}
		if (raw.find("Black") != string::npos) 
		{
			id_t b, end, len;
			b = raw.find_first_of("\"") + 1;
			end = raw.find_last_of("]") - 1;
			len = end - b;
			b_p = raw.substr(b, end - b);
		}
		else my_pos.push_back(raw);
	}
	file.close();
	m_w_player = w_p;
	m_b_player = b_p;
	positions = my_pos;
	T = new Tablero((*this), positions.at(0));
}

Partida::~Partida()
{
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
		T = new Tablero(*this, positions.at(current_pos));
	}
}

void Partida::play_forward()
{
	if (current_pos < positions.size() - 1) 
	{
		current_pos++;
		T = new Tablero(*this,positions.at(current_pos));
	}
}

void Partida::play_last()
{
	current_pos = positions.size() - 1;
	T = new Tablero(*this,positions.at(current_pos));
}
void Partida::play_first()
{
	current_pos = 0;
	T = new Tablero(*this,positions.at(current_pos));
}

void Partida::add_pos()
{
	if (current_pos == positions.size() - 1)
		positions.push_back((*T).get_fen());
	current_pos = positions.size() - 1;
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
