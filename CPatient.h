// Copyright 2021 Louise Kuhl <louise.kuhl@hotmail.fr>


#ifndef CPATIENT_H_
#define CPATIENT_H_


#include <QGroupBox>
#include <QLineEdit>
#include <QDateEdit>
#include <QFormLayout>


/**
 * \brief Widget qui gère les informations du patient
 *
 * Les informations d'un patient sont son nom, son prénom et sa date
 * de naissance.
 */
class CPatient : public QGroupBox {
    Q_OBJECT


 public:
    /**
     * Construit un widget enfant de \p parent.
     *
     * \param parent Widget parent
     */
    explicit CPatient(QWidget *parent = nullptr);
    /**
     * \return Le nom du patient
     * \sa CPatient::m_nom
     */
    QString getNom();
    /**
     * \return Le prénom du patient
     * \sa CPatient::m_prenom
     */
    QString getPrenom();
    /**
     * \return La date de naissance du patient
     * \sa CPatient::m_date
     */
    QString getDate();


 private:
    /**
     * Le nom du patient
     */
    QLineEdit *m_nom;
    /**
     * Le prénom du patient
     */
    QLineEdit *m_prenom;
    /**
     * La date de naissance du patient
     */
    QDateEdit *m_date;
};


#endif  // CPATIENT_H_
