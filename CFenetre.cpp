// Copyright 2021 Louise Kuhl <louise.kuhl@hotmail.fr>


#include "CFenetre.h"


CFenetre::CFenetre() : QWidget() {
    m_patient   = new CPatient(this);
    m_image     = new CImage(this);
    m_controle  = new CControle(this);

    QVBoxLayout* layoutfenetre = new QVBoxLayout(this);
    layoutfenetre->addWidget(m_patient);
    layoutfenetre->addWidget(m_image);
    layoutfenetre->addWidget(m_controle);

    QShortcut *shortcutSave  = new QShortcut(QKeySequence("Ctrl+S"), this);
    QShortcut *shortcutPrint = new QShortcut(QKeySequence("Ctrl+P"), this);

    QPushButton* boutonSave = m_controle->getBoutonSave();
    CPaint* paint = m_image->getPaint();

    QPushButton* boutonPrint = m_controle->getBoutonPrint();

    QObject::connect(boutonSave, SIGNAL(clicked()),
                     paint, SLOT(openDialogSave()));
    QObject::connect(boutonPrint, SIGNAL(clicked()),
                     paint, SLOT(drawID()));
    QObject::connect(shortcutSave, SIGNAL(activated()),
                     paint, SLOT(openDialogSave()));
    QObject::connect(shortcutPrint, SIGNAL(activated()),
                     paint, SLOT(drawID()));
}


CPatient *CFenetre::getPatient() {
    return m_patient;
}


CImage *CFenetre::getImage(){
    return m_image;
}
