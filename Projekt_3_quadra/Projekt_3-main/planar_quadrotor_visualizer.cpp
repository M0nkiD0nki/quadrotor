#include "planar_quadrotor_visualizer.h"

const float PlanarQuadrotorVisualizer::przelicznik=1000;
PlanarQuadrotorVisualizer::PlanarQuadrotorVisualizer(PlanarQuadrotor *quadrotor_ptr): quadrotor_ptr(quadrotor_ptr) {}

/**
 * TODO: Improve visualizetion
 * 1. Transform coordinates from quadrotor frame to image frame so the circle is in the middle of the screen
 * 2. Use more shapes to represent quadrotor (e.x. try replicate http://underactuated.mit.edu/acrobot.html#section3 or do something prettier)
 * 3. Animate proppelers (extra points)
 */
void PlanarQuadrotorVisualizer::render(std::shared_ptr<SDL_Renderer> &gRenderer) {
    Eigen::VectorXf state = quadrotor_ptr->GetState();
    float q_x, q_y, q_theta;

    /* x, y, theta coordinates */
    q_x = state[0];
    q_y = state[1];
    q_theta = state[2];
    //x = (x'-w/80)*40 = x*40 + w/2
    //y = -(y'+h/80)*40 = -y*40 - h/2
    SDL_Rect screen;
    SDL_RenderGetViewport(gRenderer.get(),&screen);
    SDL_SetRenderDrawColor(gRenderer.get(), 0xFF, 0x00, 0x00, 0xFF);
    SDL_SetRenderDrawColor(gRenderer.get(), 0xFF, 0x00, 0x00, 0x00);
    SDL_SetRenderDrawColor(gRenderer.get(), 0xFF, 0x80, 0x80, 0x80);

    q_x = q_x * przelicznik + screen.w / 2;
    q_y = -przelicznik * q_y + screen.h / 2;

    Sint16 tabx[]={q_x+35*cos(q_theta)-5*sin(q_theta),q_x-35*cos(q_theta)-5*sin(q_theta),q_x-35*cos(q_theta)+5*sin(q_theta),q_x+35*cos(q_theta)+5*sin(q_theta)};
    Sint16 taby[]={q_y-35*sin(q_theta)-5*cos(q_theta),q_y+35*sin(q_theta)-5*cos(q_theta),q_y+35*sin(q_theta)+5*cos(q_theta),q_y-35*sin(q_theta)+5*cos(q_theta)};

    filledPolygonColor(gRenderer.get(),tabx,taby,4,0xFF808080);
    
    Sint16 tabLWx[]={q_x-23+cos(q_theta)-14*sin(q_theta),q_x-23-cos(q_theta)-14*sin(q_theta),q_x-23-cos(q_theta)+14*sin(q_theta),q_x-23+cos(q_theta)+14*sin(q_theta)};
    Sint16 tabLWy[]={q_y-13-sin(q_theta)-14*cos(q_theta),q_y-13+sin(q_theta)-14*cos(q_theta),q_y-13+sin(q_theta)+14*cos(q_theta),q_y-13-sin(q_theta)+14*cos(q_theta)};
    
    SDL_SetRenderDrawBlendMode(gRenderer.get(), SDL_BLENDMODE_BLEND);

    filledPolygonColor(gRenderer.get(),tabLWx, tabLWy, 4, 0xFF808080);

    Sint16 tabRWx[]={q_x+23+cos(q_theta)-14*sin(q_theta),q_x+23-cos(q_theta)-14*sin(q_theta),q_x+23-cos(q_theta)+14*sin(q_theta),q_x+23+cos(q_theta)+14*sin(q_theta)};
    Sint16 tabRWy[]={q_y-13-sin(q_theta)-1*cos(q_theta),q_y-13+sin(q_theta)-14*cos(q_theta),q_y-13+sin(q_theta)+14*cos(q_theta),q_y-13-sin(q_theta)+14*cos(q_theta)};
    
    filledPolygonColor(gRenderer.get(),tabRWx, tabRWy, 4, 0xFF808080);

    filledCircleColor(gRenderer.get(), q_x - 17 , q_y - 23, 6, 0xFF000000);
    filledCircleColor(gRenderer.get(), q_x - 29 , q_y - 23, 6, 0xFF000000);

    filledCircleColor(gRenderer.get(), q_x + 17 , q_y - 23, 6, 0xFF000000);
    filledCircleColor(gRenderer.get(), q_x + 29 , q_y - 23, 6, 0xFF000000);


}