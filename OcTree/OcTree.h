#ifndef OCTREE_H
#define OCTREE_H

#include "punto.h"
#include <vector>
#include <QtDebug>


using namespace std;



class OctTree
{
public:

    bool leaf;
    Point dimMax;
    Point dimMin;
    vector<Point *> data;
    OctTree(){

        dimMin = Point(-1,-1,-1);
        dimMax = Point(1,1,1);
        leaf = true;
    }
    OctTree(Point min, Point max){
        dimMax = max;
        dimMin = min;
        leaf = true;
    }
    ~OctTree(){
        for(auto i = 0;i<data.size();i++)
            delete data[i];
        if(northWestF){
            delete northWestF;
            delete southWestF;
            delete northEastF;
            delete southEastF;
            delete northWestB;
            delete southWestB;
            delete northEastB;
            delete southEastB;
        }
    }
    //OCTANTE FRONTAL
    OctTree *northWestF;
    OctTree *southWestF;
    OctTree *northEastF;
    OctTree *southEastF;
    //OCTANTE POSTERIOR
    OctTree *northWestB;
    OctTree *southWestB;
    OctTree *northEastB;
    OctTree *southEastB;

     bool find(Point *pt, OctTree **pQT ){
        if(leaf){
            *pQT = this;
            for(auto i=0;i<data.size();i++){

                if(data[i]->x == pt->x and data[i]->y == pt->y and data[i]->z == pt->z){
                    return true;
                }
            }
            return false;
        }
        return ubic(pt)->find(pt,pQT);
    }

    OctTree* ubic(Point *point){              //EN QUE OCTANTE SE ENCUENTRA EL PUNTO
        float midX = (dimMax.x + dimMin.x)/2;
        float midY = (dimMax.y + dimMin.y)/2;
        float midZ = (dimMax.z + dimMin.z)/2;


        if (point->x <= midX)
                {
                    if (point->y <= midY)
                    {
                        if (point->z <= midZ)
                            return southWestB;
                        return southWestF;
                    }
                    else {
                        if (point->z <= midZ)
                            return northWestB;
                        return northWestF;
                    }
                }
                else {
                    if (point->y <= midY)
                    {
                        if (point->z <= midZ)
                            return southEastB;
                        return southEastF;
                    }
                    else {
                        if (point->z <= midZ)
                            return northEastB;
                        return northEastF;
                    }
                }
    }

    bool insert(Point *ptr)
    {

        OctTree *pQT = nullptr;

        if(find(ptr,&pQT)) return false; //SI NO EXISTE

        if(pQT==nullptr) return false;

        if( pQT->Parada() ){

            pQT->leaf = false;

            float midX = (pQT->dimMax.x + pQT->dimMin.x)/2;
            float midY = (pQT->dimMax.y + pQT->dimMin.y)/2;
            float midZ = (pQT->dimMax.z + pQT->dimMin.z)/2;


            pQT->northWestF = new OctTree(Point(pQT->dimMin.x,midY,midZ),Point(midX,pQT->dimMax.y,pQT->dimMax.z));
            pQT->southWestF = new OctTree(Point(pQT->dimMin.x,pQT->dimMin.y,midZ),Point(midX,midY,pQT->dimMax.z));
            pQT->northEastF = new OctTree(Point(midX,midY,midZ),pQT->dimMax);
            pQT->southEastF = new OctTree(Point(midX,pQT->dimMin.y,midZ),Point(pQT->dimMax.x,midY,pQT->dimMax.z));

            pQT->northWestB = new OctTree(Point(pQT->dimMin.x,midY,pQT->dimMin.z),Point(midX,pQT->dimMax.y,midZ));
            pQT->southWestB = new OctTree(pQT->dimMin,Point(midX,midY,midZ));
            pQT->northEastB = new OctTree(Point(midX,midY,pQT->dimMin.z),Point(pQT->dimMax.x,pQT->dimMax.y,midZ));
            pQT->southEastB = new OctTree(Point(midX,pQT->dimMin.y,pQT->dimMin.z),Point(pQT->dimMax.x,midY,midZ));


            for(auto i = 0;i<int(pQT->data.size());i++)
                (pQT->ubic(pQT->data[i]))->insert(pQT->data[i]);

            (pQT->ubic(ptr))->insert(ptr);

            (pQT->data).clear();

        }else
            (pQT->data).push_back(ptr);
        return true;


    }

    void printQ(){
        qDebug() << data.size() << "   ";
    }



private:

    inline bool Parada(){
        if(data.size() >= 1500)
            return true;
        return false;

    }
};

#endif // OCTREE_H
