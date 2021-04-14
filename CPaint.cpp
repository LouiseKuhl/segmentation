// Copyright 2021 Louise Kuhl <louise.kuhl@hotmail.fr>


#include "CPaint.h"
#include "CFenetre.h"


CPaint::CPaint(QWidget *parent) : QWidget(parent) {
    m_image = new QImage;
    m_liPoint = new QVector<QPoint>;

    updateImageHeight();
    updateAreaPx();

    this->setFixedSize(c_paintWidth, c_paintHeight);
}


void CPaint::openDialog() {
    m_fileName = QFileDialog::getOpenFileName(
        this,
        "Open...",
        QString(),
        "Images (*.png *.jpg *.jpeg)");

    bool imageLoaded = m_image->load(m_fileName);
    if (!imageLoaded) {
        QMessageBox::critical(this, "Error", "You have to upload an image");
    } else {
        *m_image = m_image->scaled(this->size(), Qt::KeepAspectRatio);
        updateImageHeight();
    }

    update();
}


void CPaint::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    QRect rect = event->rect();
    painter.drawImage(rect, *m_image, rect);
}


void CPaint::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        m_liPoint->append(event->pos());
        draw();
    }
}


void CPaint::draw() {
    QPainter painter(m_image);

    QPen pen;

    pen.setColor(Qt::red);
    pen.setWidth(5);
    painter.setPen(pen);

    painter.drawPoint(m_liPoint->last());

    pen.setColor(Qt::green);
    pen.setWidth(3);
    painter.setPen(pen);

    if (m_liPoint->size() >1) {
        painter.drawLine(m_liPoint->at(m_liPoint->size() - 2),
                         m_liPoint->last());
    }

     update();
}


void CPaint::clearImage() {
    if (m_liPoint->isEmpty()) {
        return;
    }

    QMessageBox::StandardButton res = QMessageBox::question(
        this,
        "Quit?",
        "Êtes-vous sûr de vouloir tout effacer ?",
        QMessageBox::Yes | QMessageBox::No,
        QMessageBox::Yes);

    if (res == QMessageBox::Yes) {
        m_liPoint->clear();
        m_image->load(m_fileName);
        *m_image = m_image->scaled(this->size(), Qt::KeepAspectRatio);
        updateImageHeight();
    }

    update();
}


void CPaint::closePoly() {
    QPainter painter(m_image);
    QPen pen;
    pen.setColor(Qt::green);
    pen.setWidth(3);
    painter.setPen(pen);

    if (m_liPoint->size() > 2) {
        painter.drawLine(m_liPoint->first(), m_liPoint->last());

        update();
        updateAreaPx();
    }
}


void CPaint::removelast() {
    if (m_liPoint->size() > 0) {
        m_liPoint->removeLast();

        m_image->load(m_fileName);
        *m_image = m_image->scaled(this->size(), Qt::KeepAspectRatio);

        QPainter painter(m_image);
        QPen pen;
        pen.setColor(Qt::red);
        pen.setWidth(5);
        painter.setPen(pen);

        painter.drawPoints(*m_liPoint);

        pen.setColor(Qt::green);
        pen.setWidth(3);
        painter.setPen(pen);

        painter.drawPolyline(*m_liPoint);
    }

    update();
}


int CPaint::computeAreaPxFromPoints(QVector<QPoint> *vec) {
    int res = 0;

    for (int i = 0; i < vec->size()-1; i++) {
        res += vec->at(i).x() * vec->at(i+1).y();
        res -= vec->at(i+1).x() * vec->at(i).y();
    }

    res += vec->last().x() * vec->first().y();
    res -= vec->first().x() * vec->last().y();

    res /= 2;

    if (res < 0) {
        res *= -1;
    }

    return res;
}


void CPaint::updateAreaPx() {
    if (m_liPoint->size() < 3) {
        m_areaPx = 0;
    } else {
        m_areaPx = computeAreaPxFromPoints(m_liPoint);
    }
    emit areaPxChanged();
}


int CPaint::getAreaPx() {
    return m_areaPx;
}


int CPaint::getImageHeight() {
    return m_imageHeight;
}


void CPaint::openDialogSave() {
    QString saveName = QFileDialog::getSaveFileName(
        this,
        "Export Plot",
        ".",
        "PNG Files (*.png);;All Files (*)");

    m_image->save(saveName);
}


void CPaint::updateImageHeight() {
    m_imageHeight = m_image->height();
    emit imageHeightChanged();
}


void CPaint::drawID() {
    CFenetre *parentFenetre = qobject_cast<CFenetre *>(nativeParentWidget());

    QString sNom    = parentFenetre->getPatient()->getNom();
    QString sPrenom = parentFenetre->getPatient()->getPrenom();
    QString sDate   = parentFenetre->getPatient()->getDate();
    QString sArea   = parentFenetre->getImage()->getArea();

    QString patientNom    = QString("%1 : %2")
                                .arg("Nom")
                                .arg(sNom);
    QString patientPrenom = QString("%1 : %2")
                                .arg("Prénom")
                                .arg(sPrenom);
    QString patientDate   = QString("%1 : %2")
                                .arg("Date")
                                .arg(sDate);

    QPainter painter(m_image);

    QPen pen;
    painter.setPen(Qt::white);
    painter.setFont(QFont("Arial", 11));
    painter.drawText(0, 10, patientNom);
    painter.drawText(0, 20, patientPrenom);
    painter.drawText(0, 30, patientDate);
    painter.drawText(0, 40, sArea);

    update();
}
