#include <cmath>
#define M_PI 3.14159265358979323846

class Circle{
    public:
        double radius, xPos, yPos;
        Uint32 color;
        SDL_Surface* mySurface;

        Circle(double xPos, double yPos, double radius, SDL_Surface* mySurface, Uint32 color){
            this->xPos = xPos;
            this->yPos = yPos;
            this->radius = radius;
            this->color = color;
            this->mySurface = mySurface;
        }

        //disclaimer: this is just straight up stolen. i did not know how to code this
        void FillCircle(){
            double powRadius = pow(radius, 2);

            for (int i = xPos - radius; i <= xPos + radius; i++){
                for (int j = yPos - radius; j < yPos + radius; j++){
                    double powDist = pow(i - xPos, 2) + pow(j - yPos, 2);
                    
                    if (powDist < powRadius){
                        SDL_Rect pixel = {i, j, 1, 1};
                        SDL_FillSurfaceRect(mySurface, &pixel, color);
                    }
                }
            }
        }
};

struct Ray{
    double originX, originY, angle, angleDeg, directionX, directionY;
};

class Sun : public Circle{
    public:
        Ray raysArray[36];
        
        void CastRays(){
            for (int i = 0; i < 36; i++){
                raysArray[i].originX = this->xPos;
                raysArray[i].originY = this->yPos;

                raysArray[i].angleDeg = i * 10.0;
                raysArray[i].angle = raysArray[i].angleDeg * (M_PI / 180.0);

                raysArray[i].directionX = cos(raysArray[i].angle);
                raysArray[i].directionY = sin(raysArray[i].angle);


                //TODO: make rays actually be rendered. rn they are being simulated but not actually drawn to the surface
                //TODO: program ray collision
            }
        }

        Sun(double xPos, double yPos, double radius, SDL_Surface* mySurface, Uint32 color) : Circle(xPos, yPos, radius, mySurface, color){
            CastRays();
        }

};