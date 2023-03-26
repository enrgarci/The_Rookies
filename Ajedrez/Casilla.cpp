/// Have a nice day !
 //  Author: enrgarci
 //  Create Time: 2023-03-26 14:15:45
 //  Modified by: enrgarci
 //  Modified time: 2023-03-26 17:31:48
 //  Description:
 //
 
#include "Casilla.h"

inline void				Casilla::setCheck(bool inCheck){m_in_check = inCheck;}
inline void				Casilla::setPiece(Pieza::figura f){m_piece.fig = f;}
inline void				Casilla::setColor(Pieza::color c){m_piece.col = c;}
inline Pieza::figura	Casilla::getPiece(){return m_piece.fig;}
inline Pieza::color		Casilla::getColor(){return m_piece.col;}
inline bool				Casilla::getCheck(){return m_in_check;}
