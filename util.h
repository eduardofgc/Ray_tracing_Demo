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

        //this is just stolen. i did not know how to do this
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

class Sun : public Circle{
    
};