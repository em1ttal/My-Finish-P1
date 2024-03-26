#include "Triangle.hh"

Triangle::Triangle() 
{
    p1 = vec3(-0.5, 0.0, 0.0);
    p2 = vec3(0.5 ,0.0, 0.0);
    p3 = vec3(0, 1, 0);
    normal = calculateNormal();
}

Triangle::Triangle(vec3 p1, vec3 p2, vec3 p3) 
{
    this->p1 = p1;
    this->p2 = p2;
    this->p3 = p3;
    normal = calculateNormal();
}

bool Triangle::hit(Ray &ray, float tmin, float tmax, bool bounding) const
{
    vec3 edge1 = p2 - p1;
    vec3 edge2 = p3 - p2;
    vec3 edge3 = p1 - p3;
    float d = -1 * dot(normal, p1);
    float t = -1 * (
        (dot(normal, ray.getOrigin()) + d) / (dot(normal, ray.getDirection()))
        );
    vec3 p = ray.getOrigin() + t * ray.getDirection();
    if (t < tmin || t > tmax) return false;
    
    vec3 C0 = p - p1;
    vec3 C1 = p - p2;
    vec3 C2 = p - p3;

    if (! ((dot(normal, cross(edge1, C0)) > 0) && (dot(normal, cross(edge2, C1)) > 0) && (dot(normal, cross(edge3, C2)) > 0)) ) return false;

    shared_ptr<HitRecord> hitRecord = make_shared<HitRecord>();
    hitRecord->t = t;
    hitRecord->p = ray.pointAt(hitRecord->t); // Punt de intersecció
    hitRecord->normal = normalize(cross(edge1, edge2)); // Normal del triangle
    hitRecord->mat = material;

    ray.insertHit(hitRecord);

    return true;
}

vec3 Triangle::calculateNormal() const 
{
    vec3 v1 = p2 - p1;
    vec3 v2 = p3 - p1;
    return normalize(cross(v1, v2));
}

bool Triangle::allHits(Ray &ray, float tmin, float tmax) const
{
    // As the triangle is a 2D object, we can't have more than one hit
    return hit(ray, tmin, tmax);
}

void Triangle::update(int nframe) 
{
    
}

void Triangle::aplicaTG(shared_ptr<TG> tg) 
{
   
}

void Triangle::read(const QJsonObject &json) 
{

}

void Triangle::write(QJsonObject &json) const 
{

}

void Triangle::print(int indentation) const 
{
    
}