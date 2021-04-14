// Copyright 2021 Louise Kuhl <louise.kuhl@hotmail.fr>


#ifndef CCONTROLE_H_
#define CCONTROLE_H_


#include <QPushButton>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QApplication>
#include <QShortcut>


/**
 * \brief Widget qui gère les commandes de l'application
 *
 * Les commandes sont :
 * \li imprimer les informations du patient sur l'image ;
 * \li sauvegarder l'image ;
 * \li quitter l'application.
 */
class CControle : public QWidget {
    Q_OBJECT


 public:
    /**
     * \brief Constructeur par défaut
     *
     * \param parent Widget parent
     */
    explicit CControle(QWidget *parent = nullptr);
    /**
     * Accesseur
     *
     * \return CControle::m_boutonSave
     */
    QPushButton* getBoutonSave();
    /**
     * Accesseur
     *
     * \return CControle::m_boutonPrint
     */
    QPushButton* getBoutonPrint();


 private:
    /**
     * Bouton pour imprimer les infos sur l'image
     *
     * \sa CPaint:drawID
     */
    QPushButton* m_boutonPrint;
    /**
     * Bouton pour sauvegarder l'image
     *
     * \sa CPaint::openDialogSave
     */
    QPushButton* m_boutonSave;
    /**
     * Bouton pour quitter l'application
     *
     * \sa CControle::quitApp
     */
    QPushButton* m_boutonQuit;


 public slots:
    /**
     * Slot pour quitter l'application.
     *
     * Dans un premier temps ouvre une boîte de dialogue pour demander
     * confirmation.
     * Si la réponse est oui, quitte l'application.
     * Sinon, ne fait rien.
     *
     * \sa CControle::m_boutonQuit
     */
    void quitApp();
};


#endif  // CCONTROLE_H_
