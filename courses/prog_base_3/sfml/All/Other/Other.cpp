#include "Other.hpp"

void saveHero(const char * file, int Name, int R, int x, int y)
{
    ofstream fout(file, ios_base::app);
    fout << "Name = " << Name << "; R = " << R << "; x = " << x << "; y = " << y << "\n";
    fout.close();
}

void fileHeroCleaning(const char * file)
{
    fstream fileClean;
    fileClean.open(file, ios::out);
    fileClean << "";
    fileClean.close();
}

void heroCleaning(const char * file, int index)
{
    int Name;

    const int len = 50, strings = 1000;
    int countStr = 0;
    int delIndex = -1;
    char buffer[len][strings];

    ifstream fs(file, ios::in | ios::binary);
    while (fs.getline(buffer[countStr], 50))
    {
        char * pointName = strstr(buffer[countStr], "Name = ");
        pointName += 7;
        Name = atoi(pointName);

        if(Name == index)
        {
            delIndex = countStr;
        }
        countStr++;
    }
    fs.close();

    fileHeroCleaning(file);

    ofstream fout(file, ios_base::app);
    for(int k = 0; k < countStr; k++)
    {
        if(k != delIndex) fout << buffer[k] << "\n";
    }
    fout.close();
}

bool checkPos(const char * file, int posX, int posY, int index)
{
    int Name, R, x, y;

    const int len = 50, strings = 100;
    int countStr = 0;
    char buffer[len][strings];

    ifstream fs(file, ios::in | ios::binary);
    while (fs.getline(buffer[countStr], 50))
    {
        char * pointName = strstr(buffer[countStr], "Name = ");
        pointName += 7;
        Name = atoi(pointName);

        char * pointR = strstr(buffer[countStr], "R = ");
        pointR += 4;
        R = atoi(pointR);

        char * pointX = strstr(buffer[countStr], "x = ");
        pointX += 4;
        x = atoi(pointX);

        char * pointY = strstr(buffer[countStr], "y = ");
        pointY += 4;
        y = atoi(pointY);

        if(Name != index)
        {
            if ( (((posX - x)*(posX - x)) + ((posY - y)*(posY - y))) <= R * R )
            {
                fs.close();
                return false;
            }
        }
        countStr++;
    }
    fs.close();
    return true;
}
