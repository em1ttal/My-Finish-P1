#include "ShadingFactory.hh"


shared_ptr<ShadingStrategy> ShadingFactory::createShading(SHADING_TYPES t) {
    shared_ptr<ShadingStrategy> s;
    switch(t) {
    case COLORSHADING:
        s= make_shared<ColorShading>();
        break;
    case NORMAL:
        s = make_shared<NormalShading>();
        break;
    case NCOLORSHADING:
        s = make_shared<NColorShading>();
        break;
    default:
        s = nullptr;
    }
    return s;
}

ShadingFactory::SHADING_TYPES ShadingFactory::getShadingType(QString name) {
    
    if (name=="COLORSHADING") return SHADING_TYPES::COLORSHADING;
    if (name=="NORMAL") return SHADING_TYPES::NORMAL;
    if (name=="NCOLORSHADING") return SHADING_TYPES::NCOLORSHADING;
    return SHADING_TYPES::COLORSHADING;
}

QString ShadingFactory::getNameType(SHADING_TYPES t) {
    switch (t) {
    case COLORSHADING:
        return (QString("COLORSHADING"));
        break;
    case NORMAL:
        return (QString("NORMAL"));
        break;
    case NCOLORSHADING:
        return (QString("NCOLORSHADING"));
        break;    
    default:
        return(QString(""));
    }
}
ShadingFactory::SHADING_TYPES ShadingFactory::getIndexType(shared_ptr<ShadingStrategy> m) {
    if (dynamic_pointer_cast<ColorShading>(m) != nullptr) {
        return SHADING_TYPES::COLORSHADING;
    } else if (dynamic_pointer_cast<NormalShading>(m) != nullptr) {
        return SHADING_TYPES::NORMAL;
    } else if (dynamic_pointer_cast<NColorShading>(m) != nullptr) {
        return SHADING_TYPES::NCOLORSHADING;
    }
    return SHADING_TYPES::COLORSHADING;
}
