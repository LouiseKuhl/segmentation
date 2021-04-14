// Copyright 2021 Louise Kuhl <louise.kuhl@hotmail.fr>

#include <QApplication>
#include <QPushButton>
#include <QWidget>

#include"CFenetre.h"
#include"CImage.h"


int main(int argc, char*argv[]) {
    QApplication app(argc, argv);

    CFenetre fenetre;
    fenetre.show();

    return app.exec();
}
