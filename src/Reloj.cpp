#include "Reloj.h"
#include "Partida.h"
#include "Clock.h"

void Reloj::draw(Partida &P)
{
    //SIZE OF THE CLOCK
    theta = P.getColorClock(c);
    std::cout << P.getColorClock(c);
    
    //Eneable
    glEnable(GL_TEXTURE_2D);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.5f);

    //Time-out animation
    if (theta < 0.25)
    {
  
        if (ClengthANDheight <= ClengthMAX)
        {
            ClengthANDheight += Rinc;
            Alength += Rinc;
            Aheight += Rinc;
        }

        if (ClengthANDheight == ClengthMAX) Rinc *= -1;
        std::cout << Rinc;
    }
    else
    {
        ClengthANDheight = ClengthMIN;
    }

    //Setting position of the elements
    aguja.Set(posxAguja, -14, Alength, Aheight, 150, 100, 150);
    marco.Set(posx, 530, ClengthANDheight, ClengthANDheight, 200, 200, 200);

    //DRAW
    //Draw reloj
    glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/ButtonsInterface/marco reloj.png").id);
    marco.Draw();

    //Draw aguja
    glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/ButtonsInterface/Aguja.png").id);
    float x = 1.5, y = 0.7, a = 1;

    glTranslatef(x, y, 0);
    glRotatef(theta * 360, 0.0f, 0.0f, 1.0f);
    aguja.Draw();
    glRotatef(-theta * 360, 0.0f, 0.0f, 1.0f);
    glTranslatef(-x, -y, 0);

    //Disable
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_ALPHA_TEST);
    glDisable(GL_BLEND);
}