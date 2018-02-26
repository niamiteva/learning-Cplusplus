/**

    The following program shows the possible bus routes
    after the user has entered starting station and final station.

    First the program ask for inputing bus count, buses and their routes,
    then print all bus routes and ask the user for start station and final station.

    The program use list, which elements are graphs.
    The elements of the graph are type station(name of the station and the number of the bus)
    For the program are used the template classes LList and graph, which uses the class LList.
    (The used classes are the implementations from M.Todorova's book "Data Structures and Algorithms")

*/

#include <iostream>
#include <string>
#include "graph.cpp"
#include "llist.cpp"


using namespace std;

#define MAX 500

/*
    station -> the elements of the graph
    name -> name of station
    busNumber -> the number of the bus that stops on that station
*/
struct station
{
    string name;
    int busNumber;

    /*
        extra operators to adapt the structure for the used classes
    */
    bool operator!=(const station& other) const
    {
        return name!=other.name || busNumber!=other.busNumber;
    }
    bool operator==(const station& other) const
    {
        return name==other.name && busNumber==other.busNumber;
    }
    operator=(const station& other)
    {
        name = other.name;
        busNumber = other.busNumber;
    }

    friend ostream& operator<<(ostream& out, const station s)
    {
        out<<s.name<<"->"<<s.busNumber<<" ";

        return out;
    }
};

typedef graph<station> stationG;
typedef LList<stationG> graphList;

/*
    creating list of graph from input in the console
    (it can be transformed to be using input file)
*/
void create(graphList& l, int* buses)
{
    // count of graphs (bus routes)
    int busses=0;
    cout<<"Enter count of buses: ";
    cin>>busses;

    // creating every graph
    for(int i=0; i<busses; i++)
    {
        stationG g;

        int bus=0;
        cout<<"Bus number: ";
        cin>>bus;
        // array with the numbers of the buses to help the program search routs by bus routes
        buses[i] = bus;

        // number of stations where the bus stops
        int stations=0;
        cout<<"Enter count of stations for bus "<<bus<<" : ";
        cin>>stations;

        // creating the stations and the connections between them
        for(int j=0; j<stations;j++)
        {
            cout<<"Station name: ";
            string stationName;
            cin>>stationName;

            station s;
            s.name = stationName;
            s.busNumber = bus;

            g.addTop(s);

            // if the rout is circular every station has one connection
            int nearStations=0;
            cout<<"Next or/and(enter 1 or 2) previous stations: ";
            cin>>nearStations;

            //creating the connections
            for(int k=0; k<nearStations;k++)
            {
                cout<<"Station name: ";
                cin>>stationName;

                station s1;
                s1.name = stationName;
                s1.busNumber = bus;

                g.addRib(s, s1);
            }
        }
        l.ToEnd(g);
    }
}
// helper for function way -> checks if element is a member of the list
bool member(const station& x, LList<station>& l)
{
    l.IterStart();
    elem_link1<station>* p = l.Iter();

    while(p && p->inf != x) p= p->link;

    return p!=NULL;
}
// helper for the function way -> deletes the last member of the list
void deleteLast(LList<station>& l)
{
    l.IterStart();
    station x;
    elem_link1<station> *p = l.Iter();

    while(p->link) p = l.Iter();

    l.DeleteElem(p,x);
}
// helper for the function findMyWay
// recursive function that checks if there is route from station A to station B and safe the found route in list l
bool way(const station& stA, const station& stB, stationG& g, LList<station>& l)
{
    l.ToEnd(stA);
    if(stA==stB) return true;

    elem_link1<station>* q = g.point(stA);
    q = q->link;

    while(q)
    {
        if(!member(q->inf,l))
        {
            if(way(q->inf, stB, g, l)) return true; //recursive call
            deleteLast(l); //returning back
        }
        q =q->link;
    }
    return false;
}
// function that finds all way from station A to station B and prints the possible routes
void findMyWay(graphList& l, int* buses)
{
    // asks the user to input starting station objects and final station
    // creating new stations for the function way
    station s1,s2;
    cout<<"Enter starting station: ";
    string stationA; cin>>stationA;
    s1.name = stationA;
    cout<<"Enter final station: ";
    string stationB; cin>>stationB;
    s2.name = stationB;

    //starting from the beginning of the graphList
    l.IterStart();
    elem_link1<stationG> *p = l.Iter();

    // check every graph for route A->B
    cout<<"Your options are: \n";
    int i=0;
    while(p)
    {
        // getting the bus numbers from the array and complete the station objects
        s1.busNumber = buses[i];
        s2.busNumber = buses[i];
        // we search for top of the graph equal to our station object A(s1)
        if(p->inf.top(s1))
        {
            // if we have top s1 we find its address and search for routes to station object B(s2)
            LList<station> l;
            way(s1,s2,p->inf,l);
            //if l is empty this means that we have not found route A->B
            if(l.empty()) cout<<"Sorry! There is no way from station "<<stationA<<" to station "<<stationB<<".\n";
            else
                l.print();
        }
        p =p->link;
        i++;
    }

}

// print the graphList
void printGList(graphList& l)
{
    l.IterStart();
    elem_link1<stationG>* p= l.Iter();

    while(p)
    {
        p->inf.print();
        p=p->link;
    }
}

int main()
{
    // array with the numbers of the buses to help the program search routs by bus routes
    int buses[MAX];

    graphList gl;

    create(gl, buses);
    printGList(gl);
    findMyWay(gl, buses);

    return 0;
}
