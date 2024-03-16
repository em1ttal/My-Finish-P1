#pragma once

#include <QtWidgets>
#include "Controller.hh"

class Builder : public QObject {
    Q_OBJECT

public:
    Builder(){};

public slots:
    void newSphere();
    void newBox();
    void newSimulatedScene();
    void newVirtualScene();
    void loadSettings();
    void activaColorShading();
    void activaNormalShader();
    void activaNColorShader();
signals:
     void settingsChanged();
};

