// Copyright 2021 Louise Kuhl <louise.kuhl@hotmail.fr>


#include "CPatient.h"


CPatient::CPatient(QWidget *parent) :
        QGroupBox("Informations du patient", parent) {
    m_nom       = new QLineEdit(this);
    m_prenom    = new QLineEdit(this);
    m_date      = new QDateEdit(this);

    m_date->setCalendarPopup(true);

    QFormLayout *layout = new QFormLayout(this);
    layout->addRow("Nom", m_nom);
    layout->addRow("Prénom", m_prenom);
    layout->addRow("Date", m_date);
}


QString CPatient::getNom() {
    return m_nom->text();
}


QString CPatient::getPrenom() {
    return m_prenom->text();
}


QString CPatient::getDate() {
    return m_date->text();
}
