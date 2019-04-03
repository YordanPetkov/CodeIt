class Cost{
    public:
    unsigned int PriceVal;
    unsigned int PricePos;
    unsigned int X,Y;
    unsigned int ValueX,ValueY;
    unsigned int Price;

    void setPriceVal(unsigned int PriceVal){
        this.PriceVal = PriceVal;
    }
    void setPricePos(unsigned int PricePos){
        this.PricePos = PricePos;
    }
    void setX(unsigned int X){
        this.X = X;
    }
    void setY(unsigned int Y){
        this.Y = Y;
    }
    void setValueX(unsigned int ValueX){
        this.ValueX = ValueX;
    }
    void setValueY(unsigned int ValueY){
        this.ValueY = ValueY;
    }
    void setPrice(unsigned int Price){
        this.Price = Price;
    }
    unsigned int getPrice(){
        return this.Price;
    }
}Cost[MAXN][MAXN];


void MakeClass(){
    for(unsigned int i = 0; i < MAXN; i++){
        for(unsigned int j = 0; j < MAXN; j++){
            Cost[i][j].setX(i);
            Cost[i][j].setY(j);
            Cost[i][j].setValueX(Perm[i]);
            Cost[i][j].setValueY(Perm[j]);
            Cost[i][j].setPricePos(PricePositions[i][j]);
            Cost[i][j].setPriceVal(PriceValue[i][j]);
            Cost[i][j].setPrice(PricePositions[i][j] + PriceValue[i][j]);
        }
    }
}
