//
// Created by e.kravchenkova on 05.04.2025.
//

#ifndef QTCLIENT_CLICABLELABEL_H
#define QTCLIENT_CLICABLELABEL_H


#include <QLabel>
#include <QWidget>
#include <Qt>

class ClickableLabel : public QLabel {
Q_OBJECT

public:
    explicit ClickableLabel(QWidget* parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags());
    ~ClickableLabel();

signals:
    void clicked();

protected:
    void mousePressEvent(QMouseEvent* event);

};


#endif //QTCLIENT_CLICABLELABEL_H
