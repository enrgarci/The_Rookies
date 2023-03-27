/// Have a nice day !
 //  Author: enrgarci
 //  Create Time: 2023-03-26 14:15:45
 //  Modified by: enrgarci
 //  Modified time: 2023-03-28 00:39:48
 //  Description:
 //
 
#include "Casilla.h"

inline void				Casilla::setCheck(bool inCheck){m_in_check = inCheck;}
inline void				Casilla::setFigure(Pieza::figura f){m_piece.fig = f;}
inline void				Casilla::setColor(Pieza::color c){m_piece.col = c;}
inline void				Casilla::setPiece(Pieza p){m_piece = p;}
inline void				Casilla::setPiece(Pieza::figura f, Pieza::color c){m_piece.fig = f; m_piece.col = c;}
inline Pieza::figura	Casilla::getFigure(){return m_piece.fig;}
inline Pieza::color		Casilla::getColor(){return m_piece.col;}
inline bool				Casilla::getCheck(){return m_in_check;}
inline	void			Casilla::setId(int id){m_id = id;}
inline	int				Casilla::getId(){return m_id;}
inline	bool			Casilla::getEnPassant(){return m_can_en_passant;}
inline	void			Casilla::setEnPassant(bool c){m_can_en_passant = c;}
inline	bool			Casilla::getPosMove(){return m_posible_destination;}
inline	void			Casilla::setPosMove(bool c){m_posible_destination = c;}
