#include <QCoreApplication>
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <stdlib.h>

//using namespace std;



class NBild {
    private:
        std::string bildString;

        //hier ist das Problem
        int cols = 89;
        int rows = 303;


    public:
        //std::string picture{""};
        std::vector<char> pictureVector;
        void readPicture();
        void writePicture(std::string txtinput);
        int readOnPic(int x, int y);
        void writeOnPic(int x, int y, char newChar);
        int targetPoint(int x, int y);
        void gui();
        void printPicture();
        void randomPic(int height, int width);
};

class cBild {
    public:

        int cols = 89;
        int rows = 303;
        std::vector<char> bildVector; //Block A = 01  B = 10
        void populateVector();        //          10      01
        void addBlock(int x, int y, char valuePic, char valueRand);
        std::vector<int> calculateBlock(int x, int y);
        void encrypt();
        std::vector<char> active, key;

};

void cBild::populateVector(){ //soll den Vector mit Nullen füllen.
    //int i;
    for (int i=0; i <= 108653; i++){
        bildVector.push_back('0');
    };
};

void cBild::addBlock(int x, int y, char valuePic, char valueRand){ // soll aus den Koordinaten und dem Wert des Pixels den entsprechenden Block berechnen und direkt an der richtigen Stelle in den Vector einfügen.
    std::vector<int> blockValues;
    //std::cout << "calculate test";
    blockValues = calculateBlock(x, y); //blockValues beinhaltet nun die Stellen an den der Block eingefügt werden soll.
    //std::cout << "calculate test2";
    int xy1, xy2, xy3, xy4;
    xy1 = blockValues[0];
    xy2 = blockValues[1];
    xy3 = blockValues[2];
    xy4 = blockValues[3];

    //if abfrage die checkt welcher Block an der Stelle sein soll, und dann entsprechenden Block einfügt
    if (valuePic == '0' && valueRand == '1'){     //01
                                                  //10
        //std::cout << "calculate test3";
        bildVector[xy1] = '0';
        //std::cout << bildVector[xy1] << std::endl;
        bildVector[xy2] = '1';
        //std::cout << bildVector[xy2] << std::endl;
        bildVector[xy3] = '1';
        bildVector[xy4] = '0';
        //std::cout << std::endl << bildVector[xy1] << bildVector[xy2] << std::endl << bildVector[xy3] << bildVector[xy4] << " " << xy1 << xy2 << xy3 << xy4  << std::endl;
    }
    if (valuePic == '0' && valueRand == '0'){     //10
                                                  //01
        //std::cout << "calculate test4";
        bildVector[xy1] = '1';
        bildVector[xy2] = '0';
        bildVector[xy3] = '0';
        bildVector[xy4] = '1';
        //std::cout << std::endl << bildVector[xy1] << bildVector[xy2] << std::endl << bildVector[xy3] << bildVector[xy4] << " " << xy1 << xy2 << xy3 << xy4 << std::endl;
    }
    if (valuePic == '1' && valueRand == '0'){     //01
                                                  //10
        //std::cout << "calculate test5";
        bildVector[xy1] = '0';
        bildVector[xy2] = '1';
        bildVector[xy3] = '1';
        bildVector[xy4] = '0';
        //std::cout << std::endl << bildVector[xy1] << bildVector[xy2] << std::endl << bildVector[xy3] << bildVector[xy4] << " " << xy1 << xy2 << xy3 << xy4  << std::endl;
    }
    if (valuePic == '1' && valueRand == '1'){     //10
                                                  //01
        //std::cout << "calculate test6";
        bildVector[xy1] = '1';
        bildVector[xy2] = '0';
        bildVector[xy3] = '0';
        bildVector[xy4] = '1';
        //std::cout << std::endl << bildVector[xy1] << bildVector[xy2] << std::endl << bildVector[xy3] << bildVector[xy4] << " " << xy1 << xy2 << xy3 << xy4  << std::endl;
    }
    else{
        //std::cout << valuePic << " " << valueRand << " ";
        //std::cerr << "Fehler";
    }

}

std::vector<int> cBild::calculateBlock(int x, int y){  //soll berechnen welche Stellen in dem Block Vector eine Stelle im ursprünglichen Bild ist.
    //int rows = 179;
    int altcols = 607;

    int xy1, xy2, xy3, xy4;
    std::vector<int> blockCoords;
    xy1 = (2*y)*(altcols+1)+(2*x); //berechnet aus dem ursprünglichen Pixel direkt die Stellen die es im eindimensionalen Vector haben wird.
    xy2 = (2*y)*(altcols+1)+((2*x)+1);
    xy3 = ((2*x)+1)+(altcols)+(2*y);
    xy4 = ((2*x)+1)+(altcols)+((2*y)+1);
    //std::cout << xy1 << " " << xy2 << " " << xy3 << " " << xy4 << " " << std::endl;
    blockCoords.push_back(xy1); //fügt die berechneten Stellen in einen Vector ein, damit dieser dann ausgegeben werden kann.
    blockCoords.push_back(xy2);
    blockCoords.push_back(xy3);
    blockCoords.push_back(xy4);
    return blockCoords;
};

void cBild::encrypt(){
    //bekommt keine Eingabe, stattdessen soll er zwei txt Dateien einlesen, und aus diesen den neuen Vector berechnen.
    //der key mit dem gearbeitet werden soll ist in randomkey.txt gespeichert
    //das Bild mit dem gearbeitet werden soll ist in activepicture.txt gespeichert.
    //Dieser neue Vector besteht aus den Blöcken A und B.
    populateVector();
    active.clear();
    key.clear();
    char x;
    cols = 89;
    rows = 303;


    //der key wird aus der txt Datei ausgelesen, danach enthält key die Inhalte von randomkey.txt
    std::fstream keystream("randomkey.txt");
    if (! keystream) {
        std::cerr << "Datei existiert nicht." << std::endl;
    }
    else{
        while (keystream >> x){
            key.push_back(x);
        }
        keystream.close();
    }

    //Das zu verschlüsselnde Bild wird aus der Datei eingelesen, danach enthält active die Inhalte von activepicture.txt
    std::fstream activestream("activepicture.txt");
    if (! activestream) {
        std::cerr << "Datei existiert nicht." << std::endl;
    }
    else{
        while (activestream >> x){
            active.push_back(x);
        }
        activestream.close();
    }

    for (int i = 0; i <= active.size(); i++){ //Fragwürdig ob das so richtig funktioniert.
        int vecrow = i % 303; //berechnet die grade bearbeitete Stelle als Koordinate damit addBlock damit weiter rechnen kann.
        int veccol = i / 303;
        addBlock(vecrow, veccol, active[i], key[i]);
    }
    int counter = 0;
//    for(int i=0; i < 179; i++ ) {

//        for(int j=0; j < 607; j++) {
//            std::cout << bildVector[counter++];
//        }
//        std::cout << std::endl;
//    }

    //jetzt muss das resultierende Blocklbild in einer txt Datei gespeichert werden.
    std::ofstream blockpic;

    blockpic.open("encryptedPicture.txt");
    for(int i=0;i<bildVector.size();i++){
        blockpic << bildVector[i];
    };
    blockpic.close();

}

void NBild::readPicture(){
    pictureVector.clear();
    char x;
    cols = 89;
    rows = 303;
//das Bild "bild1.txt" wird geöffnet und dem fstream bild1 zugeordnet
    std::fstream bild1("bild1.txt");

    //Überprüfung ob die Datei gefunden wird.
    if (! bild1) {
        std::cerr << "Datei existiert nicht." << std::endl;
    }
    else{
        //Die Datei wird symbol für symbol eingelesen.
        while (bild1 >> x){ //http://www.fredosaurus.com/notes-cpp/io/readtextfile.html
         pictureVector.push_back(x);
        }
        //die Datei wird wieder geschlossen.
        bild1.close();
    }
    //printet den Vector mit den Bilddaten auf die Console, die Zeilenumbrüche müssen eingefügt werden.

};
int NBild::targetPoint(int x,int y){
    int targetPoint = 0;
    targetPoint = x + y*(rows);
    return targetPoint;
};
int NBild::readOnPic(int x, int y){
    int target = targetPoint(x,y);
    std::cout << pictureVector[target] << std::endl;
    return pictureVector[target];
};
void NBild::writeOnPic(int x, int y, char newChar){
    int target = targetPoint(x,y);
    pictureVector[target] = newChar;

};
void NBild::writePicture(std::string txtinput){
    //http://www.cplusplus.com/doc/tutorial/files/
    std::ofstream txtpic;

    txtpic.open(txtinput);
    for(int i=0;i<pictureVector.size();i++){
        txtpic << pictureVector[i];
    };



    txtpic.close();

};
void NBild::printPicture(){
    int counter = 0;
    for(int i=0; i < cols; i++ ) {

        for(int j=0; j < rows; j++) {
            std::cout << pictureVector[counter++];
        }
        std::cout << std::endl;
    }
};
void NBild::randomPic(int height, int width){
    //srand((int)time(nullptr));
    int x,y;
    pictureVector.clear(); //Der Vektor wird als erstes geleert
    cols = height;
    rows = width;
    for(x=0; x<=cols; x++)
    {
        for(y=0;y<=rows;y++)
        {
            int r = rand() % 2; //es wird eine zufällige Zahl zwischen 0 und 1 generiert
            if (r == 0){ //weil die rand() Funktion einen int Wert zurück gibt wird so der wert mit zwei if abfragen in einen char wert übersetzt
                pictureVector.push_back('0');
            }
            if (r == 1){
                pictureVector.push_back('1');
            }

        }
    }
};

void NBild::gui(){
    int input = 0;
    std::cout << "Welcome, please enter one of the following numbers." << std::endl;
    std::cout << "1  : Input a new picture." << std::endl;
    std::cout << "2  : Print current picture to console." << std::endl;
    std::cout << "3  : Show pixel by index." << std::endl;
    std::cout << "4  : Edit pixel by index." << std::endl;
    std::cout << "5  : Save Picture to file." << std::endl;
    std::cout << "6  : Create a random picture." << std::endl;
    std::cout << "7  : Quit the programm" << std::endl;
    std::cout << "8  : Create a key for the default Picture." << std::endl;
    std::cout << "9  : Encrypt the currently active picture with a key that is stored in randomkey.txt" << std::endl;
    std::cout << "10 : Print encrypted Picture." << std::endl;
    std::cin >> input;

    if(input == 1){
        readPicture();
        gui();
    }
    if(input == 2){
        printPicture();
        gui();
    }
    if(input == 3){ //der User wird aufgefordert die x und y Koordinaten einzugeben, und bekommt dann als ausgabe die Farbe des zugehörigen "pixels"
        int xCoord, yCoord, indexVal;
        std::cout << "Enter x coordinate." << std::endl;
        std::cin >> xCoord;
        std::cout << "Enter y coordinate." << std::endl;
        std::cin >> yCoord;
        indexVal = readOnPic(xCoord,yCoord);
        //std::cout << indexVal << std::endl;
        gui();
    }
    if(input == 4){
        int xCoord, yCoord;
        char newChar;
        std::cout << "Enter x coordinate." << std::endl;
        std::cin >> xCoord;
        std::cout << "Enter y coordinate." << std::endl;
        std::cin >> yCoord;
        std::cout << "Enter new color, 0 or 1" << std::endl;
        std::cin >> newChar;
        writeOnPic(xCoord,yCoord,newChar);
        gui();
    }
    if(input == 5){
        std::string saveinput;
        std::cout << "What would you like to call the new file" << std::endl;
        std::cin >> saveinput;
        if(saveinput == "bild1.txt"){
            std::cerr << "Please choose a different name.";
        }
        if(saveinput == "randomkey.txt"){
            std::cerr << "Please choose a different name.";
        }
        if(saveinput == "activepicture.txt"){
            std::cerr << "Please choose a different name.";
        }

        else{
            writePicture(saveinput);
            std::cout << "The Picture was saved:" << std::endl;
        }

        gui();
    }
    if(input == 6){
        int randCols, randRows;
        std::cout << "Enter the heigth." << std::endl;
        std::cin >> randCols;
        std::cout << "Enter the width." << std::endl;
        std::cin >> randRows;
        randomPic(randCols, randRows);
        gui();
    }
    if(input == 7){
        exit(0);
    }
    if(input== 8){ //es soll ein zufälliges Bild von der selben Größe wie dem standart "PRG Praktikum" Bild erstellt werden.
        char yninput;
        randomPic(89, 303);
        std::cout << "The key was created, do you want to save the key? (y/n)" << std::endl;
        std::cin >> yninput;
        if(yninput == 'y'){
            writePicture("randomkey.txt");
            std::cout << "The key was saved, you can now use it." << std::endl;
        }
        if(yninput == 'n'){
            std::cout << "The key was not saved, you can save it later if you want." << std::endl;
        }
        gui();
    }
    if(input==9){ //der Inhalt des aktiven Bilds soll mit dem Inhalt in reandomkey.txt mithilfe von encrypt verschlüsselt werden.
                    //wie kann ich in der NBild Funktion gui () dei cBild Funktion encrypt() aufrufen?
        writePicture("activepicture.txt"); // Das aktive Bild wird in activepicture.txt gespeichert, damit die andere Funktion darauf zugreifen kann.
        //std::cout << "test";
        cBild cbild1{};
        //std::cout << "test1";
        cbild1.encrypt();
        //std::cout << "test2";
        std::cout << "The encrypted picture is now stored in encryptedPicture.txt" << std::endl;
        gui();
    }

    if(input == 0){
        std::cerr << "Input war 0" << std::endl;

    }
    else{
        std::cerr << "nono" << std::endl;
        gui();
    };


}



int main()
{
NBild nbild1{};
std::cout << 70/89;
nbild1.gui();


//nbild1.readPicture();
//nbild1.readOnPic(11,83); // readOnPic(Spalte, Zeile)
//nbild1.readOnPic(11,70); // gibt grade 0 aus
//nbild1.readOnPic(0,0);
//nbild1.writeOnPic(11,0);
//nbild1.writeOnPic(11,1);
//nbild1.writePicture();
}

