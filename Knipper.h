#pragma once

class Knipper {
    private:
    int period; 
    int treshold; 

    public:
    Knipper();
    Knipper(int treshold, int period);
    bool getValue(void);
};
