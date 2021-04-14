// Copyright 2021 Louise Kuhl <louise.kuhl@hotmail.fr>


#include "CControle.h"


CControle::CControle(QWidget *parent) : QWidget(parent) {
    m_boutonPrint   = new QPushButton("Print");
    m_boutonSave    = new QPushButton("Save");
    m_boutonQuit    = new QPushButton("Quit");

    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->addWidget(m_boutonPrint);
    layout->addWidget(m_boutonSave);
    layout->addWidget(m_boutonQuit);

    QShortcut *shortcutQuit = new QShortcut(QKeySequence("Ctrl+Q"), this);

    QObject::connect(m_boutonQuit, SIGNAL(clicked()),
                     this, SLOT(quitApp()));
    QObject::connect(shortcutQuit, SIGNAL(activated()),
                     this, SLOT(quitApp()));
}


void CControle::quitApp() {
    QMessageBox::StandardButton res = QMessageBox::question(
        this,
        "Quit?",
        "Êtes-vous sûr de vouloir quitter ?",
        QMessageBox::Yes | QMessageBox::No,
        QMessageBox::Yes);

    if (res == QMessageBox::Yes) {
        qApp->quit();
    }
}


QPushButton* CControle::getBoutonSave() {
    return m_boutonSave;
}


QPushButton* CControle::getBoutonPrint() {
    return m_boutonPrint;
}
