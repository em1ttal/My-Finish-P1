#pragma once

#include <vector>

#include <QString>
#include <QFile>
#include <QRegularExpression>

#include "Object.hh"
#include "Face.hh"

using namespace std;

class Mesh : public Object
{
public:
    Mesh() {};
    Mesh(const QString &fileName);

    virtual bool hit( Ray& r, float tmin, float tmax) const override;
    virtual bool allHits(Ray& r, float tmin, float tmax) const override;

    virtual void update(int nframe) override;
    virtual void aplicaTG(shared_ptr<TG> tg) override;

    virtual void read (const QJsonObject &json) override;
    virtual void write(QJsonObject &json) const override;
    virtual void print(int indentation) const override;

    virtual ~Mesh();
private:


    QString nom;
    vector<Face> cares; // facees o cares de l'objecte
    vector<vec4> vertexs; // vertexs de l'objecte sense repetits

    void load(QString filename);
    void makeTriangles();
};

