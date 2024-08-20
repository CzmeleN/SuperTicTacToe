#ifndef DATA_HPP
#define DATA_HPP

class Data {
public:
    Data();
    Data(int width, int height);

    int getWidth() const;
    int getHeight() const;
    void setResolution(int width, int height);

private:
    int width;
    int height;
};

#endif
