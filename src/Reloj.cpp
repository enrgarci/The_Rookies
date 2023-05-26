#include "Reloj.h"
#include "Partida.h"
#include "Clock.h"
#include "header.h"
#include <cmath>

Reloj::Reloj()
{
 
}

void Reloj::draw(Partida &P)
{
    //SIZE OF THE CLOCK
    float toScreenWidth = (float)1 / glutGet(GLUT_WINDOW_WIDTH);
    float toScreenHeigth = (float)1 / glutGet(GLUT_SCREEN_HEIGHT);
    float toScreen = toScreenWidth > toScreenHeigth ? toScreenWidth : toScreenHeigth;
    const float x = (posx + size * 31.5 / 64) * toScreen, const y = (posy + size * 31.5 / 64) * toScreen, a = 1;
    if (P.positions.size() > 1 && P.T->get_turn() == c) theta = P.getColorClock(c);
    
    glEnable(GL_TEXTURE_2D);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.5f);
   
    if(c == Negro)
    glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/ButtonsInterface/Marco_Reloj_Negro.png").id);
    if (c == Blanco)
    glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/ButtonsInterface/Marco_Reloj_Blanco.png").id);
   
    
    if ( P.getColorClock(c) < 0.1)
    {
        size =abs(minsize+ amplitud* sin(aum));
        aum +=0.4;               
    }    

    marco.Set(posx, posy, size , size , 200, 200, 200);
    marco.Draw();

    if (c == Negro)
    glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/ButtonsInterface/Aguja_Negra.png").id);
    if (c == Blanco)
    glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/ButtonsInterface/Aguja_Blanca.png").id);
    
    
    glTranslatef(x, y, 0);
    glRotatef(theta * 360, 0.0f, 0.0f, 1.0f);
    aguja.Set(0, 0, size /8, size * 14 / 32, 150, 100, 150);
    aguja.Draw();
    glRotatef(-theta * 360, 0.0f, 0.0f, 1.0f);
    glTranslatef(-x, -y, 0);

    glDisable(GL_TEXTURE_2D);
    glDisable(GL_ALPHA_TEST);
    glDisable(GL_BLEND);
   
}