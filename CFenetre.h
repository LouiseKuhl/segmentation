// Copyright 2021 Louise Kuhl <louise.kuhl@hotmail.fr>


#ifndef CFENETRE_H_
#define CFENETRE_H_


#include "CImage.h"
#include "CPatient.h"
#include "CControle.h"


/**
 * \brief Fenêtre principale de l'application
 *
 * Cette fenêtre contient trois `QGroupBox` pour découper les fonctionnalités
 * de l'application.
 */
class CFenetre : public QWidget {
    Q_OBJECT


 public:
    /**
     * \brief Constructeur par défaut
     */
    CFenetre();
    /**
     * Accesseur
     *
     * \return CFenetre::m_patient
     */
    CPatient *getPatient();
    /**
     * Accesseur
     *
     * \return CFenetre::m_image
     */
    CImage *getImage();


 private:
    /**
     * Widget qui gère les informations du patient
     */
    CPatient *m_patient;
    /**
     * Widget qui gère l'image
     */
    CImage *m_image;
    /**
     * Widget qui gère les commandes de l'application
     */
    CControle *m_controle;
};


#endif  // CFENETRE_H_
