// Copyright 2021 Louise Kuhl <louise.kuhl@hotmail.fr>


#include "CImage.h"


CImage::CImage(QWidget *parent) : QGroupBox("Image", parent) {
    // Widget qui gere l'image
    m_paint = new CPaint(this);

    // Creation des groupes
    QGroupBox *groupeEchelle      = new QGroupBox("Échelle", this);
    QGroupBox *groupeSegmentation = new QGroupBox("Segmentation", this);

    // Construction de tous les widgets (haut en bas)
    m_boutonLoad = new QPushButton("Load", this);

    QSpinBox *m_ratioSB = new QSpinBox(groupeEchelle);
    m_ratioSB->setRange(1, 100);
    m_ratioSB->setSuffix("%");
    m_ratioSB->setValue(100);

    QComboBox *m_formatCB = new QComboBox(groupeEchelle);
    m_formatCB->addItem("18x24");
    m_formatCB->addItem("24x30");
    m_formatCB->addItem("36x43");
    m_formatCB->addItem("20x25 (Mammographie)");
    m_formatCB->addItem("25x30 (Mammographie)");

    m_areaLabel = new QLabel(getAreaLabel(), groupeSegmentation);

    m_boutonFermer   = new QPushButton("Fermer polygone",
                                       groupeSegmentation);
    m_boutonEffacerD = new QPushButton("Effacer le dernier point",
                                       groupeSegmentation);
    m_boutonEffacerT = new QPushButton("Tout effacer",
                                       groupeSegmentation);

    // Creation des layouts
    QFormLayout *layoutEchelle = new QFormLayout(groupeEchelle);
    layoutEchelle->addRow("Ratio", m_ratioSB);
    layoutEchelle->addRow("Format", m_formatCB);

    QVBoxLayout *layoutSegmentation = new QVBoxLayout(groupeSegmentation);
    layoutSegmentation->addWidget(m_areaLabel);
    layoutSegmentation->addWidget(m_boutonFermer);
    layoutSegmentation->addWidget(m_boutonEffacerD);
    layoutSegmentation->addWidget(m_boutonEffacerT);

    QVBoxLayout *layoutControleImage = new QVBoxLayout();
    layoutControleImage->addWidget(m_boutonLoad);
    layoutControleImage->addWidget(groupeEchelle);
    layoutControleImage->addWidget(groupeSegmentation);

    // Layout principal
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(m_paint);
    layout->addLayout(layoutControleImage);

    // Raccourcis
    QShortcut *shortcutLoad       = new QShortcut(QKeySequence("Ctrl+O"), this);
    QShortcut *shortcutD          = new QShortcut(QKeySequence("Ctrl+D"), this);
    QShortcut *shortcutFermer     = new QShortcut(QKeySequence("Ctrl+F"), this);
    QShortcut *shortcutRemoveLast = new QShortcut(QKeySequence("Ctrl+Z"), this);
    QShortcut *shortcutID         = new QShortcut(QKeySequence("Ctrl+I"), this);

    // Connecteurs
    QObject::connect(m_boutonLoad, SIGNAL(clicked()),
                     m_paint, SLOT(openDialog()));
    QObject::connect(m_boutonEffacerT, SIGNAL(clicked()),
                     m_paint, SLOT(clearImage()));
    QObject::connect(m_boutonFermer, SIGNAL(clicked()),
                     m_paint, SLOT(closePoly()));
    QObject::connect(m_boutonEffacerD, SIGNAL(clicked()),
                     m_paint, SLOT(removelast()));
    QObject::connect(m_formatCB, SIGNAL(currentTextChanged(QString)),
                     this, SLOT(updateFormatHeight(QString)));
    QObject::connect(m_ratioSB, SIGNAL(valueChanged(int)),
                     this, SLOT(updateRatioPercent(int)));
    QObject::connect(this, SIGNAL(formatOrRatioChanged()),
                     this, SLOT(updateCoef()));
    QObject::connect(this, SIGNAL(coefChanged()),
                     this, SLOT(updateAreaLabel()));
    QObject::connect(shortcutLoad, SIGNAL(activated()),
                     m_paint, SLOT(openDialog()));
    QObject::connect(shortcutD, SIGNAL(activated()),
                     m_paint, SLOT(clearImage()));
    QObject::connect(shortcutFermer, SIGNAL(activated()),
                     m_paint, SLOT(closePoly()));
    QObject::connect(shortcutRemoveLast, SIGNAL(activated()),
                     m_paint, SLOT(removelast()));
    QObject::connect(m_paint, SIGNAL(areaPxChanged()),
                     this, SLOT(updateAreaLabel()));
    QObject::connect(m_paint, SIGNAL(imageHeightChanged()),
                     this, SLOT(updateCoef()));
    QObject::connect(shortcutID, SIGNAL(activated()),
                     m_paint, SLOT(drawID()));

    // Attributs
    updateFormatHeight(m_formatCB->currentText());
    updateRatioPercent(m_ratioSB->value());
}


void CImage::updateCoef() {
    int h = m_paint->getImageHeight();

    if (h == 0) {
        m_coef = 0;
    } else {
        m_coef = static_cast<float>(m_formatHeight)
            / static_cast<float>(h)
            * 100.0
            / static_cast<float>(m_ratioPercent);
    }

    emit coefChanged();
}


void CImage::updateFormatHeight(QString text) {
    m_formatHeight = getFormatIntFromText(text);
    emit formatOrRatioChanged();
}


void CImage::updateRatioPercent(int ratio) {
    m_ratioPercent = ratio;
    emit formatOrRatioChanged();
}


void CImage::updateAreaLabel() {
    m_areaLabel->setText(getAreaLabel());
}


QString CImage::getAreaLabel() {
    float areaMetric = m_paint->getAreaPx() * m_coef * m_coef;

    QString res = QString("%1 %2 %3")
        .arg(c_areaLabel1)
        .arg(areaMetric, 0, 'f', 1)
        .arg(c_areaLabel2);

    return res;
}


int CImage::getFormatIntFromText(QString text) {
    int res = text
        .split('x')
        .at(1)
        .toInt();

    return res;
}


CPaint* CImage::getPaint() {
    return m_paint;
}


QString CImage::getArea() {
    return m_areaLabel->text();
}
