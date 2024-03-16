#include "Box.hh"

Box::Box() {
    p1 = vec3(-1,-1,-1);
    p2 = vec3(1,1,1);
}

Box::Box(vec3 p1, vec3 p2) {
    this->p1 = p1;
    this->p2 = p2;
}

bool Box::hit(Ray &ray, float tmin, float tmax) const
{
    float txmin = (p1[0] - ray.getOrigin()[0]) / ray.getDirection()[0];
    float txmax = (p2[0] - ray.getOrigin()[0]) / ray.getDirection()[0];
    float tenterx = std::min(txmin, txmax);
    float texitx = std::max(txmin, txmax);

    float tymin = (p1[1] - ray.getOrigin()[1]) / ray.getDirection()[1];
    float tymax = (p2[1] - ray.getOrigin()[1]) / ray.getDirection()[1];
    float tentery = std::min(tymin, tymax);
    float texity = std::max(tymin, tymax);

    float tenter = std::max(tenterx, tentery);
    float texit = std::min(texitx, texity);
    if (tenter > texit) return false;
    if (tenter < tmin || tenter > tmax) return false;

    shared_ptr<HitRecord> hit = make_shared<HitRecord>();
    hit->t = tenter;
    hit->p = ray.pointAt(tenter);
    // Calcula la normal basada en el punt de intersecció.
    hit->normal = calculateNormal(hit->p);
    hit->mat = material;
    ray.insertHit(hit);
    return true;
}

vec3 Box::calculateNormal(const vec3 &p) const {
    vec3 normal;
    if (std::abs(p.x - p1.x) < 1e-6) normal = vec3(-1, 0, 0);
    else if (std::abs(p.x - p2.x) < 1e-6) normal = vec3(1, 0, 0);
    else if (std::abs(p.y - p1.y) < 1e-6) normal = vec3(0, -1, 0);
    else if (std::abs(p.y - p2.y) < 1e-6) normal = vec3(0, 1, 0);
    else if (std::abs(p.z - p1.z) < 1e-6) normal = vec3(0, 0, -1);
    else normal = vec3(0, 0, 1);
    return normal;
}

bool Box::allHits(Ray &ray, float tmin, float tmax) const
{
    bool hits = false;
    float txmin = (p1[0] - ray.getOrigin()[0]) / ray.getDirection()[0];
    float txmax = (p2[0] - ray.getOrigin()[0]) / ray.getDirection()[0];
    float tenterx = std::min(txmin, txmax);
    float texitx = std::max(txmin, txmax);

    float tymin = (p1[1] - ray.getOrigin()[1]) / ray.getDirection()[1];
    float tymax = (p2[1] - ray.getOrigin()[1]) / ray.getDirection()[1];
    float tentery = std::min(tymin, tymax);
    float texity = std::max(tymin, tymax);

    float tenter = std::max(tenterx, tentery);
    float texit = std::min(texitx, texity);
    if (tenter > texit) return false;
    if (texit < tmin || tenter > tmax) hits = false;

    if ((tenter > tmin && tenter < tmax) || (texit > tmin && texit < tmax)) 
    {
        shared_ptr<HitRecord> hitNear = make_shared<HitRecord>();
        hitNear->t = tenter;
        hitNear->p = ray.pointAt(tenter);
        // Calcula la normal basada en el punt de intersecció.
        hitNear->normal = calculateNormal(hitNear->p);
        hitNear->mat = material;
        ray.insertHit(hitNear);
        if (texit > tmin && texit < tmax && texit != tenter) 
        {
            shared_ptr<HitRecord> hitFar = make_shared<HitRecord>();
            hitFar->t = texit;
            hitFar->p = ray.pointAt(texit);
            // Calcula la normal basada en el punt de intersecció.
            hitFar->normal = calculateNormal(hitFar->p);
            hitFar->mat = material;
            ray.insertHit(hitFar);
        }
        hits = true;
    }
    return hits;
}

void Box::update(int nframe)
{
    // No fa res.
}

void Box::aplicaTG(shared_ptr<TG> tg)
{
    // No fa res.
}

void Box::read(const QJsonObject &json)
{
    /*
    Object::read(json);
    p1 = vec3(json["p1"].toArray()[0].toDouble(), json["p1"].toArray()[1].toDouble(), json["p1"].toArray()[2].toDouble());
    p2 = vec3(json["p2"].toArray()[0].toDouble(), json["p2"].toArray()[1].toDouble(), json["p2"].toArray()[2].toDouble());
    */
}

void Box::write(QJsonObject &json) const
{
    /*
    Object::write(json);
    QJsonArray p1Array;
    p1Array.push_back(p1[0]);
    p1Array.push_back(p1[1]);
    p1Array.push_back(p1[2]);
    json["p1"] = p1Array;
    QJsonArray p2Array;
    p2Array.push_back(p2[0]);
    p2Array.push_back(p2[1]);
    p2Array.push_back(p2[2]);
    json["p2"] = p2Array;
    */
}

void Box::print(int indentation) const
{
    /*
    string i(indentation, ' ');
    cout << i << "Box" << endl;
    cout << i << "p1: " << p1 << endl;
    cout << i << "p2: " << p2 << endl;
    Object::print(indentation);
    */
}