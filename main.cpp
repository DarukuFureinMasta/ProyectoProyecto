#include <iostream>
#include "tipes.h"
#include "Container.h"
#include "Room.h"


int main() {
    Texto Ruta_Entrada="C:\\Users\\Intel\\Desktop\\f.txt";
    Texto outPath="C:\\Users\\Intel\\Desktop\\chad.txt";

    ifstream infile;
    ofstream outfile;

    infile.open(Ruta_Entrada);
    outfile.open(outPath);
    if(! infile) exit(-1);



    unsigned int nRobots = 0;

    if (infile.good())
    {
        string sLine;
        getline(infile, sLine);
        nRobots= stoi(sLine) ;
    }
    cout<<nRobots<<'\n';

    vector<string>     names;
    names.reserve(nRobots);
    for(unsigned int i=0;i<nRobots;i++){
        names.push_back(to_string(i));
    };

    for (const auto& item : names) cout << item << ' ';



    vector<vector<Texto>> Lineas(nRobots);
    unsigned int Robot = 0;
    unsigned int nline = 0;
    for (Texto line; getline(infile, line) && nline < nRobots; Robot++, nline++)
    {
        stringstream ss(line);
        Texto parsed;
        for (; getline(ss, parsed, ' ');)
            Lineas[Robot].push_back(parsed);
    }


    vector<pair<N, N>> spawnPoints;
    std::cout << '\n';
    for (const auto & linea : Lineas) {
        pair<N, N> newSP = {stoi(linea[0]), stoi(linea[1])};
        spawnPoints.push_back(newSP);
    }

/*
    for (Texto line; getline(infile, line) && nline >= nRobots; Robot++, nline++)
    {
        stringstream ss(line);
        Texto parsed;
        for (; getline(ss, parsed, ' ');)
            Lineas[Robot].push_back(parsed);
    }
*/



int cant_ordenes=0;
    int line_no = 0;
string line3="";
    while (line_no != (nRobots) && getline(infile, line3)) {
        ++line_no;
        if(line_no == nRobots){
            stringstream ss(line3);
            Texto parsed;
            for(;getline(ss,parsed,' ');)
                cant_ordenes=stoi(line3);

        }
    }
    cout<<cant_ordenes;



/*
    Room room(7, 7);

    vector<pair<N, N>> destinations =   {{0, 1}, {1, 1},{3,3}};

    for (N i = 0; i < spawnPoints.size(); ++i )
        room.placeRobot(spawnPoints[i].first, spawnPoints[i].second, names[i]);

    for ( N i = 0; i < destinations.size(); ++i )
    {
        auto & robot = room.robots().at(i);
        robot->assignDestination(room.atPosition(destinations[i].first, destinations[i].second));
    }

    room.printRoom();
    room.controlRobots();

    return 0;

    */
}

