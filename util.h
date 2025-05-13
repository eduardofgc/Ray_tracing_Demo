#include <cmath>
#define M_PI 3.14159265358979323846
#define YELLOW 0xffd43b
#define WHITE 0xffffffff

void drawSetPixel(SDL_Surface* mySurface, Uint32 color, double x, double y){
    int trueX = (int) x;
    int trueY = (int) y;
    SDL_Rect pixel = {trueX, trueY, 1, 1};
    SDL_FillSurfaceRect(mySurface, &pixel, color);
}

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

        void MoveCircle(){
            
        }
};

struct Ray{
    double originX, originY, angle, angleDeg, directionX, directionY;
};

class Sun : public Circle{
    public:
        Ray raysArray[360];
        
        void CastRays(){ //TODO: program ray blur
            for (int i = 0; i < 360; i++){
                raysArray[i].originX = this->xPos;
                raysArray[i].originY = this->yPos;

                raysArray[i].angleDeg = i * 1.0;
                raysArray[i].angle = raysArray[i].angleDeg * (M_PI / 180.0);

                raysArray[i].directionX = cos(raysArray[i].angle);
                raysArray[i].directionY = sin(raysArray[i].angle);
            }
        }

        void DrawRays(Circle Obstacle){
            for (int i = 0; i < 360; i++){
                double endPoint = 1000;
                raysArray[i].originX = xPos;
                raysArray[i].originY = yPos;

                double tempX = raysArray[i].originX, tempY = raysArray[i].originY;
                bool objectHit = false;

                for (int j = 0; j < endPoint; j++){

                    double distanceX = Obstacle.xPos - tempX;
                    double distanceY = Obstacle.yPos - tempY;

                    if (distanceX * distanceX + distanceY * distanceY <= pow(Obstacle.radius, 2)){
                        objectHit = true;
                    }

                    if (!objectHit){
                        drawSetPixel(mySurface, YELLOW, tempX, tempY);

                        tempX += raysArray[i].directionX;
                        tempY += raysArray[i].directionY;
                    }

                    objectHit = false;
                }   
            }
        }

        Sun(double xPos, double yPos, double radius, SDL_Surface* mySurface, Uint32 color) : Circle(xPos, yPos, radius, mySurface, color){
            CastRays();
        }

};