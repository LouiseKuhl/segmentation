// Copyright 2021 Louise Kuhl <louise.kuhl@hotmail.fr>

#ifndef CIMAGE_H_
#define CIMAGE_H_


#include <QGroupBox>
#include <QPushButton>
#include <QSpinBox>
#include <QComboBox>
#include <QLabel>
#include <QShortcut>
#include <QHBoxLayout>
#include <QFormLayout>

#include "CPaint.h"


/**
 * \brief Widget qui gère la partie "image" de l'application
 *
 * On peut découper ce Widget en deux parties :
 * \li une partie "paint" qui contient une image et les dessins que
 * l'utilisateur peut faire, entièrement contenue dans le membre \p m_paint ;
 * \li une partie qui contrôle les actions possible sur la partie précédente
 * et un label qui imprime l'aire du polygone.
 */
class CImage : public QGroupBox {
    Q_OBJECT

 public:
    /**
     * Constructeur par défaut
     *
     * \param parent Widget parent
     */
    explicit CImage(QWidget *parent = nullptr);
    /**
     * Accesseur
     *
     * \return CImage::m_paint
     */
    CPaint* getPaint();
    /**
     * \return Le texte contenu dans le label CImage::m_areaLabel
     * \sa CImage::m_areaLabel
     */
    QString getArea();

 private:
    /**
     * Bouton pour charger une image
     *
     * \sa CPaint::openDialog
     */
    QPushButton *m_boutonLoad;
    /**
     * Bouton pour fermer le polygone
     *
     * \sa CPaint::closePoly
     */
    QPushButton *m_boutonFermer;
    /**
     * Bouton pour effacer le dernier point tracé
     *
     * \sa CPaint::removeLast
     */
    QPushButton *m_boutonEffacerD;
    /**
     * Bouton pour effacer tout le tracé
     * 
     * \sa CPaint::clearImage
     */
    QPushButton *m_boutonEffacerT;
    /**
     * SpinBox qui définit le ratio de notre image radiologique
     *
     * Le ratio d'une image radiologique est le coefficient appliqué pour
     * traduire une longueur sur l'image en longueur dans le monde réel.
     *
     * \sa m_ratioPercent
     */
    QSpinBox *m_ratioSB;
    /**
     * ComboBox qui définit le format de notre image radiologique
     *
     * Les formats possibles sont (en cm) :
     * \li \c 18x24
     * \li \c 24x30
     * \li \c 36x43
     * 
     * \sa m_formatHeight
     */
    QComboBox *m_formatCB;
    /**
     * Label qui imprime l'aire du polygone
     *
     * \sa CImage::updateAreaLabel, CImage::getArea
     */
    QLabel *m_areaLabel;
    /**
     * Objet qui gère la partie image et dessine
     *
     * \sa CImage::getPaint
     */
    CPaint *m_paint;
    /**
     * Coefficient qui permet de traduire des pixels en cm dans le monde réel
     *
     * Le coefficient \f$c\f$ est calculé suivant
     * \f{equation}{
     *  c\ :=\ \frac{h_F}{h_I}\cdot\frac{100}{r}\,,
     * \f}
     * avec \f$h_F\f$ la hauteur du format (en cm),
     * \f$h_I\f$ la hauteur de l'image (en pixels),
     * \f$r\f$ le ratio (en pourcent).
     *
     * \sa CImage::updateCoef, CImage::coefChanged
     */
    float m_coef;
    /**
     * Hauteur de l'image radiologique, en cm
     *
     * \sa CImage::m_formatCB
     */
    int m_formatHeight;
    /**
     * Ratio de l'image radiologique, en pourcent
     *
     * \sa CImage::m_ratioSB
     */
    int m_ratioPercent;
    /**
     * Retourne la chaîne de caractère a inclure dans \p m_areaLabel
     *
     * \return Une chaîne de caractère du type `Aire : 1.2 cm2`
     * \sa CImage::m_areaLabel
     */
    QString getAreaLabel();
    /**
     * Retourne la hauteur du format, en cm
     *
     * \param text Le format en text, *e.g.* `18x24`
     * \return La hauteur en cm, *e.g* `24`
     */
    int getFormatIntFromText(QString text);
    /**
     * Variable constante qui définit une partie du label qui affiche l'aire
     *
     * \sa c_areaLabel2
     */
    const QString c_areaLabel1 = "Aire :";
    /**
     * Variable constante qui définit une partie du label qui affiche l'aire
     *
     * \sa c_areaLabel1
     */
    const QString c_areaLabel2 = "cm2";


 public slots:
    /**
     * Slot qui actualise le coefficient
     *
     * \sa CImage::m_coef, CImage::coefChanged
     */
    void updateCoef();
    /**
     * Slot qui actualise la hauteur du format
     *
     * \sa CImage::m_formatHeight, CImage::getFormatIntFromText,
     * CImage::formatOrRatioChanged
     */
    void updateFormatHeight(QString text);
    /**
     * Slot qui actualise le ratio \p m_ratio
     *
     * \param ratio La valeur à actualiser, en pourcent
     * \sa CImage::m_ratioPercent, CImage::formatOrRatioChanged
     */
    void updateRatioPercent(int ratio);
    /**
     * Slot qui actualise le label qui imprime l'aire
     *
     * \sa CImage::m_areaLabel, CImage::getAreaLabel
     */
    void updateAreaLabel();

 signals:
    /**
     * Signal lorsque le format ou bien le ratio a changé
     *
     * \sa CImage::updateFormatHeight, CImage::updateRatioPercent,
     * CImage::updateCoef
     */
    void formatOrRatioChanged();
    /**
     * Signal lorsque le coefficient a changé
     *
     * \sa CImage::updateCoef, CImage::updateAreaLabel
     */
    void coefChanged();
};


#endif  // CIMAGE_H_
