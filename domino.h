struct Domino {
int top;
int bottom;
bool sideways;
    Domino(int top = 0, int bottom = 0):
        top{top},
        bottom{bottom},
        sideways{false}{}

    void flip() {
        int tmp = this->top;
        this->top = this->bottom;
        this->bottom = tmp;
    }

    void rotateCCW() {
        this->sideways = true;
    }

    void rotateCW() {
        this->flip();
        this->sideways = true;
    }
};