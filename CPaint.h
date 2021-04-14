// Copyright 2021 Louise Kuhl <louise.kuhl@hotmail.fr>


#ifndef CPAINT_H_
#define CPAINT_H_


#include <QWidget>
#include <QFileDialog>
#include <QMessageBox>
#include <QPainter>
#include <QImage>
#include <QVector>
#include <QPoint>
#include <QMouseEvent>
#include <QKeyEvent>


/**
 * \brief Widget qui affiche l'image et permet à l'utilisateur de dessiner
 * dessus
 */
class CPaint: public QWidget {
     Q_OBJECT


 public:
    /**
     * Constructeur par défaut
     *
     * \param parent Widget parent
     */
    explicit CPaint(QWidget *parent = nullptr);
    /**
     * Accesseur
     *
     * \return CPaint::m_areaPx
     */
    int getAreaPx();
    /**
     * Accesseur
     *
     * \return CPaint::m_imageHeight
     */
    int getImageHeight();


 private:
    /**
     * L'image sur laquelle on dessine
     */
    QImage *m_image;
    /**
     * Le chemin vers l'image
     */
    QString m_fileName;
    /**
     * Le vecteur de QPoint qui définit le polygone (sommets)
     */
    QVector<QPoint> *m_liPoint;
    /**
     * Aire du polygone, en pixels
     *
     * \sa CPaint::updateAreaPx, CPaint::getAreaPx, CPaint::areaPxChanged
     */
    int m_areaPx;
    /**
     * Hauteur de l'image, en pixels
     *
     * \sa CPaint::updateImageHeight, CPaint::getImageHeight,
     * CPaint::imageHeightChanged
     */
    int m_imageHeight;
    /**
     * Largeur du widget, fixée, en pixels
     */
    const int c_paintWidth = 400;
    /**
     * Hauteur du widget, fixée, en pixels
     */
    const int c_paintHeight = 400;
    /**
     * Dessine les points et lignes sur l'image
     *
     * Généralement appelée lorsque l'utilisateur clique sur l'image.
     * Dessine le dernier point de CPaint::m_liPoint (celui qui vient d'être
     * définit par le clique) et une ligne entre le dernier et avant-dernier
     * point.
     *
     * \sa CPaint::mousePressEvent
     */
    void draw();
    /**
     * Actualise l'attribut CPaint::m_areaPx
     *
     * Si le polygone est assez grand (plus que deux points), calcule
     * l'aire avec CPaint::computeAreaPxFromPoints().
     * Puis emet le signal CPaint::areaPxChanged().
     */
    void updateAreaPx();
    /**
     * Calcule l'aire d'un polygone, en pixels
     *
     * On note les coordonnées des sommets du polygone (dans l'ordre)
     * \f$(x_0, y_0), (x_1, y_1)\dots(x_{n-1}, y_{n-1})\f$.
     * L'aire du polygone est alors
     * \f{equation}{
     *  A\ =\ \frac12\sum_{i=0}^{n-1}x_iy_{i+1}-x_{i+1}y_i\,,
     * \f}
     * où \f$x_0=x_n\f$ et \f$y_0=y_n\f$.
     *
     * \param vec Un vecteur de QPoint, qui définit le polygone
     * \return L'aire du polygone en pixels
     */
    int computeAreaPxFromPoints(QVector<QPoint> *vec);
    /**
     * Actualise l'attribut CPaint::m_imageHeight
     *
     * \sa CPaint::imageHeightChanged
     */
    void updateImageHeight();


 protected:
    /**
     * Re-dessine le Widget lorsqu'un paint event est reçu
     *
     * \param event Un paint event
     * \sa CPaint::m_image
     */
    void paintEvent(QPaintEvent *event) override;
    /**
     * Evènement clique gauche
     *
     * Si clique gauche, ajoute la position du clique au vecteur
     * CPaint::m_liPoint puis dessine sur l'image avec CPaint::draw
     *
     * \param event Un mouse event
     * \sa CPaint::m_liPoint, CPaint::draw
     */
    void mousePressEvent(QMouseEvent *event) override;


 public slots:
    /**
     * Slot qui charge une image dans CPaint::m_image
     *
     * \sa CImage::m_boutonLoad.
     */
    void openDialog();
    /**
     * Slot qui efface les dessins sur l'image
     *
     * \sa CImage::m_boutonEffacerT.
     */
    void clearImage();
    /**
     * Slot qui ferme le polygone
     *
     * \sa CImage::m_boutonFermer, CPaint::updateAreaPx.
     */
    void closePoly();
    /**
     * Slot qui efface le dernier point et la ligne qui y est reliée.
     *
     * \sa CImage::m_boutonEffacerD.
     */
    void removelast();
    /**
     * Slot pour sauvegarder l'image
     *
     * \sa CControle::m_boutonSave
     */
    void openDialogSave();
    /**
     * Slot pour imprimer les informations du patient sur l'image
     *
     * \sa CControle::m_boutonPrint
     */
    void drawID();


 signals:
    /**
     * Signal émit lorsque CPaint::m_areaPx a changé
     *
     * \sa CPaint::m_areaPx, CPaint::updateAreaPx
     */
    void areaPxChanged();
    /**
     * Signal émit lorsque CPaint::m_imageHeight a changé
     *
     * \sa CPaint::m_imageHeight, CPaint::updateImageHeight
     */
    void imageHeightChanged();
};


#endif  // CPAINT_H_
