//
// Created by e.kravchenkova on 05.04.2025.
//

#pragma once
#include <QWidget>
#include <QPainter>
#include <QPainterPath>

class CircleImage : public QWidget {

public:
    CircleImage(QString path,QWidget* parent = nullptr) : QWidget(parent),pixmap(path) {
        setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    }

    QSize sizeHint() const override {
        return QSize(150,150);
    }
protected:
    void paintEvent(QPaintEvent* event) override {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        int penWidth = 4;
        QRect adjustedRect = rect().adjusted(penWidth/2, penWidth/2, -penWidth/2, -penWidth/2);

        QPainterPath path;
        path.addEllipse(rect());
        painter.setClipPath(path);

        painter.drawPixmap(adjustedRect,pixmap);
        painter.setClipping(false);
        painter.setPen(QPen(QColor("#6c1b4f"),penWidth));
        painter.drawEllipse(adjustedRect);
    }
private:
    QPixmap pixmap;
};

