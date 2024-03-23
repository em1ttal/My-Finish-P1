#include <QVector>
#include <QVector3D>

#include "Mesh.hh"

Mesh::Mesh(const QString &fileName): Object()
{
    nom = fileName;
    load(fileName);
}

Mesh::~Mesh() {
    if (cares.size() > 0) cares.clear();
    if (vertexs.size() > 0) vertexs.clear();

}

void Mesh::makeTriangles() {
    // TO DO Fase 1: A implementar
    triangles.clear();
    for (const auto& face : cares) {
        vec4 v0 = vertexs[face.idxVertices[0]];
        vec4 v1 = vertexs[face.idxVertices[1]];
        vec4 v2 = vertexs[face.idxVertices[2]];
        vec3 p0 = vec3(v0.x, v0.y, v0.z);
        vec3 p1 = vec3(v1.x, v1.y, v1.z);
        vec3 p2 = vec3(v2.x, v2.y, v2.z);
        Triangle triangle(p0, p1, p2);
        triangles.push_back(triangle);
    }
}

bool Mesh::hit(Ray& raig, float tmin, float tmax) const {
    bool hit = false;
    float aux = tmax;
    shared_ptr<HitRecord> closest = nullptr;
    for (const auto& triangle : triangles) {
        if (triangle.hit(raig, tmin, aux)) {
            hit = true;
            aux = raig.getHitRecords()[0]->t;
            closest = raig.getHitRecords()[0];
        }
    }
    if (closest)
    {
        raig.addHit0(closest);
    }
    

    return hit;
}

bool Mesh::allHits(Ray& raig, float tmin, float tmax) const {
    // TODO Tutorial 1: A implementar
    bool hits = false;

    for (const auto& triangle : triangles) {
        if (triangle.hit(raig, tmin, tmax)) {
            raig.insertHit(raig.getHit(0));
            hits = true;
        }
    }
    return hits;
}


void Mesh::aplicaTG(shared_ptr<TG> t) {
    // TO DO: Fase 1
}

void Mesh::update(int frame) {
    // TO DO: Cal ampliar-lo per a fer el update de la mesh
}

void Mesh::load (QString fileName) {
    QFile file(fileName);
    if(file.exists()) {
        if(file.open(QFile::ReadOnly | QFile::Text)) {
            while(!file.atEnd()) {
                QString line = file.readLine().trimmed();
                QStringList lineParts = line.split(QRegularExpression("\\s+"));
                if(lineParts.count() > 0) {
                    // if it’s a comment
                    if(lineParts.at(0).compare("#", Qt::CaseInsensitive) == 0)
                    {
                        // qDebug() << line.remove(0, 1).trimmed();
                    }

                    // if it’s a vertex position (v)
                    else if(lineParts.at(0).compare("v", Qt::CaseInsensitive) == 0)
                    {
                        vertexs.push_back(vec4(lineParts.at(1).toFloat(),
                                               lineParts.at(2).toFloat(),
                                               lineParts.at(3).toFloat(), 1.0f));
                    }

                    // if it’s a normal (vn)
                    else if(lineParts.at(0).compare("vn", Qt::CaseInsensitive) == 0)
                    {

                    }
                    // if it’s a texture (vt)
                    else if(lineParts.at(0).compare("vt", Qt::CaseInsensitive) == 0)
                    {

                    }

                    // if it’s face data (f)
                    // there’s an assumption here that faces are all triangles
                    else if(lineParts.at(0).compare("f", Qt::CaseInsensitive) == 0)
                    {
                        Face *face = new Face();

                        // get points from v array
                        face->idxVertices.push_back(lineParts.at(1).split("/").at(0).toInt() - 1);
                        face->idxVertices.push_back(lineParts.at(2).split("/").at(0).toInt() - 1);
                        face->idxVertices.push_back(lineParts.at(3).split("/").at(0).toInt() - 1);

                        cares.push_back(*face);
                    }
                }
            }
            file.close();
            makeTriangles();
        } else {
            qWarning("Boundary object file can not be opened.");
        }
    } else  qWarning("Boundary object file not found.");
}

void Mesh::read (const QJsonObject &json)
{
    Object::read(json);
    if (json.contains("objFileName") && json["objFileName"].isString()) {
        nom = json["objFileName"].toString();
        load(nom);
    }
}


//! [1]
void Mesh::write(QJsonObject &json) const
{
    Object::write(json);
    json["objFileName"] = nom;
}
//! [1]

void Mesh::print(int indentation) const
{
    Object::print(indentation);
    const QString indent(indentation * 2, ' ');
    QTextStream(stdout) << indent << "objFileName:\t" << nom << "\n";
}



