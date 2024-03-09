#pragma once

#include <QtWidgets>
#include "Controller.hh"

class Builder : public QObject {
    Q_OBJECT

public:
    Builder(){};

public slots:
    void newSphere();
    void newSimulatedScene();
    void newVirtualScene();
    void loadSettings();
    void activaColorShading();
    void activaNormalShader();

signals:
     void settingsChanged();
};

