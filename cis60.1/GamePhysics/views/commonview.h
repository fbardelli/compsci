#ifndef COMMONVIEW_H
#define COMMONVIEW_H

#include <QGraphicsView>

class CommonView : public QGraphicsView
{
    Q_OBJECT
public:
    CommonView(QGraphicsScene *scene,QWidget *parent);

signals:

public slots:

};

#endif // COMMONVIEW_H
